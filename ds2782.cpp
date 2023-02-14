#include "ds2782.h"
#include "Arduino.h"

int DS2782::_readVoltage(){
  uint16_t registerValue;
  Wire.beginTransmission(dsAddr);
  Wire.write(REG_VOLTAGE_DS);
  Wire.endTransmission();
  
  Wire.requestFrom(dsAddr, 2, true);
  registerValue = Wire.read()<<8;
  registerValue |= Wire.read();
  return((registerValue*4.88F)/8);
}

int DS2782::_readCurrent(){
  uint8_t sense_res_raw;
  int raw;
  int registerValue;
  Wire.beginTransmission(dsAddr);
  Wire.write(0x69);
  Wire.endTransmission();
  Wire.requestFrom(dsAddr, 1, true);
  sense_res_raw = Wire.read();
  raw = 1000/sense_res_raw;
  //не учитывается из за несовпадения реального установленного сопротивления и данных в EEPROM
  
  Wire.beginTransmission(dsAddr);
  Wire.write(REG_CURRENT_DS);
  Wire.endTransmission();
  Wire.requestFrom(dsAddr, 2, true);
  registerValue = Wire.read()<<8;
  registerValue |= Wire.read();
  return registerValue*0.1563F; 
}

int DS2782::_readTemperature(){
  int registerValue;
  Wire.beginTransmission(dsAddr);
  Wire.write(REG_TEMPERATURE_DS);
  Wire.endTransmission();
  Wire.requestFrom(dsAddr, 2, true);
  registerValue = Wire.read()<<8;
  registerValue |= Wire.read();
  registerValue = registerValue/32;
  return registerValue;
}

uint8_t DS2782::_readCapacity(){
  uint8_t registerValue;
  Wire.beginTransmission(dsAddr);
  Wire.write(REG_CAPACITY_DS);
  Wire.endTransmission();
  
  Wire.requestFrom(dsAddr, 1, true);
  registerValue = Wire.read();
  return registerValue;
}

uint8_t DS2782::_readAddress(){
	uint8_t registerValue;
	Wire.beginTransmission(dsAddr);
	Wire.write(REG_ADDRESS_DS);
	Wire.endTransmission();
	
	Wire.requestFrom(dsAddr, 1 ,true);
	registerValue = Wire.read();
	return registerValue;
}

String DS2782::GetData()
{	
	String comm = ",";
	String data = "";
	uint16_t voltage,c1v,fCap,capacity;
	uint8_t ser;
	int current, stat, date;
	float temperature;
	voltage = _readVoltage();
	current = _readCurrent();
	capacity = _readCapacity();
	temperature = _readTemperature()*0.125F;
	ser = 0;
	stat = 0;
	date = 0;
	c1v = voltage/4;	
	{
		data = voltage+comm+current+comm+temperature+comm+capacity+comm+c1v+comm+c1v+comm+c1v+comm+c1v+comm+ser+comm+stat+comm+date+comm+capacity;
	}
	return data;
}