#define PWMB 6
#define BI2 7
#define BI1 4

#define AI1 8
#define AI2 9
#define PWMA 5

#define button 2

bool pwr = false;

void setup() {
    Serial.begin(9600);
    pinMode(PWMA, OUTPUT);
    pinMode(AI2, OUTPUT);
    pinMode(AI1, OUTPUT);
    pinMode(BI1, OUTPUT);
    pinMode(BI2, OUTPUT);
    pinMode(PWMB, OUTPUT);
    pinMode(button, INPUT);
}

void PowerBttn() {
  if (digitalRead(button) == HIGH) {
    if (pwr == true) {
      pwr = false;
    } else {
      pwr = true;
    }
  }
}

void loop() {
    PowerBttn(); //Esta weaa no está funcionando xd

    if (pwr) {
      // Move Forward
    digitalWrite(AI1, HIGH);
    digitalWrite(AI2, LOW);
    analogWrite(PWMA, 33); // Speed for Motor A

    digitalWrite(BI1, HIGH);
    digitalWrite(BI2, LOW);
    analogWrite(PWMB, 33); // Speed for Motor B
    }
}
