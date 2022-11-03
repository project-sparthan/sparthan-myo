#include "myo.h"
#include "ArduinoBLE.h"


// The remote service (Myo) we wish to connect to
const char* deviceServiceUuid = "d5060001-a904-deb9-4748-2c7f4a124842"; //  scans for Bluetooth® Low Energy peripherals
                                                                        //  until the one inside parenthesis is found.
/********************************************************************************************************
    Connection
 ********************************************************************************************************/

void armband::scanCentral(){

  // begin initialization (initializes the library)
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");

    while (1);
  }

  Serial.println("Bluetooth® Low Energy Central scan");

  // start scanning for peripheral
  BLE.scanForUuid(deviceServiceUuid);
}


void armband::controlPeripheral(BLEDevice peripheral) {
  Serial.println("- Connecting to peripheral device ...");
  //Serial.println(peripheral.connect());

  if(peripheral.connect()) {
    
  
    Serial.println("* Connected to peripheral device Myo armband!");
    Serial.println(" ");
  } else {
    Serial.println("* Connection to peripheral device Myo armband failed!");
    Serial.println(" ");
    return;
  }
  
  Serial.println("- Discovering peripheral device attributes...");
  if (peripheral.discoverAttributes()) {
    Serial.println("* Peripheral device attributes discovered!");
    Serial.println(" ");
  } else {
    Serial.println("* Peripheral device attributes discovery failed!");
    Serial.println(" ");
    peripheral.disconnect();
    return;
  }
}

void armband::connectToPeripheral(){
  
  // check if a peripheral has been discovered
  BLEDevice peripheral = BLE.available();

  if(peripheral) {

    // discovered a peripheral
    Serial.println("Peripheral device (Myo) found!");
    Serial.println("-----------------------");

    // print address
    Serial.print("Device MAC address:: ");
    Serial.println(peripheral.address());

    // print the local name, if present
    if (peripheral.hasLocalName()) {
      Serial.print("Device name: ");
      Serial.println(peripheral.localName());
    }

    // print the advertised service UUIDs, if present
    if (peripheral.hasAdvertisedServiceUuid()) {
      Serial.print("Advertised service UUID:  ");
      for (int i = 0; i < peripheral.advertisedServiceUuidCount(); i++) {
        Serial.print(peripheral.advertisedServiceUuid(i));
        Serial.print(" ");
      }
      Serial.println();
    }

    // print the RSSI
    Serial.print("RSSI: ");
    Serial.println(peripheral.rssi());

    Serial.println();
    // stop scanning
    BLE.stopScan();

    controlPeripheral(peripheral); 
  
    //battery_notification(peripheral);

    set_myo_mode(peripheral, myohw_emg_mode_send_emg,         // EMG mode
              myohw_imu_mode_none,                            // IMU mode
              myohw_classifier_mode_disabled);
     

    emg_notification(peripheral); 

    //imu_notification(peripheral);
              

     delay(1000);
}
}

/********************************************************************************************************
    Battery notification
 ********************************************************************************************************/

void armband::battery_notification(BLEDevice peripheral){
//const char* deviceServiceCharacteristicUuid  = "00002a19-0000-1000-8000-00805f9b34fb";
BLEService batteryService = peripheral.service("180f");

    if (batteryService) {
      // use the service
       Serial.println("Peripheral have battery service");
      BLECharacteristic batteryLevelCharacteristic = peripheral.characteristic("2a19");
      if (batteryLevelCharacteristic) {
        // use the characteristic
        Serial.println("Peripheral have battery level characteristic");
         while (peripheral.connected()) {
        // while the peripheral is connected 
        if(batteryLevelCharacteristic.canRead()){
          armband::battery = batteryLevelCharacteristic.read(); //  reads incoming data.
          batteryLevelCharacteristic.readValue(battery); //  stores incoming data in the value byte.
         // Serial.println(batteryLevelCharacteristic.readValue(value));
        Serial.print("Battery level:");       
        Serial.println(battery);
        }
  }
 
  Serial.println("- Peripheral device disconnected!");

      } else {
        Serial.println("Peripheral does NOT have battery level characteristic");
      }
    } else {
      Serial.println("Peripheral does NOT have battery service");
    }
}

