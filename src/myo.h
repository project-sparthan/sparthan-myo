
#ifndef myo_h
#define myo_h

#include "Arduino.h"
#include <BLEDevice.h>
#include "includes/myo_bluetooth.h"

#define TURN_OFF 0x00
#define TURN_ON 0x01

class armband
{
  public:
    void connect();

    void get_info();
    void get_firmware();

    void set_myo_mode(uint8_t, uint8_t, uint8_t);
    void vibration(uint8_t);
    void user_action(uint8_t);
    void set_sleep_mode(uint8_t);
    void unlock(uint8_t);

    BLERemoteCharacteristic* emg_notification(uint8_t);
    BLERemoteCharacteristic* imu_notification(uint8_t);
    BLERemoteCharacteristic* battery_notification(uint8_t);
    BLERemoteCharacteristic* gesture_notification(uint8_t);
    
    BLEClient* pClient;

    // Static status variables that can be used in callbacks
    static bool connected;
    static bool detected;
    static bool debug;

    uint16_t fw_major;
    uint16_t fw_minor;
    uint16_t fw_patch;
    uint16_t fw_hardware_rev;
    uint8_t fw_serial_number[6];
    uint16_t fw_unlock_pose;
    uint8_t fw_active_classifier_type;
    uint8_t fw_active_classifier_index;
    uint8_t fw_has_custom_classifier;
    uint8_t fw_stream_indicating;
    uint8_t fw_sku;
    uint8_t fw_reserved[7];
    uint8_t battery;
    
  private:
};

#endif
