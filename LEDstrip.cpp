/*	LEDstrip.ccp

	Programmer		:	A.S. Tilanus (alban@reptile-addict.nl)
	Company			:	reptile-addict.nl
	Version			:	20130120 (yyyyMMdd)
	
	Description		:	Library to control a RGB LED
	
	Prerequisites	:	Arduino

	Keywords		:	Arduino; RGB;

	Disclaimer		:	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 	INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "LEDstrip.h"
#include "Arduino.h"
#include <math.h>

/* Usage:
	#include <LEDstrip.h>

	LEDstrip myLEDstrip;

	void setup() {
		myLEDstrip.DefineRGBLED(5, 3, 6);
	}

	void loop() {

	}
*/

LEDstrip::LEDstrip() {
}

void LEDstrip::DefineRGBLED(int Rpin, int Gpin, int Bpin) {
	/// <summary>
	/// Defines which PWM pins are used for the RGB LEDS
	/// </summary>
	/// <param name="Rpin">Red pin</param>
	/// <param name="Gpin">Green pin</param>
	/// <param name="Bpin">Blue pin</param>
	
	isRGB=true;
	pinMode(Rpin, OUTPUT);
    _Rpin = Rpin;

	pinMode(Gpin, OUTPUT);
    _Gpin = Gpin;

	pinMode(Bpin, OUTPUT);
    _Bpin = Bpin;
}

void LEDstrip::DefineSingleColourLED(int LEDpin) {
	/// <summary>
	/// Defines which PWM pin is used for a non RGB LEDstrip
	/// </summary>
	/// <param name="LEDpin">PWM pin</param>
	
	isRGB=false;
	pinMode(LEDpin, OUTPUT);
    _Rpin = LEDpin;
}

void LEDstrip::LEDstripOFF() {
	/// <summary>
	/// Turns the LEDstrip OFF
	/// </summary>
	
	analogWrite(_Rpin, 0);
	analogWrite(_Gpin, 0);
	analogWrite(_Bpin, 0);

	// save current RGB values for future use
	RedVal=0;
	GreenVal=0;
	BlueVal=0;
}


void LEDstrip::SetRGBColour(byte R, byte G, byte B) {
	/// <summary>
	/// Make the RGB LEDstrip light up in a specific RGB colour.
	/// </summary>
	/// <param name="R">The amount of RED (0-255)</param>
	/// <param name="G">The amount of GREEN (0-255)</param>
	/// <param name="B">The amount of BLUE (0-255)</param>
	
	if (isRGB=true) { 
		analogWrite(_Rpin, R);
		analogWrite(_Gpin, G);
		analogWrite(_Bpin, B);

		// save current RGB values for future use
		RedVal=R;
		GreenVal=G;
		BlueVal=B;

		// save current RGB colour as HSL
		RGB2HSL(RedVal,GreenVal,BlueVal);
	}
}

void LEDstrip::SetHSLColour(int H, int S, int L) {
	/// <summary>
	/// Make the RGB LEDstrip light up in a specific HSL colour.
	/// </summary>
	/// <param name="H">Hue (0-360)</param>
	/// <param name="S">Saturation (0-100)</param>
	/// <param name="L">Lightness (0-100)</param>

	if (isRGB=true) {
		HSL2RGB(H,S,L);

		analogWrite(_Rpin, RedVal);
		analogWrite(_Gpin, GreenVal);
		analogWrite(_Bpin, BlueVal);

		// save current HSL values for future use
		HueVal=H;
		SaturationVal=S;
		LightnessVal=L;
	}
}

void LEDstrip::SetHSLrandomColour(int StartHueAngle, int maxAngleStep) {
	/// <summary>
	/// Generate a random HSL colour which only differs by a given amount from the previous colour. 
	/// The Saturation is set to 100% and the Lightness to 50%.
	/// </summary>
	/// <param name="StartHueAngle">Start hue (0-360)</param>
	/// <param name="maxAngleStep">Max. hue step to next colour</param>

	int NewH = random(StartHueAngle-maxAngleStep,StartHueAngle+maxAngleStep);
	// modulo is used to make sure the value is between 0 and 360deg and that for example 371deg results in 375 % 360 = 15deg
	NewH=NewH % 360;

	SetHSLColour(NewH,100,50);
}

