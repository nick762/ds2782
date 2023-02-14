#ifndef DS2782_h
#define DS2782_h

#include <Wire.h>

#define dsAddr					0x34
#define REG_CAPACITY_DS			0x06//0x0e
#define REG_VOLTAGE_DS			0x0c//0x09
#define REG_CURRENT_DS			0x0e//0x0a
#define REG_TEMPERATURE_DS		0x0a//0x08
#define REG_ADDRESS_DS			0x7E

class DS2782{
	public:
		uint8_t _readCapacity();
		int _readVoltage();
		int _readCurrent();
		int _readTemperature();
		uint8_t _readAddress();
		String GetData();
};

#endif
		