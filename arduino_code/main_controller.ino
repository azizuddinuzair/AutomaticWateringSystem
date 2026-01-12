// Arduino 2 (Main Controller)
#include <LiquidCrystal.h>


// LCD pin mapping
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


String incomingData;
float tempValue;
float humidityValue;
float soilValue; 
float waterValue;


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Waiting Data...");
}


void loop() {                                                                                                                                                                                                                                                                                                             
  if (Serial.available()) {

    incomingData = Serial.readStringUntil('\n'); 

 
    int firstValue = incomingData.indexOf(',');
    int secondValue = incomingData.indexOf(',', firstValue + 1);
    int thirdValue = incomingData.indexOf(',', secondValue + 1);


    if (firstValue > 0 && secondValue > 0 && thirdValue > 0) {


      tempValue    = incomingData.substring(0, firstValue).toFloat();
      humidityValue = incomingData.substring(firstValue + 1, secondValue).toFloat();
      soilValue    = incomingData.substring(secondValue + 1, thirdValue).toFloat();
      waterValue   = incomingData.substring(thirdValue + 1).toFloat();


      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("T:"); lcd.print(tempValue);
      lcd.print(" H:"); lcd.print(humidityValue);


      lcd.setCursor(0, 1);
      lcd.print("S:"); lcd.print(soilValue);
      lcd.print(" W:"); lcd.print(waterValue);


      Serial.print(tempValue);
      Serial.print(",");
      Serial.print(humidityValue);
      Serial.print(",");
      Serial.print(soilValue);
      Serial.print(",");
      Serial.println(waterValue);
    }
  }
}