void LEDstrip::SetRandomColour() {
	/// <summary>
	/// Generate a random colour
	/// </summary>
	
	// save current RGB values for future use
	RedVal=random(255);
	GreenVal=random(255);
	BlueVal=random(255);

	analogWrite(_Rpin,RedVal );
	analogWrite(_Gpin, GreenVal);
	analogWrite(_Bpin, BlueVal);
}

void LEDstrip::SetWhiteLight(byte intensity) {
	/// <summary>
	/// Generate White light at a given intensity (0-255)
	/// </summary>
	/// <param name="intensity">The intensity of the light (0-255)</param>
	
	// save current RGB values for future use
	RedVal=random(intensity);
	GreenVal=random(intensity);
	BlueVal=random(intensity);

	analogWrite(_Rpin, intensity);
	analogWrite(_Gpin, intensity);
	analogWrite(_Bpin, intensity);
}

void LEDstrip::SetRedLight(byte intensity) {
	/// <summary>
	/// Generate Red light at a given intensity (0-255)
	/// </summary>
	/// <param name="intensity">The intensity of the light (0-255)</param>

	analogWrite(_Rpin, intensity);
	analogWrite(_Gpin, 0);
	analogWrite(_Bpin, 0);

	// save current RGB values for future use
	RedVal=random(intensity);
	GreenVal=random(0);
	BlueVal=random(0);

}

void LEDstrip::SetGreenLight(byte intensity) {
	/// <summary>
	/// Generate Green light at a given intensity (0-255)
	/// </summary>
	/// <param name="intensity">The intensity of the light (0-255)</param>

	analogWrite(_Rpin, 0);
	analogWrite(_Gpin, intensity);
	analogWrite(_Bpin, 0);

	// save current RGB values for future use
	RedVal=random(0);
	GreenVal=random(intensity);
	BlueVal=random(0);
}

void LEDstrip::SetBlueLight(byte intensity) {
	/// <summary>
	/// Generate Blue light at a given intensity (0-255)
	/// </summary>
	/// <param name="intensity">The intensity of the light (0-255)</param>

	analogWrite(_Rpin, 0);
	analogWrite(_Gpin, 0);
	analogWrite(_Bpin, intensity);

	// save current RGB values for future use
	RedVal=random(0);
	GreenVal=random(0);
	BlueVal=random(intensity);
}

void LEDstrip::SetRGBRandomColour(byte _R1, byte _G1, byte _B1, byte Variation) {
	/// <summary>
	/// Generate a random RGB colour which only differs by a given amount from the previous colour.
	/// </summary>
	/// <param name="_R1">Initial Red value (0-255)</param>
	/// <param name="_G1">Initial Green value (0-255)</param>
	/// <param name="_B1">Initial Blue value (0-255)</param>
	/// <param name="Variation">Max difference between current and next R, G and B values (0-255)</param>

	//_R1, _G1 and _B1 are the current ( or start) values for the random colour

	//The new random values are limited between an upper and lower value equal to + or - "Variation"
	int NewR = random(_R1-Variation,_R1+Variation);
	int NewG = random(_G1-Variation,_G1+Variation);
	int NewB = random(_B1-Variation,_B1+Variation);

	// save current RGB values for future use
	// modulo is used to make sure the value is between 0 and 255 and that for example 257 results in 257 % 255 = 2
	RedVal=NewR % 255;
	GreenVal=NewG % 255;
	BlueVal=NewB % 255;

	analogWrite(_Rpin, RedVal);
	analogWrite(_Gpin, GreenVal);
	analogWrite(_Bpin, BlueVal);


}

float LEDstrip::Hue_2_RGB(float v1,float v2,float vH) {
	/// <summary>
	/// Private function used by the conversion between HSL to RGB
	/// </summary>
	
	if ( vH < 0 ) 
	{
		vH += 1;
	}
   
	else if ( vH > 1 ) 
	{
		vH -= 1;
	}
	
	if ( ( 6 * vH ) < 1 ) 
	{
		return ( v1 + ( v2 - v1 ) * 6 * vH );
	}
	
	if ( ( 2 * vH ) < 1 ) 
	{
		return ( v2 );
	}
	
	if ( ( 3 * vH ) < 2 ) 
	{
		return ( v1 + ( v2 - v1 ) * ( 0.66666667 - vH ) * 6 );
	}

	return ( v1 );
}


