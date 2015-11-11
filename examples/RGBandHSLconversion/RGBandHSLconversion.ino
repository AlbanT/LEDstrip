#include <LEDstrip.h>

LEDstrip myLEDstrip;

const int Rpin = 3;
const int Gpin = 5;
const int Bpin = 6;
const int SPEED = 100;


void setup() {
	myLEDstrip.DefineRGBLED(Rpin, Gpin, Bpin);
	
	Serial.begin(9600);

	myLEDstrip.RGB2HSL(5, 165, 75);
	Serial.println("R=5 G=165 B=75 -> ");
	Serial.print("..Hue        = "); Serial.print(myLEDstrip.HueVal);Serial.println(" degrees");
	Serial.print("..Saturation = "); Serial.print(myLEDstrip.SaturationVal); Serial.println("%");
	Serial.print("..Lightness  = "); Serial.print(myLEDstrip.LightnessVal); Serial.println("%");
	Serial.println("");
	myLEDstrip.HSL2RGB(myLEDstrip.HueVal, myLEDstrip.SaturationVal, myLEDstrip.LightnessVal);
	Serial.print("..Red        = "); Serial.println(myLEDstrip.RedVal);
	Serial.print("..Green      = "); Serial.println(myLEDstrip.GreenVal);
	Serial.print("..Blue       = "); Serial.println(myLEDstrip.BlueVal);
	
}

void loop() {

}