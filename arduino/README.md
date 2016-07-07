# EL5004: Teleoperación de Go Kart

## Código para Arduino

La plataforma de desarrollo corresponde a Arduino Mega 2560.

El software se ha estructurado como una librería de Arduino. Para más información ver [librerías de Arduino]( https://www.arduino.cc/en/Guide/Libraries).

El directorio para la instalación de librerías de Arduino suele ser:
* Linux: `~/Arduino/libraries`
* OS X: `Documents/Arduino/libraries`
* Windows: `My Documents\Arduino\libraries`

## Librerías

### Dynamixel

Esta librería emplea la conexión serial 1 de Arduino Mega (TX1, RX1). El pin usado para cambiar la dirección de comunicación es configurado en el método `begin` de la librería. 

#### Instalación

Copiar el directorio `DynamixelSerial1` en `~/Arduino/libraries`

### GoKart

Contiene el código para el control del vehiculo GoKart.

```
arduino
|
+-- GoKart [Librería principal]
|   |
|   +-- examples
|       |-- dynamixel_test [Test de motores Dynamixel]
|       |-- gokart_dynamixel [Test motores Dynamixel usando interfaz GoKart]
|       |-- gokart_integration [Desarrollo de software principal]
|       |-- gokart_lcd_test [Test de pantalla LCD]
|       |-- msg_test [Test de serialización de mensajes]
|       |-- rf_test [Test de comunicación RF]
|       |-- rf_test2 [Test de comunicación RF con salida serial más rápida]
|       |-- serial_test [Test de comunicación serial]
|
```
#### Instalación

Copiar el directorio `GoKart` en `~/Arduino/libraries`


#### Problemas conocidos

La librería para el control de motores Dynamixel solo funciona usando un baudrate de 1.000.000 baud/s.

## Datasheet EX106

[Documento PDF](http://www.hizook.com/files/users/3/EX-106_Robotis_Dynamixel_Servo_UserGuide.pdf)

