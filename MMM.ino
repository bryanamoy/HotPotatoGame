//i2c Master Code(UNO)
#include <Wire.h>

// the number of the pushbutton pins
const int buttonPin = 2;    
const int buttonPin2 = 3;
const int buttonPin3 = 4;
const int buttonPin4 = 5;
const int buttonPin5 = 6;
const int buttonPin6 = 7;
const int startButton = 8;

// the number of the LED pin
const int ledPin =  13; 

// the timer LED pin
const int timerT =  11;

// state of the timer LED (on/off)
int ledState = LOW;

// current state of the buttons (pressed/unpressed)
int buttonState = 0; 
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;
int buttonState5 = 0;
int buttonState6 = 0;
int startButtonState = 0;


//Keeps track of who's turn it is
bool playerone = 0;
bool playertwo = 0;
bool playerthree = 0;

// first player of the game 
int firstplayer;

// game time
int gameTime = 0;

// state of the game (in progress/ended)
boolean gameState = false;

// determines whether the game has ended or not
boolean endGame = false;

// determines if the ending message has been printed
boolean printMsg = false;

// previous time (for blinking an LED) 
unsigned long previousMillis = 0; 

 // regular blinking time per second
const long interval = 1000; 

// faster blinking time 
const long faster = 300;

void setup()
{
  Wire.begin();
  Serial.begin(9600);

  // initalize LEDS as outputs:
  pinMode(ledPin, OUTPUT);
  pinMode(timerT, OUTPUT);
  
  // initialize the pushbuttons as inputs:
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  pinMode(buttonPin5, INPUT_PULLUP);
  pinMode(buttonPin6, INPUT_PULLUP);
  pinMode(startButton, INPUT_PULLUP);

  // method to help "randomly" pick a first player
  randomSeed(analogRead(0)); 
}

// sets up the beginning of the game 
void game() {
  // allows printing to the Serial
  while(!Serial);

  // determines a random amount of time (btwn 20-30 seconds) for the round
  gameTime =  random(20,30) * 1000;

  // if start button was pressed, randomly select the first player 
  if (startButtonState == 1) {
    firstplayer = random(1,4);

    // turn on the selected first player's LED:
    if(firstplayer == 1) {
      Wire.beginTransmission(5);
      playerone = 1;
      buttonState3 = HIGH;
      buttonState = LOW;
      buttonState2 = LOW;
      Wire.endTransmission();
    }
    
    if(firstplayer == 2) {
      Wire.beginTransmission(5);
      playertwo = 1;
      buttonState = HIGH;
      buttonState3 = LOW;
      buttonState2 = LOW;
      Wire.endTransmission();
    }
    
    if(firstplayer == 3) {
      Wire.beginTransmission(5);
      playerthree = 1;
      buttonState2 = HIGH;
      buttonState = LOW;
      buttonState3 = LOW;
      Wire.endTransmission();
    }
  }

  // print out the starting player info on Serial
  Serial.print("Starting Player: ");
  Serial.print(firstplayer);
  Serial.println();
}

