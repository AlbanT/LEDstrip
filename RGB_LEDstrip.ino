

#include <LEDstrip.h>

LEDstrip myLEDstrip;

int i;

void setup()
{
	myLEDstrip.DefineRGBLED(9,10,11);

	myLEDstrip.SetRedLight(255);
	delay(1000); 
	myLEDstrip.SetGreenLight(255);
	delay(1000);
	myLEDstrip.SetBlueLight(255);
	delay(1000);
	myLEDstrip.SetWhiteLight(255);
	delay(1000);

	i=0;
}

void loop()
{
	if (i<=20) {
		myLEDstrip.SetAdvRandomColour(myLEDstrip.RedVal,myLEDstrip.GreenVal,myLEDstrip.BlueVal,10);
		delay(500);
	}
	else if (i=21) {
		myLEDstrip.LEDstripOFF();
		delay(250);
		myLEDstrip.SetWhiteLight(255);
		delay(250);
		myLEDstrip.LEDstripOFF();
		delay(250);
	}
	else if (i>21 && i<100) {
		myLEDstrip.SetHSLrandomColour(myLEDstrip.HueVal,5);
		delay(500);
	}
	else {
		i=-1;
	}
	
	i++;
}
