#define d2 13
#define d3 14
#define d4 15
#define d5 16
#define d6 17
#define d7 18
#define IR 11

#define PWMB 6
#define BI2 7
#define BI1 4

#define AI1 8
#define AI2 9
#define PWMA 5

#define button 2

int valores[6];
float Kp = 0.1; //Constante Proporcional
float Ki = 0.1;    //Constante Integral
float Kd = 0.01;  //Constante Derivada
float error = 0, lastError = 0;
float integral = 0;
float derivative = 0;
float pos = 0, lastPos = 0;

int velocity = 33;

void setup() {
  Serial.begin(9600);
  pinMode(IR, OUTPUT);
  pinMode(d2, INPUT);
  pinMode(d3, INPUT);
  pinMode(d4, INPUT);
  pinMode(d5, INPUT);
  pinMode(d6, INPUT);
  pinMode(d7, INPUT);
  
  pinMode(PWMA, OUTPUT);
  pinMode(AI2, OUTPUT);
  pinMode(AI1, OUTPUT);
  pinMode(BI1, OUTPUT);
  pinMode(BI2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(button, INPUT);
}

bool pwr = false;

void PowerBttn() {
  if (digitalRead(button) == HIGH) {
    if (pwr == true) {
      pwr = false;
    } else {
      pwr = true;
    }
  }
}


// max : array -> float
// Devuelve el valor máximo de una array
float maxi(int list[6]) {
  float maximum = 0;
  for (int i = 0; i<6; i++) {
    if (list[i] > maximum) {
      maximum = list[i];
    }
  }
  return maximum;
}

// readIR : none -> none
// Lee los valores de los sensores IR del frente y los convierte en array
int readIR() {
  valores[0] = analogRead(d2);
  valores[1] = analogRead(d3);
  valores[2] = analogRead(d4);
  valores[3] = analogRead(d5);
  valores[4] = analogRead(d6);
  valores[5] = analogRead(d7);
}

// relative_pos : void -> int
// Devuelve un valor entre -1023 y 1023 correspondiendo a la posición de la
// linea relativa al vehículo
int relative_pos() {
  readIR();
  float sumaPonderada = -2.5*valores[0]-1.5*valores[1]-0.5*valores[2]+0.5*valores[3]+1.5*valores[4]+2.5*valores[5];
  float suma = valores[0]+valores[1]+valores[2]+valores[3]+valores[4]+valores[5];
  bool onLine = false;
if (suma > 1000){
    onLine  = true;
  } 
  if (onLine) {
      pos = int(100.0 * sumaPonderada / suma);
  } 
else {
  if (lastPos < 0) {
        pos = -255;
    } else if (lastPos >= 0) {
        pos = 255;
    }
  }
  lastPos = pos;
  return pos;
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

void loop() {
  if (pwr) {
    digitalWrite(IR, HIGH);
    pos = relative_pos();
    mover(velocity-pos, velocity+pos);
  } else {
    mover(0,0);
  }

  PowerBttn();
}
