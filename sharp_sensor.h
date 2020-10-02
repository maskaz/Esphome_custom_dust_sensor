#include "esphome.h"
class My_dust_Sensor : public PollingComponent, public Sensor {
 public:
  My_dust_Sensor() : PollingComponent(15000) {}  // period between updates, here 10s
  

  void setup() override {

    pinMode(D6, OUTPUT);     // sensor led pin         
    pinMode(A0, INPUT);      // output form sensor
    
   }

  void update() override {

    int o;
    int value = 0;
    int numReadings = 10;
    
    float dustDensity = 0;
    float voMeasured = 0;  



    for (o = 0; o < numReadings; o++){
    
    digitalWrite(D6,LOW);              // power on the LED
    delayMicroseconds(280);            // delay
    value = value + analogRead(A0);    // read ADC (sensor)
    delayMicroseconds(40);             // delay
    digitalWrite(D6,HIGH);             // turn the LED off
    delayMicroseconds(9680);           // delay
    //delay(1000);
    }
    
    value = value / numReadings;       // smoothing
    value = 0.17 * value - 0.1;        // calculate value (for GP2Y1010AU0F reads) 
  
  

    publish_state(value);              // publish
  }
};


