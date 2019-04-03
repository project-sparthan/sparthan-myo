#include <myo.h>

/**********************************************************************
 * GFORCE EMG ARMBAND EXAMPLE
 * Author: Davide Asnaghi
 * Date: April 3rd 2019
 * Requirements: 
 *    - ESP32 arduino (https://github.com/espressif/arduino-esp32.git)
 *    - ESP32 Myo library (https://github.com/project-sparthan/sparthan-myo.git)
 **********************************************************************/

armband myo;                // Myo BLE Armband

/********************************************************************************************************
    SET CALLBACKS WHEN RECEIVING DATA
 ********************************************************************************************************/

void batteryCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {
  myo.battery = pData[0];
  Serial.print("Battery: ");
  Serial.println(myo.battery);
}

void imuCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {
  Serial.print ("EMG: \t");
  for (int i = 0; i < length; i++) {
    Serial.print(pData[i]);
    Serial.print("\t");
  }
  Serial.println(millis());
}

void emgCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {
  Serial.print ("IMU: \t");
  for (int i = 0; i < length; i++) {
    Serial.print(pData[i]);
    Serial.print("\t");
  }
  Serial.println(millis());
}

void gestureCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {
  // Print the gesture
  if (pData[0] == myohw_classifier_event_pose) {
    Serial.print ("Gesture: ");
    switch (pData[1]) {
      case myohw_pose_rest:
        Serial.println ("rest");
        break;
      case myohw_pose_fist:
        Serial.println ("fist");
        break;
      case myohw_pose_wave_in:
        Serial.println ("wave in");
        break;
      case myohw_pose_wave_out:
        Serial.println ("wave out");
        break;
      case myohw_pose_fingers_spread:
        Serial.println ("fingers spread");
        break;
      case myohw_pose_double_tap:
        Serial.println ("double tap");
        break;
      default:
        break;
    }
  }
}

/********************************************************************************************************
    ARDUINO SKETCH
 ********************************************************************************************************/

void setup()
{
  Serial.begin(115200);                             // Start serial interface for debugging
  
  Serial.println ("Connecting...");
  myo.connect();                                    // Connect to the myo
  Serial.println (" - Connected");
  delay(100);
  
  myo.set_myo_mode(myohw_emg_mode_send_emg,         // EMG mode
                   myohw_imu_mode_none,             // IMU mode
                   myohw_classifier_mode_enabled);  // Classifier mode

  myo.battery_notification(TURN_ON)->registerForNotify(batteryCallback);
  myo.gesture_notification(TURN_ON)->registerForNotify(gestureCallback);
}

void loop()
{
  // Detect disconnection
  if (!myo.connected) {
    Serial.println ("Device disconnected: reconnecting...");
    myo.connect();
    Serial.println (" - Connected");
    myo.set_myo_mode(myohw_emg_mode_send_emg,               // EMG mode
                     myohw_imu_mode_none,                   // IMU mode
                     myohw_classifier_mode_enabled);        // Classifier mode
    myo.battery_notification(TURN_ON)->registerForNotify(batteryCallback);
    myo.gesture_notification(TURN_ON)->registerForNotify(gestureCallback);
  }
  
  delay (10);
}
