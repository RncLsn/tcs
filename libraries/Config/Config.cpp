#include "Config.h"

// Every sensor has a unique address. They has been read in a previous moment
DeviceAddress devAdrr_bus2_no0 =  DEVADRR_BUS2_NO0;
DeviceAddress devAdrr_bus2_no1 =  DEVADRR_BUS2_NO1;
DeviceAddress devAdrr_bus2_no2 =  DEVADRR_BUS2_NO2;
DeviceAddress devAdrr_bus1_no0 =  DEVADRR_BUS1_NO0;
DeviceAddress devAdrr_bus1_no1 =  DEVADRR_BUS1_NO1;
DeviceAddress devAdrr_bus1_no2 =  DEVADRR_BUS1_NO2;

DeviceAddress_ptr getAddressByRoom(int room)
{
	switch (room)
	{
		case 0:
			return devAdrr_bus1_no0;
			break;
		
		case 1:
			return devAdrr_bus1_no1;
			break;
		
		case 2:
			return devAdrr_bus1_no2;
			break;
		
		case 3:
			return devAdrr_bus2_no0;
			break;
		
		case 4:
			return devAdrr_bus2_no1;
			break;
		
		case 5:
			return devAdrr_bus2_no2;
			break;
			
		default:
			#ifdef DEBUG
			Serial.println("Invalid room number passed as parameter to getAddressByRoom()");
			#endif
			return NULL;
	}
}
