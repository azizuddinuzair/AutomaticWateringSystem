// Arduino 4 (Output System)


// Ultrasonic sensor pins
const int trigPin = 9;
const int echoPin = 10;

const int relayPin = 7;

const int buzzerPin = 4;

unsigned long lastUltrasonicCheck = 0;


//Button pin
const int buttonPin = 5;
int lastButtonReading = LOW;
int buttonState = LOW;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;
unsigned long lastPressTime = 0;
int state = 0;
int buzzTone = 300;

float soilValue;


// If under 30 it is dry
int dryThreshold = 30;


// Ultrasonic reading
float distance, duration;
float isFar = 12;


String incomingData;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);

  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  pinMode(buttonPin, INPUT);
}

unsigned long prevMillis, currMillis;


void loop() {
  currMillis = millis();

  if (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    float newSoilValue = line.toFloat();
   
    if (newSoilValue > 0 || line.startsWith("0")) {
      soilValue = newSoilValue;
     
    }
  }

  int currentButtonReading = digitalRead(buttonPin);
  if (currentButtonReading != lastButtonReading){
    lastDebounceTime = millis();
  }


  if ((millis() - lastDebounceTime) > debounceDelay) {
   
    if (currentButtonReading != buttonState) {
      buttonState = currentButtonReading;
      if (buttonState == LOW){
        if (state == 0){
          state = 1;
        }
        else {
          state = 0;
        }
      }
    }
  }

  lastButtonReading = currentButtonReading;


  if (currMillis - prevMillis > 1000){
    prevMillis = millis();

    //Check distance and send it
    digitalWrite(trigPin, LOW);
    digitalWrite(trigPin, HIGH);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = (duration*.0343)/2;
    Serial.println(distance);

    //If the soil is wet we dont pump water
    if (soilValue >= dryThreshold){
      digitalWrite(relayPin, HIGH);
      noTone(buzzerPin);
    }

    //else pump water and play sound
    else {
      digitalWrite(relayPin,LOW);
      if (state == 0){
        tone(buzzerPin, 100);
      }
      else {
        tone(buzzerPin, 500);
      }
    }
  }
}
