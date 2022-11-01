
#ifndef myo_h
#define myo_h

#include "Arduino.h"
#include <BLEDevice.h>
#include "includes/myo_bluetooth.h"

class armband
{
    public:

    
    void scanCentral();
    void controlPeripheral(BLEDevice);
    void connectToPeripheral();
    
    void updateStatus();
    void connect();

    // Static status variables that can be used in callbacks
    static bool connected;
    static bool detected;
    static bool debug;

    void battery_notification(BLEDevice peripheral);
    void emg_notification(BLEDevice peripheral);
    void imu_notification(BLEDevice peripheral);
    void emg_callback(uint8_t pData);
    void imu_callback(uint8_t pData);
    void print_emg_sample(int8_t *sample, size_t len);
    void set_myo_mode(BLEDevice, uint8_t, uint8_t, uint8_t);
    void print_imu_orientation(myohw_imu_data_t *imu);
    

    uint8_t battery;
    uint8_t emgdata0;
    uint8_t emgdata1;
    uint8_t emgdata2;
    uint8_t emgdata3;
    uint8_t imudata;
    uint8_t length = 2;

    private:
        /* data */

    };
   
#endif