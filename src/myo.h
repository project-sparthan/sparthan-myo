
#ifndef myo_h
#define myo_h

#include "Arduino.h"
#include <BLEDevice.h>
#include "includes/myo_bluetooth.h"

class armband
{
    public:

    //Myo connection
    void scanCentral();
    void controlPeripheral(BLEDevice);
    void connectToPeripheral();
    
    // Myo commands
    void set_myo_mode(BLEDevice, uint8_t, uint8_t, uint8_t);
    void user_action(BLEDevice, uint8_t);
    void vibration(BLEDevice, uint8_t);
    void set_sleep_mode(BLEDevice, uint8_t);
    void unlock(BLEDevice, uint8_t);

    
    //Myo notifications
    void battery_notification(BLEDevice peripheral);
    void emg_notification(BLEDevice peripheral);
    void imu_notification(BLEDevice peripheral);
    void emg_callback(uint8_t pData);
    void imu_callback(uint8_t pData);
    void print_emg_sample(int8_t *sample, size_t len);
    void print_imu_orientation(myohw_imu_data_t *imu);
    
    // Static status variables that can be used in callbacks
    uint8_t battery;
    uint8_t emgdata0;
    uint8_t emgdata1;
    uint8_t emgdata2;
    uint8_t emgdata3;
    uint8_t imudata;
    

    private:
        /* data */

    };
   
#endif