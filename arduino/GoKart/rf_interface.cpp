#include "rf_interface.h"
#include "Arduino.h"

namespace GoKart
{

  RFInterface* RFInterface::_activeRF = NULL;

  RFInterface::RFInterface(const uint8_t ch_num):
    ch_num_(ch_num)
  {
    // @TODO Assert ch_num > RF_INTERFACE_MAX_CH

    // Config ports
    ports_[0] = GOKART_RF_CH1_PIN;
    ports_[1] = GOKART_RF_CH2_PIN;
    ports_[2] = GOKART_RF_CH3_PIN;

    // Used for Steering wheel
    pinMode(GOKART_RF_CH1_PIN, INPUT); // Connected to CH1 of the Receiver
    // Used for brake and throttle
    pinMode(GOKART_RF_CH2_PIN, INPUT); // Connected to CH3 of the Receiver
    // Used for emergency
    pinMode(GOKART_RF_CH3_PIN, INPUT); // Connected to CH6 of the Receiver

    // Set active object
    _activeRF = this;

    // Attach interrups for PWM capture from receiver
    attachInterrupt(digitalPinToInterrupt(GOKART_RF_CH1_PIN), RFInterface::isrMeasureCH1, CHANGE);
    attachInterrupt(digitalPinToInterrupt(GOKART_RF_CH2_PIN), RFInterface::isrMeasureCH2, CHANGE);
    attachInterrupt(digitalPinToInterrupt(GOKART_RF_CH3_PIN), RFInterface::isrMeasureCH3, CHANGE);

    uptime_[0] = 0UL;
    uptime_[1] = 0UL;
    uptime_[2] = 0UL;

    enableFilter_ = true;

    counter_error = 0U;

    channelFlag = 0U;
    overrun = false;

  }

  bool RFInterface::init()
  {
    // @TODO Verify status! data received?
    if (RFInterface::isConsistency()){
      return true;
    }
    return false;
  }

  void RFInterface::measureCH1()
  {
    if ( digitalRead( GOKART_RF_CH1_PIN ) == HIGH )
    {
      risingTimeCH1 = micros(); //get time of pulse going up
    }
    else
    {
      fallingTimeCH1 = micros();  //get time of pulse going up
      upTimeCH1 = fallingTimeCH1 - risingTimeCH1;  //measure time between down and up
      channelFlag |= 1U;
    }
    
  }

  void RFInterface::measureCH2()
  {
    if ( digitalRead( GOKART_RF_CH2_PIN ) == HIGH )
    {
      risingTimeCH2 = micros(); //get time of pulse going up
    }
    else
    {
      fallingTimeCH2 = micros();  //get time of pulse going up
      upTimeCH2 = fallingTimeCH2 - risingTimeCH2;  //measure time between down and up
      channelFlag |= 1U << 1U;
    }
    
  }

  void RFInterface::measureCH3()
  {
    if ( digitalRead( GOKART_RF_CH3_PIN ) == HIGH )
    {
      risingTimeCH3 = micros(); //get time of pulse going up
    }
    else
    {
      fallingTimeCH3 = micros();  //get time of pulse going up
      upTimeCH3 = fallingTimeCH3 - risingTimeCH3;  //measure time between down and up
      channelFlag |= 1U << 2U;
      
    }
    
  }

  
  void RFInterface::enableFIRFilter(bool enable)
  {
    enableFilter_=enable;
  }

  bool RFInterface::updateConsistencyError(uint32_t upTimeCH1, uint32_t upTimeCH2, uint32_t upTimeCH3 ){
    if (  (upTimeCH1 > (GOKART_RF_STWHEEL_MIN - GOKART_RF_STWHEEL_DELTA)) && (upTimeCH1 < (GOKART_RF_STWHEEL_MAX + GOKART_RF_STWHEEL_DELTA)) )     {
      if (  (upTimeCH2 > (GOKART_RF_BRAKE_THROTTLE_MIN - GOKART_RF_BRAKE_THROTTLE_DELTA)) && (upTimeCH2 < (GOKART_RF_BRAKE_THROTTLE_MAX + GOKART_RF_BRAKE_THROTTLE_DELTA)) )     {
        if (  (upTimeCH3 > (GOKART_RF_EMERGENCY_MIN - GOKART_RF_EMERGENCY_DELTA)) && (upTimeCH3 < (GOKART_RF_EMERGENCY_MAX + GOKART_RF_EMERGENCY_DELTA)) )     {
          if (counter_error>0){
            counter_error--;
          }
          return true;
        }
      }
    }

    if (counter_error < RF_INTERFACE_ERROR_COUNTER_MAX*2){
      counter_error++;
    }
    return false;
  }

  bool RFInterface::isConsistency(){
    if (counter_error > RF_INTERFACE_ERROR_COUNTER_MAX){
      return false;
    }
    return true;
  }

  uint32_t RFInterface::escalon(uint32_t valorAntiguo, uint32_t valorActual){
    if (abs(valorAntiguo-valorActual)> RF_INTERFACE_DISCRETIZATION_SCALE ){
      return valorActual;
    }
    else
      return valorAntiguo;
  }

