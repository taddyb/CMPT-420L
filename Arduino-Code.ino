
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// set up a constant for the push button
const int switchPin = 6;

// set up a constant for the push button
const int inputPin = 7;

//boolean to see if the device is unlocked
boolean unlock = true;

//digital input values for the lights
const int analogPin0 = 14;
const int analogPin1 = 10;
const int analogPin2 = 9;
const int analogPin3 = 8;

// variable to hold the value of the switch pin
int switchState = 0;

// variable to hold the value of the switch pin
int inputState = 0;

//variable to hold the combination value
int var = 1;

//variable to hold the input count
int counter = 0;

//vars to hold the inputted numbers
int input1 = 0;
int input2 = 0;
int input3 = 0;
int input4 = 0;

//variable to hold the combination for the first pin
int combination1 = 1;

//variable to hold the combination for the second pin
int combination2 = 7;

//variable to hold the combination for the third pin
int combination3 = 7;

//variable to hold the combination for the fourth pin
int combination4 = 1;

// variable to hold previous value of the switch pin
int prevSwitchState = 0;

// variable to hold previous value of the switch pin
int prevInputState = 0;

//turns on song mode
boolean songMode = false;

void setup() {
  Serial.begin(9600);
  // set up the number of columns and rows on the LCD
  lcd.begin(16, 2);

  pinMode(analogPin0, OUTPUT);
  pinMode(analogPin1, OUTPUT);
  pinMode(analogPin2, OUTPUT);
  pinMode(analogPin3, OUTPUT);

  //plays the function for the startup song
  startingSong();

  // set up the switch pin as an input
  pinMode(switchPin, INPUT);

  // set up the switch pin as an input
  pinMode(inputPin, INPUT);

  // Print a message to the LCD.
  lcd.print("Enter Combo");
  // set the cursor to column 0, line 1
  lcd.setCursor(0,1);
  lcd.print(var);
}

void loop() {
  if(!songMode){
  // check the status of the switch
  switchState = digitalRead(switchPin);

  //check the status of the switch
  inputState = digitalRead(inputPin);

  // compare the switchState to its previous state
  if ((switchState != prevSwitchState) && counter < 4) {
    
    // if the state has changed from HIGH to LOW you know that the ball has been
    // tilted from one direction to the other
    if (switchState == LOW) {
     var ++;
     if(var == 10){
      var = 0;
     }
      lcd.setCursor(0, 1);
       // print to the second line
      lcd.print(var);

       }
  }

   if ((inputState != prevInputState)) {
      //if the state changes the user wants to lock in their input
      if (inputState == LOW ) {
        lcd.clear();
        lcd.setCursor(0,0);
        switch(counter){
           case 0:
           digitalWrite(analogPin0, HIGH);
           input1 = var;
           lcd.print("Enter next #");
           lcd.setCursor(0, 1);
           // print to the second line
           var = 1;
           lcd.print(var);
           counter ++;
           break;

           case 1:
           digitalWrite(analogPin1, HIGH);
           input2 = var;
           lcd.print("Enter next #");
           lcd.setCursor(0, 1);
           // print to the second line
           var = 1;
           lcd.print(var);
           counter ++;
           break;

           case 2:
            digitalWrite(analogPin2, HIGH);
           input3 = var;
           lcd.print("Enter next #");
           lcd.setCursor(0, 1);
           // print to the second line
           var = 1;
           lcd.print(var);
           counter ++;
           break;

           case 3:
           digitalWrite(analogPin3, HIGH);
           input4 = var;
           lcd.clear();
           lcd.print("Checking DB");
           delay(1000);
           digitalWrite(analogPin3, LOW);
           lcd.setCursor(0,1);
           lcd.print(".");
           delay(1000);
           digitalWrite(analogPin2, LOW);
           lcd.setCursor(0,1);
           lcd.print("..");
           delay(1000);
           digitalWrite(analogPin1, LOW);
           lcd.setCursor(0,1);
           lcd.print("...");
           delay(1000);
           lcd.clear();
           lcd.setCursor(0,0);
           //checks combination
           if(input1 != combination1){
             unlock = false;
           } else if(input2 != combination2){
            unlock = false;
           } else if(input3 != combination3){
             unlock = false;
           } else  if(input3 != combination3){
            unlock = false;
           }

           if(unlock){
            songMode = true;
            digitalWrite(analogPin1, HIGH);
            digitalWrite(analogPin2, HIGH);
            digitalWrite(analogPin3, HIGH);
            lcd.clear();
            lcd.print("Unlocked");
            var = 0;
            lcd.clear();
            lcd.print("Select song");
            lcd.setCursor(0,1);
            lcd.print(var);
            
           } else {
            digitalWrite(analogPin0, LOW);
            lcd.print("Incorrect Combo");
            lcd.setCursor(0,1);
            lcd.print("press 2 clear");
            input1 = 0;
            input2 = 0;
            input3 = 0;
            input4 = 0;
            counter ++;
           }
           break;

           case 4:
            // Print a message to the LCD.
            lcd.print("Enter Combo");
            // set the cursor to column 0, line 1
            lcd.setCursor(0,1);
            lcd.print(var);
            counter = 0;
            unlock = true;
            break;
        }
      }
   }
  
  // save the current switch state as the last state
  prevSwitchState = switchState;

  //saving the input button state
  prevInputState = inputState;
  } else{

     switchState = digitalRead(switchPin);

  //check the status of the switch
  inputState = digitalRead(inputPin);

  // compare the switchState to its previous state
  if (switchState != prevSwitchState){
     if (switchState == LOW) {
       var ++;
       if(var  > 2){
        var = 0;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Select song");
       }
        lcd.setCursor(0, 1);
       if( var != 2){
        lcd.print(var);
       } else{
        lcd.print("exit");
       }
     }
  }

   if ((inputState != prevInputState)) {
    if(inputState == LOW){
       lcd.clear();
        lcd.setCursor(0,0);
        switch(var){
          case 0:
          lcd.print("Sorry, No");
          lcd.setCursor(0,1);
          lcd.print("Song Here");
          delay(1000);
          lcd.clear();
           lcd.setCursor(0,0); 
        lcd.print("Select Song");
        lcd.setCursor(0,1);
        lcd.print(var);
          break;

          case 1:
          lcd.print("Playing:");
          lcd.setCursor(0,1);
          lcd.print("Butterfly Effect");
          delay(1000);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("by");
          lcd.setCursor(0,1);
          lcd.print("Travis Scott");
          delay(1000);
          lcd.clear();
          travisScott(4);
           lcd.setCursor(0,0); 
        lcd.print("Select song");
        lcd.setCursor(0,1);
        lcd.print(var);
          break;
          
          case 2:
          songMode = false;
          unlock = false; 
          counter = 0;
          var = 0;
          lcd.clear();
          lcd.print("Bye");
          delay(1000);
          lcd.clear();
           lcd.print("Enter Combo");
          // set the cursor to column 0, line 1
          lcd.setCursor(0,1);
          lcd.print(var);
          break; 
        }
    }
   }
    
    // save the current switch state as the last state
  prevSwitchState = switchState;

  //saving the input button state
  prevInputState = inputState;
  }
}

