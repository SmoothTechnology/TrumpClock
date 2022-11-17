#define USE_DMX

#ifdef USE_DMX
#include <DMXSerial.h>
#endif

#define START_MINUTE 10
#define START_SECOND 20

int maxSeconds = 0;
int secondsLeft = 0;

int MAX_VALUE = 255;
int MIN_VALUE = 0;

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

// BEGIN TRUMP NUMBERS
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


void LightOff(SevenSeg &mySeg)
{
  mySeg.segA.value = MIN_VALUE;
  mySeg.segB.value = MIN_VALUE;
  mySeg.segC.value = MIN_VALUE;
  mySeg.segD.value = MIN_VALUE;
  mySeg.segE.value = MIN_VALUE;
  mySeg.segF.value = MIN_VALUE;
  mySeg.segG.value = MIN_VALUE;
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
 else if(num == -1)
  {
    LightOff(mySeg);
  }
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

#define OFFSETDIGIT1 0
#define OFFSETDIGIT2 10
#define OFFSETDIGIT3 20
#define OFFSETDIGIT4 30
#define OFFSETDIGIT5 40
#define OFFSETDIGIT6 50

void Digit1Setup()
{
	digit1.segA.dmxChannel = OFFSETDIGIT1 + 5;
	digit1.segB.dmxChannel = OFFSETDIGIT1 + 4;
	digit1.segC.dmxChannel = OFFSETDIGIT1 + 6;
	digit1.segD.dmxChannel = OFFSETDIGIT1 + 7;
	digit1.segE.dmxChannel = OFFSETDIGIT1 + 1;
	digit1.segF.dmxChannel = OFFSETDIGIT1 + 2;
	digit1.segG.dmxChannel = OFFSETDIGIT1 + 3;
}

void Digit2Setup()
{
	digit2.segA.dmxChannel = OFFSETDIGIT2 + 5;
	digit2.segB.dmxChannel = OFFSETDIGIT2 + 4;
	digit2.segC.dmxChannel = OFFSETDIGIT2 + 6;
	digit2.segD.dmxChannel = OFFSETDIGIT2 + 7;
	digit2.segE.dmxChannel = OFFSETDIGIT2 + 1;
	digit2.segF.dmxChannel = OFFSETDIGIT2 + 2;
	digit2.segG.dmxChannel = OFFSETDIGIT2 + 3;
}

void Digit3Setup()
{
	digit3.segA.dmxChannel = OFFSETDIGIT3 + 5;
	digit3.segB.dmxChannel = OFFSETDIGIT3 + 4;
	digit3.segC.dmxChannel = OFFSETDIGIT3 + 6;
	digit3.segD.dmxChannel = OFFSETDIGIT3 + 7;
	digit3.segE.dmxChannel = OFFSETDIGIT3 + 1;
	digit3.segF.dmxChannel = OFFSETDIGIT3 + 2;
	digit3.segG.dmxChannel = OFFSETDIGIT3 + 3;
}

void Digit4Setup()
{
	digit4.segA.dmxChannel = OFFSETDIGIT4 + 5;
	digit4.segB.dmxChannel = OFFSETDIGIT4 + 4;
	digit4.segC.dmxChannel = OFFSETDIGIT4 + 6;
	digit4.segD.dmxChannel = OFFSETDIGIT4 + 7;
	digit4.segE.dmxChannel = OFFSETDIGIT4 + 1;
	digit4.segF.dmxChannel = OFFSETDIGIT4 + 2;
	digit4.segG.dmxChannel = OFFSETDIGIT4 + 3;
}

void Digit5Setup()
{
	digit5.segA.dmxChannel = OFFSETDIGIT5 + 5;
	digit5.segB.dmxChannel = OFFSETDIGIT5 + 4;
	digit5.segC.dmxChannel = OFFSETDIGIT5 + 6;
	digit5.segD.dmxChannel = OFFSETDIGIT5 + 7;
	digit5.segE.dmxChannel = OFFSETDIGIT5 + 1;
	digit5.segF.dmxChannel = OFFSETDIGIT5 + 2;
	digit5.segG.dmxChannel = OFFSETDIGIT5 + 3;
}

void Digit6Setup()
{
	digit6.segA.dmxChannel = OFFSETDIGIT6 + 5;
	digit6.segB.dmxChannel = OFFSETDIGIT6 + 4;
	digit6.segC.dmxChannel = OFFSETDIGIT6 + 6;
	digit6.segD.dmxChannel = OFFSETDIGIT6 + 7;
	digit6.segE.dmxChannel = OFFSETDIGIT6 + 1;
	digit6.segF.dmxChannel = OFFSETDIGIT6 + 2;
	digit6.segG.dmxChannel = OFFSETDIGIT6 + 3;
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
#ifdef USE_DMX
	DMXSerial.write(digit.segA.dmxChannel, digit.segA.value);
	DMXSerial.write(digit.segB.dmxChannel, digit.segB.value);
	DMXSerial.write(digit.segC.dmxChannel, digit.segC.value);
	DMXSerial.write(digit.segD.dmxChannel, digit.segD.value);
	DMXSerial.write(digit.segE.dmxChannel, digit.segE.value);
	DMXSerial.write(digit.segF.dmxChannel, digit.segF.value);
	DMXSerial.write(digit.segG.dmxChannel, digit.segG.value);
#endif
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

void LightTestNumbers()
{
  LightNumber(1, digit1);
  LightNumber(2, digit2);
  LightNumber(3, digit3);
  LightNumber(4, digit4);
  LightNumber(5, digit5);
  LightNumber(6, digit6);
}

void LightMinuteSecondNumbers()
{
	int minutesLeftToDisplay = secondsLeft / 60;
	int secondsLeftToDisplay = secondsLeft % 60;

#ifndef USE_DMX
	Serial.print(minutesLeftToDisplay/10);
	Serial.print(minutesLeftToDisplay%10);
	Serial.print(":");
	Serial.print(secondsLeftToDisplay/10);
	Serial.println(secondsLeftToDisplay%10);
#endif

	LightNumber(0, digit1); // Black out first 2 digits
	LightNumber(0, digit2); // Black out first 2 digits

	// Light Minutes on next 2 digits
	LightNumber((minutesLeftToDisplay/10)%10, digit3);
	LightNumber((minutesLeftToDisplay)%10, digit4);

	// Light Seconds on final 2 digits
	LightNumber((secondsLeftToDisplay/10)%10, digit5);
	LightNumber((secondsLeftToDisplay)%10, digit6);
}

void playEndingAnimation(){
	digitalWrite(13, HIGH);

  while(true){
#ifndef USE_DMX
	Serial.println("00:00");
#endif

    LightNumber(-1, digit1);
    LightNumber(-1, digit2);
    LightNumber(-1, digit3);
    LightNumber(-1, digit4);
    LightNumber(-1, digit5);
    LightNumber(-1, digit6);
    delay(750);
    ReadPotentiometer();
    // Pretty much will be used for brightness
    LightSevenSegDisplays();

#ifndef USE_DMX
	Serial.println("  :  ");
#endif

    LightNumber(0, digit1);
    LightNumber(0, digit2);
    LightNumber(0, digit3);
    LightNumber(0, digit4);
    LightNumber(0, digit5);
    LightNumber(0, digit6);
    delay(750);
    ReadPotentiometer();
    // Pretty much will be used for brightness
    LightSevenSegDisplays();
  }
}

#define DO_FADE
#define ONOFF_TIME 1000 // Peak and Trough hold time for the fade, and blinking
#define FADE_TIME 1000 // Ramp time for fade
#define FADE_INTERVAL 20 // Frame Rate for Fade
#define COLON_CHANNEL 58

unsigned long LastTime = 0;
unsigned long fadeTime = 0;
int curColonValue = MIN_VALUE;

// State 0, 2 are on off
// State 1, 3 are fade
int fadeState = 0;

void DoColonBlink()
{
	if(millis() - LastTime > ONOFF_TIME)
	{
		LastTime = millis();

		if(curColonValue == MIN_VALUE)
		{
			curColonValue = MAX_VALUE;
		}
		else 
		{
			curColonValue = MIN_VALUE;
		}
	}
}

void DoColonFade()
{
	int divisor = FADE_TIME / FADE_INTERVAL;
	int fadeValue = (MAX_VALUE - MIN_VALUE) / divisor;

	if(fadeState == 0 || fadeState == 2)
	{
		if(fadeState == 0)
		{
			curColonValue = MIN_VALUE;
		}
		else
		{
			curColonValue = MAX_VALUE;
		}

		if(millis() - LastTime > ONOFF_TIME)
		{
			LastTime = millis();
			fadeTime = millis();

			if(fadeState == 0)
			{
				fadeState = 1;
			}
			else
			{
				fadeState = 3;
			}
		}
	}
	else if(fadeState == 1 || fadeState == 3)
	{
		if(millis() - LastTime > FADE_INTERVAL)
		{
			LastTime = millis() - ((millis()-LastTime)-FADE_INTERVAL);

			if(fadeState == 1)
			{
				curColonValue = curColonValue + fadeValue;
			}
			else
			{
				curColonValue = curColonValue - fadeValue;
			}

		}

		if(millis() - fadeTime > FADE_TIME)
		{
			fadeTime = millis();
			LastTime = millis();

			if(fadeState == 1)
			{
				fadeState = 2;
			}
			else
			{
				fadeState = 0;
			}
		}
	}
	else
	{
		fadeState = 0;
	}
}

void DoColon()
{
#ifdef DO_FADE
	DoColonFade();
#else
	DoColonBlink();
#endif

	if(curColonValue > MAX_VALUE)
	{
		curColonValue = MAX_VALUE;
	}
	else if(curColonValue < MIN_VALUE)
	{
		curColonValue = MIN_VALUE;
	}
	
#ifdef USE_DMX
	DMXSerial.write(COLON_CHANNEL, curColonValue);
#endif
}

unsigned long startMillis = 0;
void setup() {

	pinMode(13, OUTPUT);

	maxSeconds = START_MINUTE * 60 + START_SECOND;
	secondsLeft = maxSeconds;


	SetupSevenSegDigits();
#ifdef USE_DMX
	DMXSerial.init(DMXController);
#else
	Serial.begin(9600);
#endif

	// Seed the counter when starting... Probably could just use millis directly, but this feels more reliable
	startMillis = millis();

} // setup

void ReadPotentiometer()
{
	int potValue = analogRead(A0);
	potValue = 1023-potValue;
	MAX_VALUE = potValue/4;
}

void loop() {

	unsigned long timeElapsed = millis() - startMillis;

	secondsLeft = maxSeconds - (timeElapsed/1000);

	digitalWrite(13, secondsLeft%2);

	// When we have no more seconds left, blink all zeroes
	if(secondsLeft == 0){
		playEndingAnimation();
	}
  
	LightMinuteSecondNumbers();
	ReadPotentiometer();
	// Pretty much will be used for brightness
	LightSevenSegDisplays();
	DoColon();

	delayMicroseconds(2000); // wait a little bit
} // loop
