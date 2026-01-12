// Arduino 3 (Display Unit)
#include <LiquidCrystal.h>


// LCD pins
const int rs = 12, en = 11, d4 = 8, d5 = 7, d6 = 6, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


// LED pins
const int greenLED = 4;
const int redLED   = 3;
const int blueLED  = 2;


String incomingData;


// Sensor values received from Main Controller
float tempValue = 0;
float humidityValue = 0;
float soilValue = 0;
float waterDistance = 0;


unsigned long lastUpdate = 0;
const unsigned long updateInterval = 1000;


void setup() {
  Serial.begin(9600);

  // no data sent yet
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Waiting data...");


  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);


  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);
  digitalWrite(blueLED, LOW);
}


void loop() {
  if (Serial.available()) {

    incomingData = Serial.readStringUntil('\n');  


    int firstValue = incomingData.indexOf(',');
    int secondValue = incomingData.indexOf(',', firstValue + 1);
    int thirdValue = incomingData.indexOf(',', secondValue + 1);


    if (firstValue > 0 && secondValue > 0 && thirdValue > 0) {
      tempValue       = incomingData.substring(0, firstValue).toFloat();
      humidityValue   = incomingData.substring(firstValue + 1, secondValue).toFloat();
      soilValue       = incomingData.substring(secondValue + 1, thirdValue).toFloat();
      waterDistance   = incomingData.substring(thirdValue + 1).toFloat();

      // send the soil data to water pump
      Serial.println(soilValue);
    }
  }


  if (millis() - lastUpdate >= updateInterval) {
    lastUpdate = millis();
    updateDisplay();
  }
}


void updateDisplay() {
  lcd.clear();

  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);
  digitalWrite(blueLED, LOW);


  String mood = "";
  String waterStatus = "";


  if (waterDistance >= 10) {
    waterStatus = "Refill Bottle!!!";
    digitalWrite(blueLED, HIGH);
  }
  else{
    waterStatus = "Water Ready!!!";
    digitalWrite(blueLED, LOW);
  }


  if (soilValue < 30) {
    mood = "Sad :(";
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
  }
  else {
    mood = "Happy :)";
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED,LOW);
  }
 

  // mood
  lcd.setCursor(0, 0);
  lcd.print(mood);


  // water status
  lcd.setCursor(0, 1);
  lcd.print(waterStatus);
}

