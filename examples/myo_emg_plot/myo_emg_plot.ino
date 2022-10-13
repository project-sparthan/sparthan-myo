#include <myo.h>

/**********************************************************************
 * MYO EMG ARMBAND EXAMPLE
 * Author: Davide Asnaghi
 * Date: April 3rd 2019
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

void print_emg_sample(int8_t *sample, size_t len)
{
  for (int i = 0; i < len; i++)
  {
    Serial.print(sample[i]);
    Serial.print("\t");
  }
  Serial.println();
}

void emg_callback(BLERemoteCharacteristic *pBLERemoteCharacteristic, uint8_t *pData, size_t length, bool isNotify)
{
  myohw_emg_data_t *emg_data = (myohw_emg_data_t *)pData;
  print_emg_sample(emg_data->sample1, myohw_num_emg_sensors);
  print_emg_sample(emg_data->sample2, myohw_num_emg_sensors);
}

void myo_connect()
{
  Serial.println("Connecting...");
  myo.connect();
  Serial.println(" - Connected");
  delay(100);

  myo.set_myo_mode(myohw_emg_mode_send_emg,         // EMG mode
                   myohw_imu_mode_none,             // IMU mode
                   myohw_classifier_mode_disabled); // Classifier mode

  myo.emg_notification(TURN_ON)->registerForNotify(emg_callback);
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
