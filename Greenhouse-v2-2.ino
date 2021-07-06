
#include "DHT.h"
#define SensorPin A2
#define DHTPIN 2
#define DHTTYPE DHT22
const int stepsPerRevolution = 200;
const int capteur_D = 4;
const int capteur_A = A0;
int val_analogique;
float sensorValue = 0;
bool moveClockwise = true;
bool lid;
DHT dht(DHTPIN, DHTTYPE);
CheapStepper stepper;
// arduino pin <--> pins on ULN2003 board:
// 8 <--> IN1
// 9 <--> IN2
// 10 <--> IN3
// 11 <--> IN4

void setup() {
  pinMode(capteur_D, INPUT);
  pinMode(capteur_A, INPUT);
  Serial.begin(9600);
  dht.begin();
}

void Stepper1() {
  for (int s = 0; s < 4096; s++) {
    // 4096 steps = full rotation
    stepper.step(moveClockwise);
    int nStep = stepper.getStep();
    if (nStep % 64 == 0) {
      Serial.print("current step position: "); Serial.print(nStep);
      Serial.println();
    }
  }
  delay(1000);
  moveClockwise = !moveClockwise;
  bool lid = true;
}
void Rain2() {
  val_analogique = analogRead(capteur_A);
  Serial.print("Analog value : ");
  Serial.println(val_analogique);
  Serial.println("");

  if (bool lid = false) {
    if (val_analogique > 100) {
      Stepper1();
      bool lid = true;
      delay(1000);
    }
  }
  else {
    delay(100);
  }
}


void Soil3() {
  for (int i = 0; i <= 100; i++);
  {
    sensorValue = sensorValue + analogRead(SensorPin);
    delay(1);
  }
  sensorValue = sensorValue / 100.0;
  Serial.println(sensorValue);
  delay(30);
}

void TempHumid() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  //  Serial.print(hif);
  Serial.println(F("°F"));
}

void loop() {
  //Stepper1();
  Rain2();
  //  Soil3();
}