  bool RFInterface::update()
  {
    cli();
    overrun = (channelFlag != 7U);
    sei();

    if (overrun) return false;

    cli();
    channelFlag = 0U;
    sei();




    //Analizar consistencia de datos y aumentar/disminuir contador
    bool current_consistency= RFInterface::updateConsistencyError(upTimeCH1,upTimeCH2,upTimeCH3 );

    // Si los datos no son consistentes, entonces no actualizo el buffer de datos
    if (!current_consistency){
      return false;
    }

    if (enableFilter_){
      uptime_[0] = (uint32_t) ( (1-RF_INTERFACE_FIR_NEW_VALUE_WEIGHT)* upTimeCH1 + RF_INTERFACE_FIR_NEW_VALUE_WEIGHT*uptime_[0] );
      uptime_[1] = (uint32_t) ( (1-RF_INTERFACE_FIR_NEW_VALUE_WEIGHT)* upTimeCH2 + RF_INTERFACE_FIR_NEW_VALUE_WEIGHT*uptime_[1] );
      uptime_[2] = (uint32_t) ( (1-RF_INTERFACE_FIR_NEW_VALUE_WEIGHT)* upTimeCH3 + RF_INTERFACE_FIR_NEW_VALUE_WEIGHT*uptime_[2] );
    }
    else{
      uptime_[0] = upTimeCH1; //pulseIn(GOKART_RF_CH1_PIN, HIGH, 21000);
      uptime_[1] = upTimeCH2; //pulseIn(GOKART_RF_CH2_PIN, HIGH, 21000);
      uptime_[2] = upTimeCH3; //pulseIn(GOKART_RF_CH3_PIN, HIGH, 21000);
    }
    
    return true;

  }

  void RFInterface::getCommand(DataSerialization::GoKartCommand& cmd)
  {
    //Updatea canales del transmisor
    if (!update()) return;

    // Update time stamp
    cmd.stamp.data = millis();

    //Si se cumple la condicion de inconsistencia de datos, entonces seteo estado de emergencia.
    if (!RFInterface::isConsistency()){
      cmd.emergency.data = (uint8_t) 1;
      return;
    }

    //Stwheel match
    int medium_stwheel= round((GOKART_RF_STWHEEL_MIN + GOKART_RF_STWHEEL_MAX)/2);
    int left_max= medium_stwheel - round(GOKART_RF_STWHEEL_DELTA/2);
    int right_min= medium_stwheel + round(GOKART_RF_STWHEEL_DELTA/2);
    uint32_t old_stwheel=cmd.stwheel.data;

    if (uptime_[0]<= left_max)
    {
      cmd.stwheel.data = uptime_[0]<GOKART_RF_STWHEEL_MIN ? (uint8_t) 127 : (uint8_t) map(uptime_[0], GOKART_RF_STWHEEL_MIN, left_max, 127, 0);
    }
    else if (uptime_[0]>= right_min)
    {
      cmd.stwheel.data = uptime_[0]>GOKART_RF_STWHEEL_MAX ? (uint8_t) -128 : (uint8_t) map(uptime_[0], right_min, GOKART_RF_STWHEEL_MAX, 0, -128);
    }
    else
    {
      cmd.stwheel.data = (uint8_t) 0;
    }

    cmd.stwheel.data= RFInterface::escalon(old_stwheel, cmd.stwheel.data);

    //Brake & Throttle match
    int medium_brake_throttle= round((GOKART_RF_BRAKE_THROTTLE_MIN + GOKART_RF_BRAKE_THROTTLE_MAX)/2);
    int brake_max= medium_brake_throttle - round(GOKART_RF_BRAKE_THROTTLE_DELTA/2);
    int throttle_min= medium_brake_throttle + round(GOKART_RF_BRAKE_THROTTLE_DELTA/2);
    uint32_t old_throttle=cmd.throttle.data;
    uint32_t old_brake=cmd.brake.data;

    if (uptime_[1]<= brake_max)
    {
      cmd.brake.data = uptime_[1]<GOKART_RF_BRAKE_THROTTLE_MIN ? (uint8_t) 255 : (uint8_t) map(uptime_[1], GOKART_RF_BRAKE_THROTTLE_MIN, brake_max, 255, 0);
      cmd.throttle.data = (uint8_t) 0;
    }
    else if (uptime_[1]>= throttle_min)
    {
      cmd.throttle.data = uptime_[1]>GOKART_RF_BRAKE_THROTTLE_MAX ? (uint8_t) 255 : (uint8_t) map(uptime_[1], throttle_min, GOKART_RF_BRAKE_THROTTLE_MAX, 0, 255);
      cmd.brake.data = (uint8_t) 0;
    }
    else
    {
      cmd.throttle.data = (uint8_t) 0;
      cmd.brake.data = (uint8_t) 0;
    }

    cmd.throttle.data= RFInterface::escalon(old_throttle, cmd.throttle.data);
    cmd.brake.data= RFInterface::escalon(old_brake, cmd.brake.data);

    //Emergency match
    int medium_emergency= (GOKART_RF_EMERGENCY_MIN + GOKART_RF_EMERGENCY_MAX)/2;
    if ( uptime_[2]>medium_emergency )
    {
      cmd.emergency.data = (uint8_t) 1;
    }
    else
    {
      cmd.emergency.data = (uint8_t) 0;
    }
  }
}
