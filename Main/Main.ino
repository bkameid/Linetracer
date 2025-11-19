#define PINBUZZER 10
#define PINBOTON 2
#define PINLED 13
#define PIN_Sensor_ON 11
#define mover Motores

int posicion_ideal = 0;

bool hitL = false;
bool  hitR = true;
bool inStart = true;

//cómo modificar el kprop: Comenzar con valores con valores bajos, y aumentar de a poco, hasta que siga la linea y quede oscilando.
//cómo modificar el kderiv: Comenzar con valores con valores bajos, y aumentar de a poco, hasta que el robot deje de oscilar.

//cuando el robot deje de oscilar, puedes subirle la velocidad nuevamente, y comenzar nuevamente a modificar el Kprop y el Kderiv.

float Kprop = 0.4 ; //0.388
float Kderiv[5] = {10,15,10,10,10}; //0.2
float Kint[5] = {0,0,0,0,0};

int ref = 60;

int vuelta = 0;
int base[5] = {50,60,70,80,90}; // Error en 90
int curva = 60;
int error_pasado = 0;
int error_cumulativo = 0;


void setup() {
    Serial.begin(9600);
    Peripherals_init();
    TB6612FNG_init();
    Sensors_init();

    digitalWrite(PINLED, LOW);
    WaitBoton();
    calibracion();
    WaitBoton();
    delay(2000);
}

void PID() {
    int p = GetPos() - ref;
    int error = p - posicion_ideal;
    int d_error = error - error_pasado;
    int correction_power = int(Kprop * error) + int(Kderiv[vuelta] * d_error) + int(Kint[vuelta] * error_cumulativo);

    if (correction_power > 255) {
        correction_power = 255;

    }

    else if (correction_power < -255) {
        correction_power = -255;
    }

    Motores(base[vuelta] + correction_power, base[vuelta] - correction_power);
    error_pasado = error;
    error_cumulativo += error;
}

void loop() {
  hits();
  if (inStart) {
    PID();
  } else {
    if (!hitR) {
      PID();
    } else {
      Serial.print("meta");
      Motores(0,0);
      vuelta += 1;
      WaitBoton();
      inStart = true;
      delay(2000);
    }
  }
}
