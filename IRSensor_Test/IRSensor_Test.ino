#define d2 A1
#define d3 A2
#define d4 A3
#define d5 A4
#define d6 A5
#define d7 A6
#define IR 11

#define HR A0
#define HL A7

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
  pinMode(HR, INPUT);
  pinMode(HL, INPUT);
  Serial.print("[");
}

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
  valores[0] = analogRead(d2);
  valores[1] = analogRead(d3); //Lectura de este sensor da problemas
  valores[2] = analogRead(d4);
  valores[3] = analogRead(d5);
  valores[4] = analogRead(d6);
  valores[5] = analogRead(d7);
}

int relative_pos() {
  float minimo = mini(valores);
  for (int i = 0; i<6; i++) {
    valores[i] = map(valores[i], 1024, minimo, 0, 255);
    if (valores[i] < 50) {
      valores[i] = 0;
    }
  }
  float sumaPonderada = -2.5*valores[0]-1.5*valores[1]-0.5*valores[2]+0.5*valores[3]+1.5*valores[4]+2.5*valores[5];

  return sumaPonderada/9;
}

void testIR() {
  float minimo = mini(valores); 
  for (int i = 0; i<6; i++) {
    valores[i] = map(valores[i], 1024, minimo, 0, 255);
  }
  digitalWrite(IR, HIGH);
  for (int i = 0; i<6; i++) {
    Serial.print(valores[5-i]); Serial.print("  |  ");
  }
  Serial.println(relative_pos());
}

void loop() {
  readIR();
  testIR();
  //Serial.print(valores[1]); Serial.print(", ");
  delay(100);
}
