//1,屏幕显示部分=============================
#include "U8glib.h"
//2,传感器部分================================
#include <Wire.h>
#include "I2Cdev.h"
//温湿度
#include <AM2321.h>
AM2321 am2321;
//气压
#include "BMP085.h"
BMP085 barometer;
//光照
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_LOW, 12345);

const int ledPin =  5; 

#include "weather.h"
#include "oled.h"

void setup(void) {
  //初始化串口波特率
  Serial.begin(115200);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  //pinMode(buttonPin, INPUT);
  initWeatherSensor();

}

void loop(void) {
  updateSensorData();
  volcd();                       //调用显示库
}
