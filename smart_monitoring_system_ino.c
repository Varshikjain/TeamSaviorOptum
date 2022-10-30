
#include <OneWire.h>
#include <Wire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

const int SENSOR_PIN = 13; // Arduino pin connected to DS18B20 sensor's DQ pin

OneWire oneWire(SENSOR_PIN);         // setup a oneWire instance
DallasTemperature sensors(&oneWire); // pass oneWire to DallasTemperature library
LiquidCrystal_I2C lcd(0x3F, 16, 2);  // I2C address 0x27, 16 column and 2 rows


double alpha=0.75;
int period=20;
double refresh=0.0;
float tempCelsius;    // temperature in Celsius

void setup()
{
  pinMode(A0,INPUT);
  sensors.begin();    // initialize the sensor
  lcd.init(); // initialize the lcd
  lcd.init();
  lcd.backlight();    // open the backlight 
  lcd.clear();
  lcd.setCursor(0,0);
}

void loop()
{
  static double oldValue=0;
  static double oldrefresh=0;

  int beat=analogRead(A0);
  
  double value=alpha*oldValue+(0-alpha)*beat;

  
  refresh=value-oldValue;
  sensors.requestTemperatures();             // send the command to get temperatures
  tempCelsius = sensors.getTempCByIndex(0);  // read temperature in Celsius

  lcd.clear();
  lcd.setCursor(0, 0);       // start to print at the first row
  lcd.print("Body:  ");// print the temperature in Celsius
  lcd.print(tempCelsius);
  lcd.print((char)223);      // print  character
  lcd.print("C");
  lcd.setCursor(0, 1);       // start to print at the second row
  lcd.print("Heart: "); 
  lcd.print(beat/10);
  oldValue=value;
  oldrefresh=refresh;
  delay(period*10);
  

  delay(500);
}
