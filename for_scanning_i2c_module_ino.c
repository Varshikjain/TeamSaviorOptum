
#include <Wire.h>



void setup()
{
Wire.begin();
Serial.begin(9600);
Serial.println("\nI2C Scanner");
}


void loop()
{

byte error, address;
int Devices;
Serial.println("\nScanning for the address");
Devices = 0;

for(address = 1; address < 127; address++ )
{

Wire.beginTransmission(address);
error = Wire.endTransmission();

if (error == 0)
{
Serial.print("\nI2C device found at address 0x");
if (address<16)
Serial.print("0");
Serial.print(address,HEX);
Serial.println("  *");
Serial.print("Copy this address and paste on the main code");
Devices++;
}

else if (error==4)
{
Serial.print("Error at address 0x,Please check the connection properly or device may be defective");

if (address<16)
Serial.print("0");
Serial.println(address,HEX);
}
}

if (Devices == 0)
Serial.println("No I2C devices found\n");

else
Serial.println("\nMission accomplishment");
Serial.println("********************************************************************");
delay(5000);          
}