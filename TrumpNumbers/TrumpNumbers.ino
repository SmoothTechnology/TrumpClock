#include <DMXSerial.h>

int MAX_VALUE = 255;
int MIN_VALUE = 0;
#define USE_GPS

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

// Current Date and Time
int curHour = 9;
int curMinute = 0;
int curSecond = 0;
int curDay = 11;
int curMonth = 5;
int curYear = 2017;

// Define Destination Date
int destinationHour = 24;
int destinationDay = 19;
int destinationMonth = 1;
int destinationYear = 2021;

//
//// Define FAKE Destination Date
//int destinationHour = 10;
//int destinationDay = 12;
//int destinationMonth = 5;
//int destinationYear = 2017;

int dayDifference = 0;
int hourDifference = 0;

// DATE CALCULATION
int days_in_month[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

struct date {
  int day;
  int month;
  int year;
};

int leap_year(int year) {
    if(year%400==0) return 1;

    if(year%4==0 && year%100!=0) return 1;

    return 0;
}

int correct(date &d) {
    if(d.day < 1 || d.day > days_in_month[d.month]) return 0;

    if(d.month < 1 || d.month > 12) return 0;

    return 1;
}

int number_of_days(date &d) {
    int result = 0;
    int i;

    for(i=1; i < d.year; i++) {
        if(leap_year(i))
            result += 366;
        else
            result += 365;
    }

    for(i=1; i < d.month; i++) {
        result += days_in_month[i];

        if(leap_year(d.year) && i == 2) result++;
    }

    result += d.day;
    return result;
}

void GetTimeDifference()
{
	date current;
	current.day = curDay;
	current.month = curMonth;
	current.year = curYear;

	date destination;
	destination.day = destinationDay;
	destination.month = destinationMonth;
	destination.year = destinationYear;

	int destDays = number_of_days(destination);
	int curDays = number_of_days(current);

	hourDifference = abs(destinationHour - curHour);
	dayDifference = destDays - curDays;

	if(dayDifference == 0 && hourDifference == 0)
	{
		dayDifference = 0;
		hourDifference = 0;
    playEndingAnimation();
	}
}

/// GPS TIME GETTING
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(8, 7);

Adafruit_GPS GPS(&mySerial);

// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences. 
#define GPSECHO  false

// this keeps track of whether we're using the interrupt
// off by default!
boolean usingInterrupt = false;
void useInterrupt(boolean); // Func prototype keeps Arduino 0023 happy


void SetupGPS()
{

  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);
  
  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  
  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate

  // Request updates on antenna status, comment out to keep quiet
  GPS.sendCommand(PGCMD_ANTENNA);

  useInterrupt(true);

  delay(1000);
  // Ask for firmware version
  mySerial.println(PMTK_Q_RELEASE);
}

SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
#ifdef UDR0
  if (GPSECHO)
    if (c) UDR0 = c;  
#endif
}

void useInterrupt(boolean v) {
  if (v) 
  {
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } 
  else 
  {
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}

uint32_t timer = millis();
void ReadGPS()
{
  if (GPS.newNMEAreceived()) 
  {
	  if (!GPS.parse(GPS.lastNMEA())) 
	      return;  
  }

  if (timer > millis())  timer = millis();

  if (millis() - timer > 2000) 
  { 
    timer = millis();
    
    curHour	 	= GPS.hour;

    // Adjust to EST FROM GMT
    curHour = curHour - 5;
    if(curHour < 0)
    {
    	curHour = 24+curHour;
    }

    curMinute 	= GPS.minute;
    curSecond 	= GPS.seconds;
    curDay 		= GPS.day;
    curMonth 	= GPS.month;
    curYear 	= GPS.year + 2000; // Adjust for GPS only returning last 2 digits
  }
}


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

void CalculateSevenSegmentNumbers()
{
	GetTimeDifference();

	LightNumber((dayDifference/1000)%10, digit1);
	LightNumber((dayDifference/100)%10, digit2);
	LightNumber((dayDifference/10)%10, digit3);
	LightNumber((dayDifference)%10, digit4);
	LightNumber((hourDifference/10)%10, digit5);
	LightNumber((hourDifference)%10, digit6);

}

void LightTestNumbers()
{
  LightNumber(3, digit1);
  LightNumber(3, digit2);
  LightNumber(3, digit3);
  LightNumber(3, digit4);
  LightNumber(3, digit5);
  LightNumber(3, digit6);
}

unsigned long number = 123456;
unsigned long lastMillis = 0;
void CountTest()
{
	if(millis() - lastMillis > 10)
	{
		lastMillis = millis();
		number++;
	}

	LightNumber((number/100000)%10, digit1);
	LightNumber((number/10000)%10, digit2);
	LightNumber((number/1000)%10, digit3);
	LightNumber((number/100)%10, digit4);
	LightNumber((number/10)%10, digit5);
	LightNumber((number)%10, digit6);
}

void FakeCount()
{
	if(millis() - lastMillis > 250)
	{
		lastMillis = millis();
		
		curHour++;

		if(curHour > 24)
		{
			curHour = 0;
			curDay++;

			if(curDay > days_in_month[curMonth])
			{
				curDay = 1;
				curMonth++;
				if(curMonth > 12)
				{
					curMonth = 1;
					curYear++;
				}
			}
		}
	}
}

void playEndingAnimation(){
  while(true){
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
	
	DMXSerial.write(COLON_CHANNEL, curColonValue);
}

void setup() {

#ifdef USE_GPS
	SetupGPS();
#endif

  SetupSevenSegDigits();
  DMXSerial.init(DMXController);

} // setup

void ReadPotentiometer()
{
	int potValue = analogRead(A0);
	potValue = 1023-potValue;
	MAX_VALUE = potValue/4;
}

void loop() {
  
#ifdef USE_GPS
	ReadGPS();
	CalculateSevenSegmentNumbers();
#else
 	//LightTestNumbers();
 	//CountTest();
 	CalculateSevenSegmentNumbers();
 	FakeCount();
#endif
  
  ReadPotentiometer();
  // Pretty much will be used for brightness
  LightSevenSegDisplays();
  DoColon();

  delayMicroseconds(2000); // wait a little bit
} // loop