void startingSong(){
  tone(13, 440);
 digitalWrite(analogPin0, HIGH);
  delay(500);
  tone(13, 493.88);
  digitalWrite(analogPin0, LOW);
  digitalWrite(analogPin1, HIGH);
  delay(500);
  tone(13, 523.25);
  digitalWrite(analogPin2, HIGH);
  digitalWrite(analogPin1, LOW);
  delay(500);
  tone(13, 587.33);
   digitalWrite(analogPin2, LOW);
  digitalWrite(analogPin3, HIGH);
  delay(500);
  tone(13, 523.25);
  digitalWrite(analogPin2, HIGH);
  digitalWrite(analogPin3, LOW);
  delay(500);
  tone(13, 493.88);
  digitalWrite(analogPin2, LOW);
  digitalWrite(analogPin1, HIGH);
  delay(500);
  tone(13, 440);
   digitalWrite(analogPin0, HIGH);
  digitalWrite(analogPin1, LOW);
  delay(500);
  tone(13, 587.33);
   digitalWrite(analogPin0, HIGH);
  digitalWrite(analogPin1, HIGH);
  digitalWrite(analogPin2, HIGH);
  digitalWrite(analogPin3, HIGH);
  delay(1000);
   digitalWrite(analogPin0, LOW);
  digitalWrite(analogPin1, LOW);
  digitalWrite(analogPin2, LOW);
  digitalWrite(analogPin3, LOW);
  noTone(13);
  
}

void travisScott(int count){
  while(count > 0){
  double Db = 554.37;
  double E = 659.25;
  double Eb = 622.25;
  double B = 493.88;
  double Ab = 415.30;
  digitalWrite(analogPin0, HIGH);
  tone(13, Db);
  delay(212.76);
  digitalWrite(analogPin0, LOW);
  digitalWrite(analogPin1, HIGH);
  tone(13, E);
   delay(638.29);
   digitalWrite(analogPin1, LOW);
  digitalWrite(analogPin0, HIGH);
  tone(13, B);
   delay(212.76);
    digitalWrite(analogPin0, LOW);
  digitalWrite(analogPin2, HIGH);
  tone(13, Eb);
   delay(638.29);
   digitalWrite(analogPin2, LOW);
  digitalWrite(analogPin3, HIGH);
  tone(13, B);
    delay(212.76);
  digitalWrite(analogPin3, LOW);
  digitalWrite(analogPin0, HIGH);
  tone(13, Ab);
   delay(638.29);
   delay(638.29);
   noTone(13);
   delay(212.76);
   digitalWrite(analogPin0, LOW);
   count--;
  }
  
}

