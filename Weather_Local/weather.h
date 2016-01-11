float sensor_tem, sensor_hum, sensor_alt, sensor_pre, sensor_lux; //温度、湿度、海拔、气压、光照 

char s_data;

void initWeatherSensor() {
  //初始化-气压   
  barometer.initialize();   
  Serial.println(barometer.testConnection() ? "BMP085 successful" : "BMP085 failed");   
  if(barometer.testConnection())
    //volcdsetup("-BMP085 OK-",10,15);
  //else
    //volcdsetup("-BMP085 failed-",10,15);
  delay(1000);
  //初始化-光照   
  Serial.println(tsl.begin() ? "TSL2561 successful" : "TSL2561 failed");   
  tsl.enableAutoGain(true);                                  // 在1x 与16x 增益中切换  
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);      //13MS的采样速度 

  if(barometer.testConnection())
    //volcdsetup("-TSL2561 OK-",10,15);
  //else
    //volcdsetup("-TSL2561 failed-",10,15);
  delay(1000);  
}



void updateSensorData() {
  //获取温湿度============================================== 
  am2321.read();   
  sensor_tem = am2321.temperature / 10.0;   
  sensor_hum = am2321.humidity / 10.0;   

  //获取气压、海拔========================================== 
  barometer.setControl(BMP085_MODE_TEMPERATURE);   
  unsigned long lastMicros = micros();      
  //先获取温度，用来补偿气压值  
  while (micros() - lastMicros < barometer.getMeasureDelayMicroseconds());    
  barometer.getTemperatureC();  
  barometer.setControl(BMP085_MODE_PRESSURE_3);   
  //得出气压值  
  while (micros() - lastMicros < barometer.getMeasureDelayMicroseconds());  
  sensor_pre = barometer.getPressure()/1000.0;  
  //结合气压值，以标准大气压得出海拔值  
  sensor_alt = barometer.getAltitude(sensor_pre);    

  //获取光照===============================================    
//  sensors_event_t event;   
//  tsl.getEvent(&event);   
//  (event.light)?  sensor_lux = event.light : Serial.println("Sensor overload"); 

    sensor_lux = map(analogRead(A0), 0, 1023, 0, 255);
}


void updateWeatherData() {
  if(s_data == '0') {
    digitalWrite(ledPin, LOW);      
  }
  else if(s_data == '1') {
    digitalWrite(ledPin, HIGH);
  }

 // voCC3000_ping(0);
 // voCC3000_rec();
}


