#define HR A0
#define HL A7

int umbral = 1000;
int geo[4] = {0, 0, 0, 0};

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
    } else {
        geo[0] = 0;
    }

    if (geo[0] != geo[1]) {
        if (geo[0] == 0 && geo[1] == 1 && geo[2] == 0) {
            // Código hit Izq
            hitL != hitL;
        } else if (geo[0] == 0 && geo[1] == 2 && geo[2] == 0) {
            // Código hit Der
            hitR = !hitR;
            inStart = false;
            beep();
        } else if (geo[0] == 0 && geo[1] == 3 && geo[2] == 0) {
            // Código hit Ambos

        }
        geo[3] = geo[2];
        geo[2] = geo[1];
        geo[1] = geo[0];
    }
}
