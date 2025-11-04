#define PINBUZZER 10
#define PINBOTON 2
#define PINLED 13
#define PIN_Sensor_ON 11


int posicion_ideal = 0;

//cómo modificar el kprop: Comenzar con valores con valores bajos, y aumentar de a poco, hasta que siga la linea y quede oscilando.
//cómo modificar el kderiv: Comenzar con valores con valores bajos, y aumentar de a poco, hasta que el robot deje de oscilar.

//cuando el robot deje de oscilar, puedes subirle la velocidad nuevamente, y comenzar nuevamente a modificar el Kprop y el Kderiv.

float Kprop = 0.35;  
float Kderiv = 0.2;
float Kint = 0.0001;

int ref = 0;

int base = 90;
int error_pasado = 0;
int error_cumulativo = 0;


void setup() {
    Serial.begin(115200);
    Peripherals_init();
    TB6612FNG_init();
    Sensors_init();

    digitalWrite(PINLED, LOW);
    delay(500);

    Motores(0, 0);

    delay(500);
    WaitBoton();
    calibracion();
}

void PID() {
    int p = GetPos() - ref;
    int error = p - posicion_ideal;
    int d_error = error - error_pasado;
    int correction_power = int(Kprop * error) + int(Kderiv * d_error) + int(Kint * error_cumulativo);

    if (correction_power > 255) {
        correction_power = 255;

    }

    else if (correction_power < -255) {
        correction_power = -255;
    }

    Motores(base + correction_power, base + -correction_power);
    error_pasado = error;
    error_cumulativo += error;
}

int vuelta = 0;
bool inStart = true;

void loop() {
    hits();
    if (hitR % 2 == 0) {
        if (inStart) {
            WaitBoton();
            PID();
        } else {
            inStart = true;
            error_cumulativo = 0;
            error_pasado = 0;
            Motores(0, 0);
            WaitBoton();
        }
    } else {
        PID();
    }
}
