#include <DMXSerial.h>
#define MAX_VALUE 255
#define MIN_VALUE 0

struct Segment
{
	int dmxChannel;
	int value;
};

struct SevenSeg
{
	Segment segA;
	Segment segB;
	Segment segC;
	Segment segD;
	Segment segE;
	Segment segF;
	Segment segG;
};

void LightZero(SevenSeg &mySeg)
{
	mySeg.segA.value = MAX_VALUE;
	mySeg.segB.value = MAX_VALUE;
	mySeg.segC.value = MAX_VALUE;
	mySeg.segD.value = MAX_VALUE;
	mySeg.segE.value = MAX_VALUE;
	mySeg.segF.value = MAX_VALUE;
	mySeg.segG.value = MIN_VALUE;
}

void LightOne(SevenSeg &mySeg)
{
	mySeg.segA.value = MIN_VALUE;
	mySeg.segB.value = MAX_VALUE;
	mySeg.segC.value = MAX_VALUE;
	mySeg.segD.value = MIN_VALUE;
	mySeg.segE.value = MIN_VALUE;
	mySeg.segF.value = MIN_VALUE;
	mySeg.segG.value = MIN_VALUE;
}

void LightTwo(SevenSeg &mySeg)
{
	mySeg.segA.value = MAX_VALUE;
	mySeg.segB.value = MAX_VALUE;
	mySeg.segC.value = MIN_VALUE;
	mySeg.segD.value = MAX_VALUE;
	mySeg.segE.value = MAX_VALUE;
	mySeg.segF.value = MIN_VALUE;
	mySeg.segG.value = MAX_VALUE;
}

void LightThree(SevenSeg &mySeg)
{
	mySeg.segA.value = MAX_VALUE;
	mySeg.segB.value = MAX_VALUE;
	mySeg.segC.value = MAX_VALUE;
	mySeg.segD.value = MAX_VALUE;
	mySeg.segE.value = MIN_VALUE;
	mySeg.segF.value = MIN_VALUE;
	mySeg.segG.value = MAX_VALUE;
}

void LightFour(SevenSeg &mySeg)
{
	mySeg.segA.value = MIN_VALUE;
	mySeg.segB.value = MAX_VALUE;
	mySeg.segC.value = MAX_VALUE;
	mySeg.segD.value = MIN_VALUE;
	mySeg.segE.value = MIN_VALUE;
	mySeg.segF.value = MAX_VALUE;
	mySeg.segG.value = MAX_VALUE;
}

void LightFive(SevenSeg &mySeg)
{
	mySeg.segA.value = MAX_VALUE;
	mySeg.segB.value = MIN_VALUE;
	mySeg.segC.value = MAX_VALUE;
	mySeg.segD.value = MAX_VALUE;
	mySeg.segE.value = MIN_VALUE;
	mySeg.segF.value = MAX_VALUE;
	mySeg.segG.value = MAX_VALUE;
}

void LightSix(SevenSeg &mySeg)
{
	mySeg.segA.value = MAX_VALUE;
	mySeg.segB.value = MIN_VALUE;
	mySeg.segC.value = MAX_VALUE;
	mySeg.segD.value = MAX_VALUE;
	mySeg.segE.value = MAX_VALUE;
	mySeg.segF.value = MAX_VALUE;
	mySeg.segG.value = MAX_VALUE;
}

void LightSeven(SevenSeg &mySeg)
{
	mySeg.segA.value = MAX_VALUE;
	mySeg.segB.value = MAX_VALUE;
	mySeg.segC.value = MAX_VALUE;
	mySeg.segD.value = MIN_VALUE;
	mySeg.segE.value = MIN_VALUE;
	mySeg.segF.value = MIN_VALUE;
	mySeg.segG.value = MIN_VALUE;
}

void LightEight(SevenSeg &mySeg)
{
	mySeg.segA.value = MAX_VALUE;
	mySeg.segB.value = MAX_VALUE;
	mySeg.segC.value = MAX_VALUE;
	mySeg.segD.value = MAX_VALUE;
	mySeg.segE.value = MAX_VALUE;
	mySeg.segF.value = MAX_VALUE;
	mySeg.segG.value = MAX_VALUE;
}

void LightNine(SevenSeg &mySeg)
{
	mySeg.segA.value = MAX_VALUE;
	mySeg.segB.value = MAX_VALUE;
	mySeg.segC.value = MAX_VALUE;
	mySeg.segD.value = MAX_VALUE;
	mySeg.segE.value = MIN_VALUE;
	mySeg.segF.value = MAX_VALUE;
	mySeg.segG.value = MAX_VALUE;
}

