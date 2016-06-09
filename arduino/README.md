# Código para Arduino

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
|       |-- rf_test [Test de comunicación RF]
|       |-- gokart_integration [Desarrollo de software principal]
|
```
### Problemas conocidos

La librería para el control de motores Dynamixel solo funciona usando un baudrate de 1.000.000 baud/s.
