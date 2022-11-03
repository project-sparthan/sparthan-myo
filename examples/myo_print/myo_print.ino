#include <myo.h>

/**********************************************************************
 * Myo EMG ARMBAND EXAMPLE
 * Author: Rayane Belaid
 * Date: October 18th 2022
 * Requirements: 
 *    - Arduino nano 33 IoT (https://docs.arduino.cc/hardware/nano-33-iot)
 *    - ArduinoBLE library (https://github.com/arduino-libraries/ArduinoBLE)
 **********************************************************************/

armband myo;                // Myo BLE Armband


/********************************************************************************************************
    ARDUINO SKETCH
 ********************************************************************************************************/

void setup()
{
  // Start the serial interface
  Serial.begin(115200);
 
// start scanning 
 myo.scanCentral();


}

void loop()
{
  


// connect to myo 
myo.connectToPeripheral();

  delay(1000);
}