void LEDstrip::RGB2HSL(byte R, byte G, byte B) {
	/// <summary>
	/// Converts an RGB color value to HSL. 
	/// Conversion formula adapted from http://en.wikipedia.org/wiki/HSL_color_space.
	/// http://www.rapidtables.com/convert/color/rgb-to-hsl.htm
	/// 
	/// Returns HueVal (0-360), SaturationVal (0-100) and LightnessVal (0-100)
	/// </summary>
	/// <param name="R">Red value (0-255)</param>
	/// <param name="G">Green value (0-255)</param>
	/// <param name="B">Blue value (0-255)</param>
	
	
	float _R = R;
	float _G = G;
	float _B = B;
	_R = _R / 255;
	_G = _G / 255;
	_B = _B / 255;

	float RGB[] = {_R,_G,_B};
	float Cmax = -1;
		for (int i=0; i<=2; i++) {	
			if (RGB[i] > Cmax) {
				Cmax = RGB[i];
			}
		}

	float Cmin = 256;
		for (int i=0; i<=2; i++) {
			if (RGB[i] < Cmin) {
				Cmin = RGB[i];
			}
		}

	float Delta = Cmax - Cmin;

	float _H;
	float temp;
	if (Cmax == _R) {	
		_H =(1.0/6.0) * (fmod((_G - _B)/Delta,6));
	}
	else if (Cmax == _G) {
		_H = (1.0/6.0) * (((_B - _R)/Delta) + 2);
	}
	else if (Cmax == _B) {
		temp = 1/6 * (((_R - _G)/Delta) + 4);
		_H = 0.1666667 * (((_R - _G)/Delta) + 4);
	}
	

	float _L = (Cmax + Cmin) / 2;

	

	float _S;
	if (Delta == 0) {
		_S=0;
	}
	else {
		_S = Delta / (1 - abs(2*_L - 1));
	}

	_H = _H*360;
	_H=_H+0.5; //adding 0.5 for rounding purposes

	if (_H < 0) {
		_H=360 + _H;
	}

	int H=_H;

	_S=(_S*100)+0.5;
	int S=_S;
	
	_L=(_L*100)+0.5;
	int L = _L;

	HueVal=H;
	SaturationVal=S;
	LightnessVal=L;
}

void LEDstrip::HSL2RGB(int _H, int _S, int _L) {
	/// <summary>
	/// Converts an HSL color value to RGB.
	/// Returns RedVal, GreenVal and BlueVal (0-255)
	/// </summary>
	/// <param name="_H">Hue (0-360)</param>
	/// <param name="_S">Saturation (0-100)</param>
	/// <param name="_L">Lightness (0-100)</param>
	
	float H = _H;	// 0 >= H <= 360

	float S = _S;
	S = 0.01 * S;	// 0 >= S <=1

	float L = _L;
	L = 0.01 * L;	// 0 >= L <=1


	float C = ( 1 - abs(2*L - 1)) * S;

	float X = C * (1 - abs(fmod((H/60),2)-1));

	float m = L - C / 2;

	float _R;
	float _G;
	float _B;

	if (H>=0 && H<60) {
		_R = C;
		_G = X;
		_B = 0;
	}
	else if (H>=60 && H<120) {
		_R = X;
		_G = C;
		_B = 0;
	}
	else if (H>=120 && H<180) {
		_R = 0;
		_G = C;
		_B = X;
	}
	else if (H>=180 && H<240) {
		_R = 0;
		_G = X;
		_B = C;
	}
	else if (H>=240 && H<300) {
		_R = X;
		_G = 0;
		_B = C;
	}
	else if (H>=300 && H<360) {
		_R = C;
		_G = 0;
		_B = X;
	}

	_R = ((_R + m)*255) + 0.5;
	_G = ((_G + m)*255) + 0.5;
	_B = ((_B + m)*255) + 0.5;

	RedVal = _R;
	GreenVal = _G;
	BlueVal = _B;
}






