#include <Stepper.h>
#include <CheapStepper.h>
const int capteur_D = 4;
const int capteur_A = A0;
int val_analogique;
bool moveClockwise = true;
int lid_open;
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
      Serial.print("Step-Pos: ");
      Serial.print(nStep);
      Serial.print("");
      Serial.println();
    }
  }
  // set whether lid is open or closed (swap value each time stepper is run)
  if (lid_open == 0) {
    lid_open = 1;
  }
  else {
    lid_open = 0;
  }
}


//delay(1000);
//moveClockwise = !moveClockwise;

void RainOpen() {
  val_analogique = analogRead(capteur_A);
  Serial.print("Analog value : ");
  Serial.println(val_analogique);
    Serial.print("Lid value : ");
  Serial.println(lid_open);
  Serial.println("");

  if (val_analogique > 50 && (lid_open == 0)) {
    Serial.print("Open Lid");
    Serial.println("");
    delay(1000);
    Stepper1();

  }
  // bug //////////////////////////////////////////////////////////
  if (val_analogique < 50 && (lid_open == 1)) {
    Serial.print("Close Lid");
    Serial.println("");
    delay(1000);
    Stepper1();
  }
}

void loop() {
  //Stepper1();

  RainOpen();
  //int lid = 1;
  delay(1000);
  //  Soil3();
}
