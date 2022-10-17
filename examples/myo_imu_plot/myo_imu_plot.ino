#include <myo.h>

/**********************************************************************
 * MYO IMU ARMBAND EXAMPLE
 * Author: Davide Asnaghi
 * Date: October 12th 2022
 * Requirements:
 *    - ESP32 arduino (https://github.com/espressif/arduino-esp32.git)
 *    - ESP32 Myo library (https://github.com/project-sparthan/sparthan-myo.git)
 * Notes:
 * This sketch is intended to be used with the Arduino IDE serial
 * plotter, it produces visualization for the data coming from the MYO
 * armband. Flash the example sketch onto a board, then open the
 * "Serial Plotter" tool to see the data in real time
 **********************************************************************/

armband myo; // Myo BLE Armband

void print_imu_orientation(myohw_imu_data_t *imu)
{
  Serial.print(imu->orientation.x);
  Serial.print("\t");
  Serial.print(imu->orientation.y);
  Serial.print("\t");
  Serial.print(imu->orientation.z);
  Serial.print("\t");
  Serial.print(imu->orientation.w);
  Serial.print("\t");
}

void imu_callback(BLERemoteCharacteristic *pBLERemoteCharacteristic, uint8_t *pData, size_t length, bool isNotify)
{
  myohw_imu_data_t *imu_data = (myohw_imu_data_t *)pData;
  print_imu_orientation(imu_data);
  Serial.println();
}

void myo_connect()
{
  Serial.println("Connecting...");
  myo.connect();
  Serial.println(" - Connected");
  delay(100);

  myo.set_myo_mode(myohw_emg_mode_none,             // EMG mode
                   myohw_imu_mode_send_data,        // IMU mode
                   myohw_classifier_mode_disabled); // Classifier mode

  myo.imu_notification(TURN_ON)->registerForNotify(imu_callback);
}

/********************************************************************************************************
    ARDUINO SKETCH
 ********************************************************************************************************/

void setup()
{
  // Start the serial interface
  Serial.begin(115200);
}

void loop()
{
  // Detect disconnection
  if (!myo.connected)
  {
    myo_connect();
  }

  delay(10);
}
