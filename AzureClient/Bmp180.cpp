#include "Bmp180.h"


void Bmp180::initialise(){
  if (initialised) { return; }  
  bmp180.begin(); 
  delay(100);  
  initialised = true;
}

void Bmp180::measure(){
  const int numberOfSamples = 4;
  int sampleCount = 0, sampleAttempts = 0;

  initialise();

  temperature = pressure = humidity = 0;
   
  while (sampleCount < numberOfSamples && sampleAttempts < 10) { // no more than 10 attempts to read sensor

    sensors_event_t event;
    bmp180.getEvent(&event);
   
    if (event.pressure) {      
      pressure += (int)event.pressure;    
      float temperature;
      bmp180.getTemperature(&temperature);
      temperature += temperature;

      sampleCount++;
      delay(100);  
    }
    
    sampleAttempts++;
  }   
  
  temperature /= sampleCount;
  pressure /= sampleCount;  
  humidity /= sampleCount;  
}

