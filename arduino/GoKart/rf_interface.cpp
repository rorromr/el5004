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

    enableFilter_=true;

    for (uint8_t i=0; i <= RF_INTERFACE_BUFFER_SIZE; ++i){
      buffer_uptimeCH1[i]=0UL;
      buffer_uptimeCH2[i]=0UL;
      buffer_uptimeCH3[i]=0UL;
    }

    counter_buffer= 0;
    counter_error= RF_INTERFACE_ERROR_COUNTER_MAX*2;

  }

  bool RFInterface::init()
  {
    // @TODO Verify status! data received?
    while (true){
      if (RFInterface::isConsistency()){
        return true;
      }
    }
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
    }
  }

  void RFInterface::enableFilter(bool enable)
  {
    enableFilter_=enable;
  }

  uint32_t RFInterface::meanBuffer(uint32_t *buffer){
    uint32_t result = 0;
    for (uint8_t i=0; i < RF_INTERFACE_BUFFER_SIZE; ++i){
      result += buffer[i];
    }
    result = (uint32_t) (1.0f/RF_INTERFACE_BUFFER_SIZE*result);
    return result;
  }

  bool RFInterface::updateConsistencyError(uint32_t upTimeCH1, uint32_t upTimeCH2, uint32_t upTimeCH3 ){
    if (  (upTimeCH1 < (GOKART_RF_STWHEEL_MIN - GOKART_RF_STWHEEL_DELTA)) || (upTimeCH1 > (GOKART_RF_STWHEEL_MAX + GOKART_RF_STWHEEL_DELTA)) )     {
      if (  (upTimeCH2 < (GOKART_RF_BRAKE_THROTTLE_MIN - GOKART_RF_BRAKE_THROTTLE_DELTA)) || (upTimeCH2 > (GOKART_RF_BRAKE_THROTTLE_MAX + GOKART_RF_BRAKE_THROTTLE_DELTA)) )     {
        if (  (upTimeCH3 < (GOKART_RF_EMERGENCY_MIN - GOKART_RF_EMERGENCY_DELTA)) || (upTimeCH3 > (GOKART_RF_EMERGENCY_MAX + GOKART_RF_EMERGENCY_DELTA)) )     {
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

  void RFInterface::update()
  {
    //Analizar consistencia de datos y aumentar/disminuir contador
    bool current_consistency= RFInterface::updateConsistencyError(uint32_t upTimeCH1, uint32_t upTimeCH2, uint32_t upTimeCH3 );

    // Si los datos no son consistentes, entonces no actualizo el buffer de datos
    if (!current_consistency){
      return;
    }

    uptime_[0] = upTimeCH1; //pulseIn(GOKART_RF_CH1_PIN, HIGH, 21000);
    uptime_[1] = upTimeCH2; //pulseIn(GOKART_RF_CH2_PIN, HIGH, 21000);
    uptime_[2] = upTimeCH3; //pulseIn(GOKART_RF_CH3_PIN, HIGH, 21000);

    //Reiniciar contador de buffer ("puntero"), de ser necesario
    if (counter_buffer == RF_INTERFACE_BUFFER_SIZE)
    {
      counter_buffer = 0;
    }

    //Actualizar buffer con valor nuevo y eliminando el mas antiguo
    buffer_uptimeCH1[counter_buffer]=uptime_[0];
    buffer_uptimeCH2[counter_buffer]=uptime_[1];
    buffer_uptimeCH3[counter_buffer]=uptime_[2];

    //Actualizar valor final del buffer => Ponderacion entre promedio y valor entrante, ponderacion dependiente del DEFINE.
    if (enableFilter_){
      buffer_uptimeCH1[RF_INTERFACE_BUFFER_SIZE] = (uint32_t) ( (1-RF_INTERFACE_BUFFER_NEW_VALUE_WEIGHT)* RFInterface::meanBuffer(buffer_uptimeCH1) + RF_INTERFACE_BUFFER_NEW_VALUE_WEIGHT*uptime_[0] );
      buffer_uptimeCH2[RF_INTERFACE_BUFFER_SIZE] = (uint32_t) ( (1-RF_INTERFACE_BUFFER_NEW_VALUE_WEIGHT)* RFInterface::meanBuffer(buffer_uptimeCH2) + RF_INTERFACE_BUFFER_NEW_VALUE_WEIGHT*uptime_[1] );
      buffer_uptimeCH3[RF_INTERFACE_BUFFER_SIZE] = (uint32_t) ( (1-RF_INTERFACE_BUFFER_NEW_VALUE_WEIGHT)* RFInterface::meanBuffer(buffer_uptimeCH3) + RF_INTERFACE_BUFFER_NEW_VALUE_WEIGHT*uptime_[2] );
    }
    else{
      buffer_uptimeCH1[RF_INTERFACE_BUFFER_SIZE] = (uint32_t) uptime_[0];
      buffer_uptimeCH2[RF_INTERFACE_BUFFER_SIZE] = (uint32_t) uptime_[1];
      buffer_uptimeCH3[RF_INTERFACE_BUFFER_SIZE] = (uint32_t) uptime_[2];
    }

    //ACtualizar contador
    counter_buffer++;

  }


  void RFInterface::getCommand(DataSerialization::GoKartCommand& cmd)
  {
    update(); //Updatea canales del transmisor

    //Si se cumple la condicion de inconsistencia de datos, entonces seteo estado de emergencia.
    if (!RFInterface::isConsistency()){
      cmd.emergency.data = (uint8_t) 1;
      return;
    }

    //Stwheel match
    int medium_stwheel= round((GOKART_RF_STWHEEL_MIN + GOKART_RF_STWHEEL_MAX)/2);
    int left_max= medium_stwheel - round(GOKART_RF_STWHEEL_DELTA/2);
    int right_min= medium_stwheel + round(GOKART_RF_STWHEEL_DELTA/2);
    if (buffer_uptimeCH1[RF_INTERFACE_BUFFER_SIZE]<= left_max)
    {
      cmd.stwheel.data = buffer_uptimeCH1[RF_INTERFACE_BUFFER_SIZE]<GOKART_RF_STWHEEL_MIN ? (uint8_t) -128 : (uint8_t) map(buffer_uptimeCH1[RF_INTERFACE_BUFFER_SIZE], GOKART_RF_STWHEEL_MIN, left_max, -128, 0);
    }
    else if (buffer_uptimeCH1[RF_INTERFACE_BUFFER_SIZE]>= right_min)
    {
      cmd.stwheel.data = buffer_uptimeCH1[RF_INTERFACE_BUFFER_SIZE]>GOKART_RF_STWHEEL_MAX ? (uint8_t) 127 : (uint8_t) map(buffer_uptimeCH1[RF_INTERFACE_BUFFER_SIZE], right_min, GOKART_RF_STWHEEL_MAX, 0, 127);
    }
    else
    {
      cmd.stwheel.data = (uint8_t) 0;
    }


    //Brake & Throttle match
    int medium_brake_throttle= round((GOKART_RF_BRAKE_THROTTLE_MIN + GOKART_RF_BRAKE_THROTTLE_MAX)/2);
    int brake_max= medium_brake_throttle - round(GOKART_RF_BRAKE_THROTTLE_DELTA/2);
    int throttle_min= medium_brake_throttle + round(GOKART_RF_BRAKE_THROTTLE_DELTA/2);
    if (buffer_uptimeCH2[RF_INTERFACE_BUFFER_SIZE]<= brake_max)
    {
      cmd.brake.data = buffer_uptimeCH2[RF_INTERFACE_BUFFER_SIZE]<GOKART_RF_BRAKE_THROTTLE_MIN ? (uint8_t) 255 : (uint8_t) map(buffer_uptimeCH2[RF_INTERFACE_BUFFER_SIZE], GOKART_RF_BRAKE_THROTTLE_MIN, brake_max, 255, 0);
      cmd.throttle.data = (uint8_t) 0;
    }
    else if (buffer_uptimeCH2[RF_INTERFACE_BUFFER_SIZE]>= throttle_min)
    {
      cmd.throttle.data = buffer_uptimeCH2[RF_INTERFACE_BUFFER_SIZE]>GOKART_RF_BRAKE_THROTTLE_MAX ? (uint8_t) 255 : (uint8_t) map(buffer_uptimeCH2[RF_INTERFACE_BUFFER_SIZE], throttle_min, GOKART_RF_BRAKE_THROTTLE_MAX, 0, 255);
      cmd.brake.data = (uint8_t) 0;
    }
    else{
      cmd.throttle.data = (uint8_t) 0;
      cmd.brake.data = (uint8_t) 0;
    }


    //Emergency match
    int medium_emergency= (GOKART_RF_EMERGENCY_MIN + GOKART_RF_EMERGENCY_MAX)/2;
    if ( buffer_uptimeCH3[RF_INTERFACE_BUFFER_SIZE]>medium_emergency )
    {
      cmd.emergency.data = (uint8_t) 1;
    }
    else
    {
      cmd.emergency.data = (uint8_t) 0;
    }
  }
}
