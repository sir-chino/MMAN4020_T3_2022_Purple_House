#include <OneWire.h>
#include <DallasTemperature.h>

// Number of temperature devices found
int numberOfDevices = 0;

// We'll use this variable to store a found device address
DeviceAddress tempDeviceAddress; 
DeviceAddress wireAddresses[4];

// Function used to check if sensors are connected and returns how many are connected.
int sensor_check() {
  // Start up the library
  sensors.begin();

  // Grab a count of devices on the wire
  numberOfDevices = sensors.getDeviceCount();
  
  // locate devices on the bus
  Serial.println("Searching for temperature sensors...");
  Serial.print("Found ");
  Serial.print(numberOfDevices, DEC);
  Serial.println(" devices.");

  // Loop through each device, print out address
  for (int i = 0; i < numberOfDevices; i++) {
    // Search the wire for address
    if (sensors.getAddress(tempDeviceAddress, i)) {
      Serial.print("Found device ");
      Serial.print(i, DEC);
      Serial.print(" with address: ");
      printAddress(tempDeviceAddress);
      Serial.println();
      memcpy(wireAddresses[i], tempDeviceAddress, 8);
    } else {
      Serial.print("Found ghost device at ");
      Serial.print(i, DEC);
      Serial.print(" but could not detect address. Check power and cabling");
    }
  }

  return numberOfDevices;  
}

// Function to print a device address
void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i=0; i < 8; i++) {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

// Function to return temperatures of all connected sensors
void get_sensors_data(float* temperatures) {
  sensors.requestTemperatures(); // Send the command to get temperatures
  
  // Loop through each device, print out temperature data
  for (int i=0; i < numberOfDevices; i++) {
    temperatures[i] = sensors.getTempC(wireAddresses[i]);
  }
}
