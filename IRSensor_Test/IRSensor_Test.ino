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

void loop() {
  digitalWrite(IR, HIGH);
  Serial.println(analogRead(d2));
}