/********************************************************************************************************
    EMG notification
 ********************************************************************************************************/

void armband::emg_notification(BLEDevice peripheral){
BLEService EmgDataService = peripheral.service("d5060005-a904-deb9-4748-2c7f4a124842");


    if (EmgDataService) {
      // use the service
       Serial.println("Peripheral have EMG service");

      
      BLECharacteristic EmgData0Characteristic = peripheral.characteristic("d5060105-a904-deb9-4748-2c7f4a124842");
      BLECharacteristic EmgData1Characteristic = peripheral.characteristic("d5060205-a904-deb9-4748-2c7f4a124842");
      BLECharacteristic EmgData2Characteristic = peripheral.characteristic("d5060305-a904-deb9-4748-2c7f4a124842");
      BLECharacteristic EmgData3Characteristic = peripheral.characteristic("d5060405-a904-deb9-4748-2c7f4a124842");
      
      if(EmgData0Characteristic && EmgData1Characteristic && EmgData2Characteristic && EmgData3Characteristic){
      // use the characteristics
        //Serial.println("Check if EMG can subscribe ");
        //Serial.println(EmgData0Characteristic.canSubscribe());
        //Serial.println("Peripheral have EmgData2 Characteristic");
        //Serial.println("Peripheral have EmgData3 Characteristic");

        while(peripheral.connected()){
            
         // EmgData0Characteristic.readValue(emgdata1);
          //Serial.print("EMG data :");       
         // Serial.println(EmgData0Characteristic.canWrite());
          if(EmgData0Characteristic.canSubscribe() && EmgData1Characteristic.canSubscribe() && EmgData2Characteristic.canSubscribe() && EmgData3Characteristic.canSubscribe()){
     
     /*     //Serial.println("EmgData0Characteristic.read");
            Serial.println(EmgData0Characteristic.subscribe());
            Serial.println(EmgData1Characteristic.subscribe());
            Serial.println(EmgData2Characteristic.subscribe());
            Serial.println(EmgData3Characteristic.subscribe());
  */  
          
            EmgData0Characteristic.subscribe();
            EmgData1Characteristic.subscribe();
            EmgData2Characteristic.subscribe();
            EmgData3Characteristic.subscribe();
       /*  
            armband::emgdata0= EmgData0Characteristic.read(); //  reads incoming data.
            armband::emgdata1= EmgData1Characteristic.read(); //  reads incoming data.
            armband::emgdata2= EmgData2Characteristic.read(); //  reads incoming data.
            armband::emgdata3= EmgData3Characteristic.read(); //  reads incoming data.
 
           
            armband::emgdata0= EmgData0Characteristic.subscribe(); 
            armband::emgdata1= EmgData1Characteristic.subscribe(); 
            armband::emgdata2= EmgData2Characteristic.subscribe();
            armband::emgdata3= EmgData3Characteristic.subscribe(); 
 */ 
            EmgData0Characteristic.readValue(emgdata0);
            EmgData1Characteristic.readValue(emgdata1);
            EmgData2Characteristic.readValue(emgdata2);
            EmgData3Characteristic.readValue(emgdata3);

  /*      
            Serial.print("EmgData 0 Characteristic read ");
            Serial.println(EmgData0Characteristic.readValue(emgdata0));
       
            Serial.print("EmgData 1 Characteristic read ");
            Serial.println(EmgData1Characteristic.readValue(emgdata1));

            Serial.print("EmgData 2 Characteristic read ");
            Serial.println(EmgData2Characteristic.readValue(emgdata2));

            Serial.print("EmgData 3 Characteristic read ");
            Serial.println(EmgData3Characteristic.readValue(emgdata3));
      */   
       // Serial.print("EMG data 0 :");       
        //Serial.println(emgdata0);
     
        emg_callback(emgdata0); // print EMG data
    
/*
         Serial.print("EMG data 1 :");       
         Serial.println(emgdata1);

         Serial.print("EMG data 2 :");       
         Serial.println(emgdata2);

         Serial.print("EMG data 3 :");       
         Serial.println(emgdata3);
   */         
          }
        }
      }else{
        Serial.println("Periphral does NOT have EMG charactersitics ");
      }
    } else {
      Serial.println("Peripheral does NOT have EMG service");
    }
}


