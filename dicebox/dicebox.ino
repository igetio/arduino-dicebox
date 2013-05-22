int randRoll; // output of roll
int dieCount; // number of dice
int dieSize; // die Size
int dieMax; // max value for all dice (used by random())
int dieArray[9] = {2,3,4,6,8,10,12,20,100};  // array of possible dice
int curDie; // Sets current die from dieArray at startup
int lastDie;
int lastCount;
char output_buffer[10];

const int decDiePin = 2;
const int decCountPin = 3;
const int rollPin = 4;
const int incDiePin = 6;
const int incCountPin = 5;

int rollBtnState = 0;
int decDieState = 0;
int decCountState = 0;
int incDieState = 0;
int incCountState = 0;

// include the library code:
#include "Wire.h"
#include "LiquidCrystal.h"

// Connect via i2c, default address #0 (A0-A2 not jumpered)
LiquidCrystal lcd(0);

void setup(){
//sets default to 1d6 and sets up random seed for dice rolls
  Serial.begin(9600);
  randomSeed(analogRead(0));
  curDie = 7;
  dieSize = dieArray[curDie];
  dieCount = 1;
  pinMode(rollPin, INPUT);
  pinMode(decDiePin, INPUT);
  pinMode(decCountPin, INPUT);
  pinMode(incDiePin, INPUT);
  pinMode(incCountPin, INPUT);

    // set up the LCD's number of rows and columns: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Dice: 1d20");
  lcd.setCursor(0, 1);
lcd.print("Roll: ???");
}

void loop(){  
  rollBtnState = digitalRead(rollPin);
  if (rollBtnState == LOW) { 
  rollThemDice();
  }
  
  decDieState = digitalRead(decDiePin);
  if (decDieState == LOW) { 
    curDie = decButton(curDie, 0, 8);
    dieSize = dieArray[curDie];
          whatURoll();
  }
  
  decCountState = digitalRead(decCountPin);
  if (decCountState == LOW) { 
    dieCount = decButton(dieCount, 1, 5);
          whatURoll();
  }
  
    incDieState = digitalRead(incDiePin);
  if (incDieState == LOW) { 
    curDie = incButton(curDie, 0, 8);
    dieSize = dieArray[curDie];
            whatURoll();
  }
  
  incCountState = digitalRead(incCountPin);
  if (incCountState == LOW) { 
    dieCount = incButton(dieCount, 1, 5);
            whatURoll();
  }
}

//generic function for nav to increment through array
int incButton(int current, int min, int max ) {
 if ( current == max ){
  current = min;
 }
 else{
  current++;
 }
 delay(500);
 return current;
}

//generic function for nav to decrement through array
int decButton(int current, int min, int max ) {
 if ( current== min ){
  current= max ;
    }
 else{
  current--;
	}
 delay(500);
 return current;
}
	
	
//Function to roll the dice
void rollThemDice(){
  
 //Sets up max size and ramdom roll based on selected range
  dieMax = dieCount * dieSize +1;
  randRoll = random(dieCount, dieMax);

 // output status to let user know new roll is being generated
 lcd.setCursor(6, 1);
 lcd.print("-Rolling-");
 delay(150);

 // blank out display before revealing roll
 lcd.setCursor(6, 1);
 snprintf_P(output_buffer, 10, PSTR("%d           "), randRoll);
 lcd.print(output_buffer); 
 
 // Stores last roll for display if die type or count is changed  
 lastDie = dieSize;
 lastCount = dieCount;
 // Prevents rerolling from electrical bounce or a slow finger. 	
 delay(500);
}

// function to pick die type and count of dice
void whatURoll(){
  
 // generate output for curent dice count and size in 1d20 format
 snprintf_P(output_buffer, 10, PSTR("%dd%d  "), dieCount, dieSize);
  lcd.setCursor(6, 0);
 lcd.print(output_buffer); 
snprintf_P(output_buffer, 10, PSTR("%dd%d %d   "), lastCount, lastDie, randRoll);
 lcd.setCursor(6, 1);
 lcd.print(output_buffer); 
}
