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

int readIR() {
  valores[5] = analogRead(d2);
  valores[4] = analogRead(d3); // Calibración
  valores[3] = analogRead(d4);
  valores[2] = analogRead(d5);
  valores[1] = analogRead(d6);
  valores[0] = analogRead(d7);
}

//max : array -> float
//Devuelve el valor máximo de una array
float max(int list[6]) {
  float maximo = 0;
  for (int i = 0; i<6; i++) {
    if (list[i] > maximo) {
      maximo = list[i];
    }
  }
  return maximo;
}

//mini : array -> float
//Devuelve el valor mínimo de una array
float min(int list[6]) {
  float minimo = 1024;
  for (int i = 0; i<6; i++) {
    if (list[i] < minimo) {
      minimo = list[i];
    }
  }
  return minimo;
}

//declarar arrays minimos y maximos

void calibrar() {
  digitalWrite(IR, HIGH);
  // Look for lower (白)
  for (int i = 0; i<10; i++) {
    readIR();
    for (int j = 0; j<6; j++) {
      if (valores[j] < minimos[j]) {
        minimos[j] = valores[j];
      }
    delay(100);
    }
  }

  tone(buzzer, 1000, 200);
  delay(2000);
  //look for upper (黒)
  for (int i = 0; i<10; i++) {
    readIR();
    for (int j = 0; j<6; j++) {
      if (valores[j] > maximos[j]) {
        maximos[j] = valores[j];
      }
    }
  }
  tone(buzzer, 2000, 200);
  delay(2000);
}