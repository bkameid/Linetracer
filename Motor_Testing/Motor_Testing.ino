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

int smoothing(int vi, int vf, int ti) {
  float delta = vf - vi;
  float step = delta / 2000;
  int v = int(vi + step * (millis() - ti));
  Serial.print(vi); Serial.print(" | "); Serial.print(step); Serial.print(" | "); Serial.print(millis() - ti); Serial.print(" | "); Serial.println(int(step*(millis() - ti)));
  if ((step > 0 && v > vf) || (step < 0 && v < vf)) {
    v = vf;
  }
  return v;
}

void mover(int leftSpeed, int rightSpeed) {
  // Función para mover el robot, leftSpeed y rightSpeed van de -255 a 255
    // Move Forward
  digitalWrite(AI1, HIGH);
  digitalWrite(AI2, LOW);
  analogWrite(PWMA, leftSpeed); // Speed for Motor A

  digitalWrite(BI1, HIGH);
  digitalWrite(BI2, LOW);
  analogWrite(PWMB, rightSpeed); // Speed for Motor B
}

int v = 100;

void loop() {
    PowerBttn(); //Esta weaa no está funcionando xd

    if (pwr) {
      mover(v*1.04,v);
    }
}
