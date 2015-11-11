
#include <LEDstrip.h>

LEDstrip myLEDstrip;

const int Rpin = 3;
const int Gpin = 5;
const int Bpin = 6;
const int SPEED = 100;


void setup() {
	myLEDstrip.DefineRGBLED(Rpin, Gpin, Bpin);
}

void loop() {

	for (int i = 0; i < 360; i++) {
		myLEDstrip.SetHSLColour(i, 100, 50);
		delay(SPEED);
	}

}

