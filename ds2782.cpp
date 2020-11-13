#include "ds2782.h"
#include "Arduino.h"

int DS2782::_readVoltage(){
  int8_t registerValue;
  Wire.beginTransmission(dsAddr);
  Wire.write(REG_VOLTAGE_DS);
  Wire.endTransmission();
  Wire.requestFrom(Addr, 1, true);
  registerValue = Wire.read();
  Wire.endTransmission();
  registerValue = (registerValue/32)*4800;
  return registerValue;
}

int DS2782::_readCurrent(){
  int8_t registerValue;
  Wire.beginTransmission(dsAddr);
  Wire.write(REG_CURRENT_DS);
  Wire.endTransmission();
  Wire.requestFrom(Addr, 1, true);
  registerValue = Wire.read();
  Wire.endTransmission();
  registerValue = (registerValue*1563)/100;//100000
  return registerValue;
}

int DS2782::_readTemperature(){
  int16_t registerValue;
  Wire.beginTransmission(dsAddr);
  Wire.write(REG_TEMPERATURE_DS);
  Wire.endTransmission();
  Wire.requestFrom(Addr, 1, true);
  registerValue = Wire.read();
  Wire.endTransmission();
  //Serial.println(registerValue);
  //registerValue = ((registerValue/32)*125)/100;
  return registerValue;
}

uint8_t DS2782::_readCapacity(){
  uint8_t registerValue;
  Wire.beginTransmission(dsAddr);
  Wire.write(REG_CURRENT_DS);
  Wire.endTransmission();
  Wire.requestFrom(Addr, 1, true);
  registerValue = Wire.read();
  Wire.endTransmission();
  return registerValue;
}