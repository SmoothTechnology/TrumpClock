#include <DMXSerial.h>

#define MAX_VALUE 255
#define MIN_VALUE 0
//#define USE_GPS

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
int curHour = 0;
int curMinute = 0;
int curSecond = 0;
int curDay = 0;
int curMonth = 0;
int curYear = 0;

// Define Destination Date
int destinationHour = 0;
int destinationDay = 0;
int destinationMonth = 0;
int destinationYear = 0;


/// GPS TIME GETTING
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2);

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
    curMinute 	= GPS.minute;
    curSecond 	= GPS.seconds;
    curDay 		= GPS.day;
    curMonth 	= GPS.month;
    curYear 	= GPS.year;
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

void CalculateSevenSegmentNumbers()
{

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

unsigned long number = 123456;
unsigned long lastMillis = 0;
void CountTest()
{
	if(millis() - lastMillis > 1000)
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

void setup() {

#ifdef USE_GPS
	SetupGPS();
#endif

  SetupSevenSegDigits();
  DMXSerial.init(DMXController);

} // setup


void loop() {

#ifdef USE_GPS
	ReadGPS();
	CalculateSevenSegmentNumbers();
#else
 	//LightTestNumbers();
 	CountTest();
#endif
  
  // Pretty much will be used for brightness
  LightSevenSegDisplays();

  delayMicroseconds(2000); // wait a little bit
} // loop