void LightNumber(int num, SevenSeg &mySeg)
{
	if(num == 0)
	{
		LightZero(mySeg);
	}
	else if(num == 1)
	{
		LightOne(mySeg);
	}
	else if(num == 2)
	{
		LightTwo(mySeg);
	}
	else if(num == 3)
	{
		LightThree(mySeg);
	}
	else if(num == 4)
	{
		LightFour(mySeg);
	}
	else if(num == 5)
	{
		LightFive(mySeg);
	}
	else if(num == 6)
	{
		LightSix(mySeg);
	}
	else if(num == 7)
	{
		LightSeven(mySeg);
	}
	else if(num == 8)
	{
		LightEight(mySeg);
	}
	else if(num == 9)
	{
		LightNine(mySeg);
	}
}

void LightTwoDigitNumber(int number, SevenSeg &segLeft, SevenSeg &segRight)
{
	int TensPlace = (number/10)%10;
	int onesPlace = number%10;
	LightNumber(TensPlace, segLeft);
	LightNumber(onesPlace, segRight);
}


/*
	Standard 7 Seg Display Lettering

  		  A
      ==========
     |          |
    F|		    | B
     |     G    |
     |==========|
     |          |
    E|		    | C
	 |     D	|
	  ==========

*/

SevenSeg digit1;
SevenSeg digit2;
SevenSeg digit3;
SevenSeg digit4;
SevenSeg digit5;
SevenSeg digit6;

void Digit1Setup()
{
	digit1.segA.dmxChannel = 0;
	digit1.segB.dmxChannel = 1;
	digit1.segC.dmxChannel = 2;
	digit1.segD.dmxChannel = 3;
	digit1.segE.dmxChannel = 4;
	digit1.segF.dmxChannel = 5;
	digit1.segG.dmxChannel = 6;
}

void Digit2Setup()
{
	digit2.segA.dmxChannel = 7;
	digit2.segB.dmxChannel = 8;
	digit2.segC.dmxChannel = 9;
	digit2.segD.dmxChannel = 10;
	digit2.segE.dmxChannel = 11;
	digit2.segF.dmxChannel = 12;
	digit2.segG.dmxChannel = 13;
}

void Digit3Setup()
{
	digit3.segA.dmxChannel = 14;
	digit3.segB.dmxChannel = 15;
	digit3.segC.dmxChannel = 16;
	digit3.segD.dmxChannel = 17;
	digit3.segE.dmxChannel = 18;
	digit3.segF.dmxChannel = 19;
	digit3.segG.dmxChannel = 20;
}

void Digit4Setup()
{
	digit4.segA.dmxChannel = 21;
	digit4.segB.dmxChannel = 22;
	digit4.segC.dmxChannel = 23;
	digit4.segD.dmxChannel = 24;
	digit4.segE.dmxChannel = 25;
	digit4.segF.dmxChannel = 26;
	digit4.segG.dmxChannel = 27;
}

void Digit5Setup()
{
	digit5.segA.dmxChannel = 28;
	digit5.segB.dmxChannel = 29;
	digit5.segC.dmxChannel = 30;
	digit5.segD.dmxChannel = 31;
	digit5.segE.dmxChannel = 32;
	digit5.segF.dmxChannel = 33;
	digit5.segG.dmxChannel = 34;
}

void Digit6Setup()
{
	digit6.segA.dmxChannel = 35;
	digit6.segB.dmxChannel = 36;
	digit6.segC.dmxChannel = 37;
	digit6.segD.dmxChannel = 38;
	digit6.segE.dmxChannel = 39;
	digit6.segF.dmxChannel = 40;
	digit6.segG.dmxChannel = 41;
}

void SetupSevenSegDigits()
{
	Digit1Setup();
	Digit2Setup();
	Digit3Setup();
	Digit4Setup();
	Digit5Setup();
	Digit6Setup();
}

void LightSevenSegDigit(SevenSeg &digit)
{
	DMXSerial.write(digit.segA.dmxChannel, digit.segA.value);
	DMXSerial.write(digit.segB.dmxChannel, digit.segB.value);
	DMXSerial.write(digit.segC.dmxChannel, digit.segC.value);
	DMXSerial.write(digit.segD.dmxChannel, digit.segD.value);
	DMXSerial.write(digit.segE.dmxChannel, digit.segE.value);
	DMXSerial.write(digit.segF.dmxChannel, digit.segF.value);
	DMXSerial.write(digit.segG.dmxChannel, digit.segG.value);
}

void LightSevenSegDisplays()
{
	LightSevenSegDigit(digit1);
	LightSevenSegDigit(digit2);
	LightSevenSegDigit(digit3);
	LightSevenSegDigit(digit4);
	LightSevenSegDigit(digit5);
	LightSevenSegDigit(digit6);
}

void setup() {

  SetupSevenSegDigits();
  DMXSerial.init(DMXController);

} // setup


void loop() {
  
  LightNumber(1, digit1);
  LightNumber(2, digit2);
  LightNumber(3, digit3);
  LightNumber(4, digit4);
  LightNumber(5, digit5);
  LightNumber(6, digit6);

  // Pretty much will be used for brightness
  LightSevenSegDisplays();

  delayMicroseconds(2000); // wait a little bit
} // loop