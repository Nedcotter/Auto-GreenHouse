#include <Stepper.h>
#include <CheapStepper.h>
#include "DHT.h"
#define SensorPin A2
#define DHTPIN 2
#define DHTTYPE DHT11
const int capteur_D = 4;
const int capteur_A = A0;
int val_analogique;
float sensorValue = 0;
bool moveClockwise = true;
int lid_open;
bool start = false;
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
}
void Stepper1() {
  for (int s = 0; s < 4096; s++) {
    // 4096 steps = full rotation
    stepper.step(moveClockwise);
    int nStep = stepper.getStep();
    if (nStep % 64 == 0) {
      //Serial.print("Step-Pos: ");
      //Serial.print(nStep);
      //Serial.print("");
      //Serial.println();
    }
  }
  // set whether lid is open or closed (swap value each time stepper is run)

  lid_open = 1;
}

void Stepper2() {
  for (int s = 0; s < 4096; s++) {
    // 4096 steps = full rotation
    stepper.step(!moveClockwise);
    int nStep = stepper.getStep();
    if (nStep % 64 == 0) {
      //Serial.print("Step-Pos: ");
      //Serial.print(nStep);
      //Serial.print("");
      //Serial.println();
    }
  }
  // set whether lid is open or closed (swap value each time stepper is run)

  lid_open = 0;
}
//delay(1000);
//moveClockwise = !moveClockwise;

// val_analogique is the variable for the dielectric constant
void RainOpen() {
  val_analogique = analogRead(capteur_A);
  //Serial.print("Rain : ");
  Serial.println(val_analogique);
  //Serial.print("Lid value : ");
  //Serial.println(lid_open);

  if (val_analogique > 100 && (lid_open == 0)) {
    //Serial.print("Open Lid");
    //Serial.println("");
    delay(1000);
    Stepper1();

  }
  // bug //////////////////////////////////////////////////////////
  if (val_analogique < 100 && (lid_open == 1)) {
    //Serial.print("Close Lid");
    //  Serial.println("");
    delay(1000);
    Stepper2();
  }
}

void Soil3() {
  for (int i = 0; i <= 100; i++);
  {
    sensorValue = sensorValue + analogRead(SensorPin);
    delay(1);
  }
  sensorValue = sensorValue / 100.0;
  //Serial.println("100");
  Serial.println(sensorValue);
  delay(30);
}

void TempHumid() {
  delay(2000);
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  int f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  //float hic = dht.computeHeatIndex(t, h, false);

  //Serial.print(F("Humidity: "));
  Serial.println(h);
  //Serial.print(F("%"));
  //Serial.println("");
  Serial.println(t);
  //Serial.print(F("°C "));
  //Serial.println();
  //Serial.print(f);
  //Serial.print(F("°F  Heat index: "));
  //Serial.print(hic);
  //Serial.print(F("°C "));
  //  Serial.print(hif);
  //Serial.println(F("°F"));
}

void loop() {
  if (start == false && Serial.available()) {
   // command = Serial.readStringUntil('\n');
    if (Serial.readStringUntil('\n').equals("start")) {
      start = true;
    }
  }
  if (start == true) {
    RainOpen();
    delay(1000);
    Soil3();
    delay(5000);
    TempHumid();
    delay(5000);
  }
}