void armband::print_emg_sample(int8_t *sample, size_t len)
{
  /*
  Serial.print(-100);
  Serial.print("\t");
  Serial.print(+100);
  Serial.print("\t");
*/
  for (int i = 0; i < len; i++)
  {
  
   Serial.print(sample[i]);
   Serial.print("\t");
  
  }
  Serial.println();
  
}

void armband::emg_callback(uint8_t pData)
{
  
  myohw_emg_data_t *emg_data = (myohw_emg_data_t *)pData;
  print_emg_sample(emg_data->sample1, myohw_num_emg_sensors);
  //Serial.println("");
}
/********************************************************************************************************
    IMU notification
 ********************************************************************************************************/
void armband::print_imu_orientation(myohw_imu_data_t *imu)
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


void armband::imu_callback(uint8_t pData)
{
  myohw_imu_data_t *imu_data = (myohw_imu_data_t *)pData;
  print_imu_orientation(imu_data);
  Serial.println();
}

void armband::imu_notification(BLEDevice peripheral){
  BLEService ImuDataService = peripheral.service("d5060002-a904-deb9-4748-2c7f4a124842");
 
    if (ImuDataService) {
      // use the service
       Serial.println("Peripheral have IMU service");
  
      BLECharacteristic IMUDataCharacteristic = peripheral.characteristic("d5060402-a904-deb9-4748-2c7f4a124842");

      if(IMUDataCharacteristic){
        Serial.println("Peripheral have IMU characteristic");

        while(peripheral.connected()){

          if(IMUDataCharacteristic.canSubscribe()){
              IMUDataCharacteristic.subscribe();
              armband::imudata= IMUDataCharacteristic.read();
              //Serial.print("reading imudata ");
             // Serial.print(imudata);
              imu_callback(imudata);
          }
        }
      }

}
}


/********************************************************************************************************
   COMMANDS
 ********************************************************************************************************/

void armband::set_myo_mode(BLEDevice peripheral, uint8_t emg_mode, uint8_t imu_mode, uint8_t clf_mode){
  BLEService ControlService = peripheral.service("d5060001-a904-deb9-4748-2c7f4a124842");

  if(ControlService){
    BLECharacteristic CommandCharacteristic = peripheral.characteristic("d5060401-a904-deb9-4748-2c7f4a124842");
    Serial.println("Peripheral have Myo mode command service");
    if(CommandCharacteristic){

      Serial.println("Peripheral have Myo mode command characteristic");
        while (peripheral.connected()) {
        // while the peripheral is connected 
        if(CommandCharacteristic.canWrite()){
       CommandCharacteristic.writeValue((byte)0x01); // write request or command sent
       CommandCharacteristic.writeValue((byte)0x03); // write request or command sent  
       CommandCharacteristic.writeValue(emg_mode); // write request or command sent 
       CommandCharacteristic.writeValue(imu_mode); // write request or command sent 
       CommandCharacteristic.writeValue(clf_mode); // write request or command sent 
     
        }
  }

    }else {
      Serial.println("Peripheral does NOT have Myo mode command characteristic");
    }
  }else{
    Serial.println("Peripheral does NOT have Myo mode command service");
  }
}