void loop()
{
    // current time in milliseconds
    unsigned long currentMillis = millis();

  // ------------------------------------------//
    // read the state of the pushbutton value:
    buttonState = digitalRead(buttonPin);
    buttonState2 = digitalRead(buttonPin2);
    buttonState3 = digitalRead(buttonPin3);
    buttonState4 = digitalRead(buttonPin4);
    buttonState5 = digitalRead(buttonPin5);
    buttonState6 = digitalRead(buttonPin6);
    startButtonState = digitalRead(startButton);
  // ------------------------------------------//

  // start the game once start button has been pushed
  if(gameState == false && startButtonState == 1) {
    game();
    gameState = true;
  }

  // restart game if start button has been pushed again at the end of a previous game
  if(gameTime <= 0 && startButtonState == 1) {
      reset();
      game();
      endGame = false;
      printMsg = false;
      gameState = true;
    }

  // if game has ended, determine & display the loser of the round
  if(gameTime == 0 && gameState == true) {
    int loser = 0;
    
    if(playerone == 1) {
      loser = 1;
    } else if(playertwo == 1) {
      loser = 2;
    } else if(playerthree == 1) {
      loser = 3;
    }

    // print out ending game message & loser
    if(printMsg == false) {
      Serial.println ("PLAYERS! TIME'S UP!");
      Serial.print ("PLAYER ");
      Serial.print(loser);
      Serial.println(" , YOU LOSE!");
    }

    // leave timer LED on for 3 seconds before turning off 
    delay(3000);
    digitalWrite(timerT, LOW);

    // message has been printed & game has ended
    printMsg = true;
    endGame = true;
  }

  // keep timer LED (blue) on while game is in progress & above 6 seconds
  if(gameTime !=0 && gameTime >= 6000) {
    // check if it is time to blink the LED again
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;   //save the last time you blinked the LED
      gameTime -= 1000;                 // decrement the game time by 1 second  
      ledState = HIGH;                  // leave LED on 
      digitalWrite(timerT, ledState);   
      
    }
 
  }

  // blink fast to signal end of game is near (under 6 seconds)
 if(gameTime !=0 && gameTime <= 6000) {
  if (currentMillis - previousMillis >= faster) {
      //save the last time you blinked the LED
      previousMillis = currentMillis;
      gameTime -= 1000;
      Serial.println(gameTime/1000);

      // blink the LED
      if(ledState == HIGH) {
        ledState = LOW;
      } else {
        ledState = HIGH;
      }

      digitalWrite(timerT, ledState);
  }
 }

    
 // Buttons Presses
 if(endGame != true) {
    
    if(playerone == 1 || startButtonState == HIGH){
      // First Player, Right (Second LED)
      if (buttonState == HIGH) {
        Wire.beginTransmission(5);
        Wire.write('M');
        Wire.write('B');
        Wire.endTransmission();
        playertwo = 1;
        playerone = 0;
      }    
      // First Player, Left (Third LED)
      else if (buttonState4 == HIGH) {
        Wire.beginTransmission(5);
        Wire.write('K');
        Wire.write('B');
        Wire.endTransmission();   
        playerthree = 1;
        playerone = 0;     
      }
    }

    
    if(playertwo == 1 ||startButtonState == HIGH){
      // Second Player, Right (Third LED)
      if (buttonState2 == HIGH) {
        Wire.beginTransmission(5);
        Wire.write('E');
        Wire.write('D');
        Wire.endTransmission();
        playerthree = 1;
        playertwo = 0;
      }    
      // Second Player, Left (First LED)
      else if(buttonState5 == HIGH) {
        Wire.beginTransmission(5);
        Wire.write('G');
        Wire.write('D');
        Wire.endTransmission();
        playerone = 1;
        playertwo = 0;
      }
    }

    if(playerthree == 1 ||startButtonState == HIGH){
      // Third Player, Right (First LED)
      if (buttonState3 == HIGH) {
        Wire.beginTransmission(5);
        Wire.write('A');
        Wire.write('F');
        Wire.endTransmission();
        playerone = 1;
        playerthree = 0;
      }
      // Third Player, Left (Second LED)
      else if (buttonState6 == HIGH) {
        Wire.beginTransmission(5);
        Wire.write('J');
        Wire.write('F');
        Wire.endTransmission();
        playertwo = 1;
        playerthree = 0;
      }
      
    }
      delay(20);
    
 } 
} 

// resets everything back to 0 
void reset(){
      playerone = 0;
      playertwo = 0;
      playerthree = 0;
      buttonState = LOW;
      buttonState2 = LOW;     
      buttonState3 = LOW;
      buttonState4 = LOW;      
      buttonState5 = LOW;
      buttonState6 = LOW;
}
