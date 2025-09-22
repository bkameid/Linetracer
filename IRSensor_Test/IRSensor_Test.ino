#define d2 A1
#define d3 A2
#define d4 A3
#define d5 A4
#define d6 A5
#define d7 A6
#define IR 11

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
  
  digitalWrite(IR, HIGH);
  
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
  int suma = 0;
  int nums[] = {-3, -2, -1, 1, 2, 3};
  readIR();
  float ratio = 1024.0 / maxi(valores);
  for (int i = 0; i<6; i++) {
    if (valores[i] <= 100) {  // Filtro de Ruido
      valores[i] = 0;
    }
    Serial.print(valores[i]); Serial.print(" ");
    valores[i] = valores[i]*nums[i]*ratio;
    suma += valores[i];
  }
  int result = suma / 6;
  return result;
}

void loop() {
  Serial.println(relative_pos());
}
