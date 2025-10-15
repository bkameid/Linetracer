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

#define HR A0
#define HL A7

#define button 2
#define buzzer 10

int valores[6];

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

  pinMode(HR, INPUT);
  pinMode(HL, INPUT);
    
  pinMode(button, INPUT);
  pinMode(buzzer, OUTPUT);
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


// mini : array -> float
// Devuelve el valor mínimo de una array
float mini(int list[6]) {
  float minimo = 1024;
  for (int i = 0; i<6; i++) {
    if (list[i] < minimo) {
      minimo = list[i];
    }
  }
  return minimo;
}

// readIR : none -> none
// Lee los valores de los sensores IR del frente y los convierte en array
int readIR() {
  valores[5] = analogRead(d2);
  valores[4] = analogRead(d3); // Calibración
  valores[3] = analogRead(d4);
  valores[2] = analogRead(d5);
  valores[1] = analogRead(d6);
  valores[0] = analogRead(d7);
}

// relative_pos : void -> int
// Devuelve un valor entre -255 y 255 correspondiendo a la posición de la
// linea relativa al vehículo
int relative_pos() {
  readIR();
  float minimo = mini(valores);
  for (int i = 0; i<6; i++) {
    valores[i] = map(valores[i], 1024, minimo, 0, 255);
  }
  float sumaPonderada = -2.5*valores[0]-1.5*valores[1]-0.5*valores[2]+0.5*valores[3]+1.5*valores[4]+2.5*valores[5];

  return sumaPonderada/9;
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

bool hitR = false;
bool hitL = false;
int geo[4] = {0,0,0,0}; 

float Kp = 0.3; //Constante Proporcional
float Kd = 0.2;  //Constante Derivada
float Ki = 0;    //Constante Integral
float error = 0, lastError = 0;
float integral = 0;
float derivative = 0;
float pos = 0, lastPos = 0;

int vRecta = 40;
int vCurva = 30;

int velocity = vRecta;

int umbral = 1000;

// hits : none -> none
// geo = 0: no hay choque
// geo = 1: choque izquierda
// geo = 2: choque derecha
// geo = 3: choque ambos
void hits() {
  if (analogRead(HL) < umbral && analogRead(HR) < umbral) {
    geo[0] = 3;
  } else if (analogRead(HR) < umbral) {
    geo[0] = 2;
  } else if (analogRead(HL) < umbral) {
    geo[0] = 1;
    tone(buzzer, 1000, 50);
  } else {
    geo[0] = 0;
  }

  if (geo[0] != geo[1]) {
    if (geo[0] == 0 && geo[1] == 1 && geo[2] == 0) {
      // Código hit Izq
      /*if (hitL == false) {
        hitL = true;
        Kp = 0.5;
        velocity = vCurva;
      } else {
        hitL = false;
        Kp = 0.2;
        velocity = vRecta;
      }*/
    } else if (geo[0] == 0 && geo[1] == 2 && geo[2] == 0) {
      // Código hit Der
    } else if (geo[0] == 0 && geo[1] == 3 && geo[2] == 0) {
      // Código hit Ambos
    }
    geo[3] = geo[2];
    geo[2] = geo[1];
    geo[1] = geo[0];
  }
}

void PID() {
  pos = relative_pos();
  error = pos;
  integral = integral + error;
  derivative = error - lastError;
  int adjust = Kp*error + Ki*integral + Kd*derivative;
  lastError = error;
  int leftSpeed = velocity - adjust;
  int rightSpeed = velocity + adjust;

  if (leftSpeed > 255) {
    leftSpeed = 255;
  }
  if (rightSpeed > 255) {
    rightSpeed = 255;
  }
  if (leftSpeed < 0) {
    leftSpeed = 0;
  }
  if (rightSpeed < 0) {
    rightSpeed = 0;
  }

  //mover(leftSpeed, rightSpeed);
  Serial.print(relative_pos());Serial.print("   |   ");
  Serial.println(adjust);
}

void loop() {
  digitalWrite(IR, HIGH);
  if (pwr) {
    PID();
    hits();
  } else {
    mover(0,0);
  }

  PowerBttn();
}
