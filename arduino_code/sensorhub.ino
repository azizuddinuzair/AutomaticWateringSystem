// Arduino 1 (Sensor Hub)
#include <string.h>

#include <dht.h>
dht DHT;
#define DHT11_PIN 5


//Soil Moisture
const int sensorpin = A0;
const int sensorpower = 8;
int sensorRaw;
int soilMoisturePercent;


const int AirValue = 520;  
const int WaterValue = 260;

float waterVal = 0;

void setup() {
  pinMode(sensorpower, OUTPUT);
  digitalWrite(sensorpower, LOW);
 
  Serial.begin(9600);
}


unsigned long prevMillis = 0;
unsigned long currMillis;


void loop() {
 
  currMillis = millis();


  //Read in the waterLevel from other arduino
  if (Serial.available()){
    String line = Serial.readStringUntil('\n');  
    waterVal = line.toFloat();              
  }
 
  if (currMillis - prevMillis > 1000){
    prevMillis = currMillis;
   

    // soil Moisture Sensor
    digitalWrite(sensorpower, HIGH);


    sensorRaw = analogRead(sensorpin);
    digitalWrite(sensorpower, LOW);
   
    // changes the moisture level to a percentage
    soilMoisturePercent = map(sensorRaw, AirValue, WaterValue, 0, 100);
   
    // moisture level within the range of 0-100
    soilMoisturePercent = constrain(soilMoisturePercent, 0, 100);


    // reads in value from DHT which gives temp and humidity
    int chk = DHT.read11(DHT11_PIN);


    // sends all values to other arduinos.
    Serial.print(DHT.temperature);
    Serial.print(",");
    Serial.print(DHT.humidity);
    Serial.print(",");
    Serial.print(soilMoisturePercent);
    Serial.print(",");
    Serial.println(waterVal);\
  }
}