void armband::set_sleep_mode(BLEDevice peripheral, uint8_t sleep_mode){
 BLEService ControlService = peripheral.service("d5060001-a904-deb9-4748-2c7f4a124842");
 if(ControlService){
    BLECharacteristic CommandCharacteristic = peripheral.characteristic("d5060401-a904-deb9-4748-2c7f4a124842");
    Serial.println("Peripheral have sleep mode command service");
    if(CommandCharacteristic){

      Serial.println("Peripheral have sleep mode command characteristic");
        while (peripheral.connected()) {
        // while the peripheral is connected 
        if(CommandCharacteristic.canWrite()){
       CommandCharacteristic.writeValue(sleep_mode); // write request or command sent 
        }
  }
    }else {
      Serial.println("Peripheral does NOT have sleep mode command characteristic");
    }
  }else{
    Serial.println("Peripheral does NOT have sleep mode command service");
  }
}

void armband::vibration(BLEDevice peripheral, uint8_t duration){
 BLEService ControlService = peripheral.service("d5060001-a904-deb9-4748-2c7f4a124842");
 if(ControlService){
    BLECharacteristic CommandCharacteristic = peripheral.characteristic("d5060401-a904-deb9-4748-2c7f4a124842");
    Serial.println("Peripheral have vibration command service");
    if(CommandCharacteristic){

      Serial.println("Peripheral have vibration command characteristic");
        while (peripheral.connected()) {
        // while the peripheral is connected 
        if(CommandCharacteristic.canWrite()){
        CommandCharacteristic.writeValue((byte)0x03); // write request or command sent 
        CommandCharacteristic.writeValue((byte)0x01); // write request or command sent 
        CommandCharacteristic.writeValue(duration); // write request or command sent 
        }
  }
    }else {
      Serial.println("Peripheral does NOT have vibration command characteristic");
    }
  }else{
    Serial.println("Peripheral does NOT have vibration command service");
  }
}

void armband::user_action(BLEDevice peripheral, uint8_t action_type){
 BLEService ControlService = peripheral.service("d5060001-a904-deb9-4748-2c7f4a124842");
 if(ControlService){
    BLECharacteristic CommandCharacteristic = peripheral.characteristic("d5060401-a904-deb9-4748-2c7f4a124842");
    Serial.println("Peripheral have user action cammand  service");
    if(CommandCharacteristic){

      Serial.println("Peripheral have user action cammand  characteristic");
        while (peripheral.connected()) {
        // while the peripheral is connected 
        if(CommandCharacteristic.canWrite()){
       // CommandCharacteristic.writeValue(myohw_command_user_action); // write request or command sent 
        CommandCharacteristic.writeValue((byte)0x01); // write request or command sent 
       CommandCharacteristic.writeValue(action_type); // write request or command sent 
        }
  }
    }else {
      Serial.println("Peripheral does NOT have user action cammand characteristic");
    }
  }else{
    Serial.println("Peripheral does NOT have user action cammand service");
  }
}

void armband::unlock(BLEDevice peripheral, uint8_t unlock_mode){
 BLEService ControlService = peripheral.service("d5060001-a904-deb9-4748-2c7f4a124842");
 if(ControlService){
    BLECharacteristic CommandCharacteristic = peripheral.characteristic("d5060401-a904-deb9-4748-2c7f4a124842");
    Serial.println("Peripheral have unlock command  service");
    if(CommandCharacteristic){

      Serial.println("Peripheral have unlock command characteristic");
        while (peripheral.connected()) {
        // while the peripheral is connected 
        if(CommandCharacteristic.canWrite()){
        CommandCharacteristic.writeValue((byte)0x0a); // write request or command sent 
        CommandCharacteristic.writeValue((byte)0x01); // write request or command sent 
        CommandCharacteristic.writeValue(unlock_mode); // write request or command sent 
        }
  }
    }else {
      Serial.println("Peripheral does NOT have unlock command characteristic");
    }
  }else{
    Serial.println("Peripheral does NOT have unlock command service");
  }
}
