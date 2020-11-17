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
  int sense_res;
  uint8_t sense_res_raw;
  int16_t registerValue;
  Wire.beginTransmission(dsAddr);
  Wire.write(0x69);
  Wire.endTransmission();
  Wire.requestFrom(dsAddr, 1, true);
  sense_res_raw = Wire.read();
  Wire.endTransmission();
  sense_res = 1000 / sense_res_raw;
  
  Wire.beginTransmission(dsAddr);
  Wire.write(REG_CURRENT_DS);
  Wire.endTransmission();
  Wire.requestFrom(dsAddr, 1, true);
  registerValue = Wire.read();
  Wire.endTransmission();
  registerValue = registerValue*(1563/sense_res);
  return registerValue;
}

int DS2782::_readTemperature(){
  int16_t registerValue;
  Wire.beginTransmission(dsAddr);
  Wire.write(REG_TEMPERATURE_DS);
  Wire.endTransmission();
  Wire.requestFrom(dsAddr, 1, true);
  registerValue = Wire.read();
  Wire.endTransmission();
  //Serial.println(registerValue);
  //registerValue = ((registerValue/32)*125)/100;
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