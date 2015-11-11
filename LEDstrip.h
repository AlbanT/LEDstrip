/*	LEDstrip.h

	Programmer		:	A.S. Tilanus (alban@reptile-addict.nl)
	Company			:	reptile-addict.nl
	Version			:	20130120 (yyyyMMdd)
	
	Description		:	Library to control a RGB LED
	
	Prerequisites	:	Arduino

	Keywords		:	Arduino; RGB;

	Disclaimer		:	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 	INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef LEDstrip_h
	#define LEDstrip_h

	#include "Arduino.h"

	class LEDstrip
	{
	  public:
		LEDstrip();
		void DefineRGBLED(int Rpin, int Gpin, int Bpin);
		void DefineSingleColourLED(int LEDpin);
		void SetRGBColour(byte R, byte G, byte B);
		void SetHSLColour(int H, int S, int L);
		void SetRandomColour();
		void SetWhiteLight(byte intensity);
		void LEDstripOFF();
		void SetRedLight(byte intensity);
		void SetGreenLight(byte intensity);
		void SetBlueLight(byte intensity);
		void SetRGBRandomColour(byte _R1, byte _G1, byte _B1, byte Variation);
		void SetHSLrandomColour(int StartHueAngle, int maxAngleStep);
		void RGB2HSL(byte R, byte G, byte B);
		void HSL2RGB(int H, int S, int L);
		int RedVal;
		int GreenVal;
		int BlueVal;
		int HueVal;
		int SaturationVal;
		int LightnessVal;
	  private:
		int _Rpin;
		int _Gpin;
		int _Bpin;
		boolean isRGB;
		float Hue_2_RGB(float v1,float v2,float vH);
	};
#endif