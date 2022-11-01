#include <myo.h>


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

