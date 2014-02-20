#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS1 2
#define ONE_WIRE_BUS2 3
#define TEMPERATURE_PRECISION 9

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire1(ONE_WIRE_BUS1);
OneWire oneWire2(ONE_WIRE_BUS2);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors1(&oneWire1);
DallasTemperature sensors2(&oneWire2);

// arrays to hold device addresses
DeviceAddress thermometer0, thermometer1, thermometer2,thermometer3,thermometer4,thermometer5;

void setup(void)
{
  // start serial port
  Serial.begin(9600);

  // Start up the library
  sensors1.begin();
  sensors2.begin();

  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  Serial.print(sensors1.getDeviceCount(), DEC);
  Serial.print(" devices on the bus 1 and ");
  Serial.print(sensors2.getDeviceCount(), DEC);
  Serial.println(" devices on the bus 2.");

  // assign address manually.  the addresses below will beed to be changed
  // to valid device addresses on your bus.  device address can be retrieved
  // by using either oneWire.search(deviceAddress) or individually via
  // sensors.getAddress(deviceAddress, index)
  //insideThermometer = { 0x28, 0x1D, 0x39, 0x31, 0x2, 0x0, 0x0, 0xF0 };
  //outsideThermometer   = { 0x28, 0x3F, 0x1C, 0x31, 0x2, 0x0, 0x0, 0x2 };

  // search for devices on the bus and assign based on an index.  ideally,
  // you would do this to initially discover addresses on the bus and then 
  // use those addresses and manually assign them (see above) once you know 
  // the devices on your bus (and assuming they don't change).
  // 
  // method 1: by index
  if (!sensors1.getAddress(thermometer0, 0)) Serial.println("Unable to find address for Device 0"); 
  if (!sensors1.getAddress(thermometer1, 1)) Serial.println("Unable to find address for Device 1"); 
  if (!sensors1.getAddress(thermometer2, 2)) Serial.println("Unable to find address for Device 2"); 
  if (!sensors2.getAddress(thermometer3, 0)) Serial.println("Unable to find address for Device 3"); 
  if (!sensors2.getAddress(thermometer4, 1)) Serial.println("Unable to find address for Device 4"); 
  if (!sensors2.getAddress(thermometer5, 2)) Serial.println("Unable to find address for Device 5"); 

  // method 2: search()
  // search() looks for the next device. Returns 1 if a new address has been
  // returned. A zero might mean that the bus is shorted, there are no devices, 
  // or you have already retrieved all of them.  It might be a good idea to 
  // check the CRC to make sure you didn't get garbage.  The order is 
  // deterministic. You will always get the same devices in the same order
  //
  // Must be called before search()
  //oneWire.reset_search();
  // assigns the first address found to insideThermometer
  //if (!oneWire.search(insideThermometer)) Serial.println("Unable to find address for insideThermometer");
  // assigns the seconds address found to outsideThermometer
  //if (!oneWire.search(outsideThermometer)) Serial.println("Unable to find address for outsideThermometer");

  // show the addresses we found on the bus
  Serial.print("Device 0 Address: ");
  printAddress(thermometer0);
  Serial.println();

  Serial.print("Device 1 Address: ");
  printAddress(thermometer1);
  Serial.println();
  
  Serial.print("Device 2 Address: ");
  printAddress(thermometer2);
  Serial.println();
   
  Serial.print("Device 3 Address: ");
  printAddress(thermometer3);
  Serial.println();
   
  Serial.print("Device 4 Address: ");
  printAddress(thermometer4);
  Serial.println();
   
  Serial.print("Device 5 Address: ");
  printAddress(thermometer5);
  Serial.println();

  // set the resolution to 9 bit
  sensors1.setResolution(thermometer0, TEMPERATURE_PRECISION);
  sensors1.setResolution(thermometer1, TEMPERATURE_PRECISION);
  sensors1.setResolution(thermometer2, TEMPERATURE_PRECISION);
  sensors2.setResolution(thermometer3, TEMPERATURE_PRECISION);
  sensors2.setResolution(thermometer4, TEMPERATURE_PRECISION);
  sensors2.setResolution(thermometer5, TEMPERATURE_PRECISION);


  Serial.print("Device 0 Resolution: ");
  Serial.print(sensors1.getResolution(thermometer0), DEC); 
  Serial.println();
  
  Serial.print("Device 1 Resolution: ");
  Serial.print(sensors1.getResolution(thermometer1), DEC); 
  Serial.println();
  
  Serial.print("Device 2 Resolution: ");
  Serial.print(sensors1.getResolution(thermometer2), DEC); 
  Serial.println();
  
  Serial.print("Device 3 Resolution: ");
  Serial.print(sensors2.getResolution(thermometer3), DEC); 
  Serial.println();
  
  Serial.print("Device 4 Resolution: ");
  Serial.print(sensors2.getResolution(thermometer4), DEC); 
  Serial.println();
  
  Serial.print("Device 5 Resolution: ");
  Serial.print(sensors2.getResolution(thermometer5), DEC); 
  Serial.println();
}

// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

// function to print the temperature for a device
void printTemperature(DeviceAddress deviceAddress, DallasTemperature sens)
{
  float tempC = sens.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.print(tempC);
  Serial.print(" Temp F: ");
  Serial.print(DallasTemperature::toFahrenheit(tempC));
}

// function to print a device's resolution
void printResolution(DeviceAddress deviceAddress, DallasTemperature sens)
{
  Serial.print("Resolution: ");
  Serial.print(sens.getResolution(deviceAddress));
  Serial.println();    
}

// main function to print information about a device
void printData(DeviceAddress deviceAddress, DallasTemperature sens)
{
  Serial.print("Device Address: ");
  printAddress(deviceAddress);
  Serial.print(" ");
  printTemperature(deviceAddress, sens);
  Serial.println();
}

void loop(void)
{ 
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors1.requestTemperatures();
  sensors2.requestTemperatures();
  Serial.println("DONE");

  // print the device information
  printData(thermometer0, sensors1);
  printData(thermometer1, sensors1);
  printData(thermometer2, sensors1);
  printData(thermometer3, sensors2);
  printData(thermometer4, sensors2);
  printData(thermometer5, sensors2);
}

