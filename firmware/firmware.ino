  // Include libraries
#include "TCS3200.h"
#include "DCMDriverL298.h"
#include "CH926.h"
#include "TM1637Display.h"
#include <EEPROM.h>

  // define pins for all modules
#define TCS3200_PIN_S0  13
#define TCS3200_PIN_S1  A3
#define TCS3200_PIN_S2  A4
#define TCS3200_PIN_S3  A1
#define TCS3200_PIN_OUT 12
#define CDMOTORDRIVERL298_PIN_ENA 5 // analog input - speed
#define CDMOTORDRIVERL298_PIN_ENB 6 // analog input - speed
#define CDMOTORDRIVERL298_PIN_IN1 4
#define CDMOTORDRIVERL298_PIN_IN2 7
#define CDMOTORDRIVERL298_PIN_IN3 8
#define CDMOTORDRIVERL298_PIN_IN4 9
#define COINACCEPTOR_PIN_SIG  2 // pin to use interrupt speed
#define TM1637DISPLAY_PIN_CLK 3
#define TM1637DISPLAY_PIN_DIO A0
#define PUSHBUTTON_PIN A2 // simulation button

  //global variables init
int *rgb;
int impulsCount, count, stripeCount, solidCount, gamesPlayed;
float total = 0.0;
float price = 0.0;
int pulse = 0; // simulation pulse

  //object init
TCS3200 colorSensor(TCS3200_PIN_S0, TCS3200_PIN_S1, TCS3200_PIN_S2, TCS3200_PIN_S3, TCS3200_PIN_OUT); 
DCMDriverL298 motorDriver(CDMOTORDRIVERL298_PIN_ENA, CDMOTORDRIVERL298_PIN_ENB, CDMOTORDRIVERL298_PIN_IN1, CDMOTORDRIVERL298_PIN_IN2, CDMOTORDRIVERL298_PIN_IN3, CDMOTORDRIVERL298_PIN_IN4);
CH926 coinAcceptor(COINACCEPTOR_PIN_SIG, impulsCount, price);
TM1637Display display(TM1637DISPLAY_PIN_CLK, TM1637DISPLAY_PIN_DIO);

void impulses()
{
  impulsCount++;
  count = 0;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  display.setBrightness(0x0f);
    // attach interrupt on pin, taking impulses
  attachInterrupt(digitalPinToInterrupt(COINACCEPTOR_PIN_SIG), impulses, FALLING);
  EEPROM.read(0);
  display.clear();
  //get a pseudo-random number every time we start the program
  randomSeed(analogRead(0));
  // pulse simulation with button
  pinMode(PUSHBUTTON_PIN, INPUT_PULLUP);
}

int lastState = HIGH;
void loop() {
    count++;
    delay(300);
  // -------------------------------------------------------------------------- //
  //                         FOR TESTING PURPOSES
  // this function uses the pushbutton release signal to simulate pulses sent from
  // the coin acceptor. every time its pressed it will input a pulse and depending
  // on the amount it will input a different price.

  int value = digitalRead((PUSHBUTTON_PIN));

  Serial.print("Count: ");
  Serial.print(count);
  Serial.print(". pulses: ");
  Serial.println(pulse);
  if (lastState != value) {
    lastState = value;

    if (value == LOW) {
      pulse++;
    } 
    if (count > 20 && pulse == 1) {
        price = price + 2.0;
        count = 0;
        pulse = 0;
        Serial.print("Money given: ");
        Serial.println(price);
    }
    if (count > 20 && pulse == 2) {
        price = price + 1.0;
        count = 0;
        pulse = 0;
        Serial.print("Money given: ");
        Serial.println(price);
    }
    if (count > 20 && pulse == 3) {
        price = price + 0.5;
        count = 0;
        pulse = 0;
        Serial.print("Money given: ");
        Serial.println(price);
    }
    if (count > 20 && pulse == 4) {
        price = price + 0.2;
        count = 0;
        pulse = 0;
        Serial.print("Money given: ");
        Serial.println(price);
    }
    if (count > 20 && pulse == 5) {
        price = price + 0.1;
        count = 0;
        pulse = 0;
        Serial.print("Money given: ");
        Serial.println(price);
    }
  }
  // -------------------------------------------------------------------------- //
  //price = coinAcceptor.coinCounter(count);
  if(price<1)
  {
      // arguments in order: number to be shown, display a dot, true=if you want leading 0, number of digits to be modified, the position from which to print.
    display.showNumberDecEx(price*10, 0b10000000, true, 2, 2);
  }
  else
  {
    display.showNumberDecEx(price*10, 0b00100000, false, 4, 0);
  }
  if(price>=5)
  {
    solidCount = stripeCount = 7;
    Serial.println("Game is starting!");
    coinAcceptor.resetPrice();
          // open hatch for all balls
    Serial.println("Opening hatch A to release all balls...");
    motorDriver.enMotorA(200, 1); //speed value 0-255, direction either 1 or 0
    delay(100); // open hatch for half a turn (depending on speed, different time)
    motorDriver.stopMotorA();
    delay(1000); // wait 10 sec for all balls to come out
    motorDriver.enMotorA(200, 0);
    delay(100); //close hatch back to original position
    motorDriver.stopMotorA();
    Serial.println("Closing hatch A");


        //get rgb values
      rgb = colorSensor.getRGB();
      // -------------------------------------------------------------------------- //
      //                         FOR TESTING PURPOSES
      // this function initialises the array balls with 16 numbers then shuffles them
      // after that the program is run in a for loop to have a simulation of a pseudo
      // random game. for the actual implementation this is not needed.
      int balls[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
      const int ballCount = sizeof balls / sizeof balls[0];
      for (int i=0; i < ballCount; i++) {
        int n = random(0, ballCount);  // Integer from 0 to ballCount-1
        int temp = balls[n];
        balls[n] =  balls[i];
        balls[i] = temp;
      }
      for (int i=0; i< ballCount; i++)
      {
        if(balls[i] == 0) {
          rgb[0] = 220;
          rgb[1] = 220;
          rgb[2] = 220;
        } else if(balls[i] == 1) {
            rgb[0] = 245;
            rgb[1] = 245;
            rgb[2] = 20;
        } else if(balls[i] == 2) {
            rgb[0] = 20;
            rgb[1] = 20;
            rgb[2] = 245;
        } else if(balls[i] == 3) {
            rgb[0] = 245;
            rgb[1] = 20;
            rgb[2] = 20;
        } else if(balls[i] == 4) {
            rgb[0] = 110;
            rgb[1] = 20;
            rgb[2] = 245;
        } else if(balls[i] == 5) {
            rgb[0] = 245;
            rgb[1] = 110;
            rgb[2] = 20;
        } else if(balls[i] == 6) {
            rgb[0] = 20;
            rgb[1] = 245;
            rgb[2] = 20;
        } else if(balls[i] == 7) {
            rgb[0] = 110;
            rgb[1] = 20;
            rgb[2] = 20;
        } else if(balls[i] == 8) {
            rgb[0] = 5;
            rgb[1] = 5;
            rgb[2] = 5;
        } else if(balls[i] == 9) {
            rgb[0] = 205;
            rgb[1] = 205;
            rgb[2] = 20;
        } else if(balls[i] == 10) {
            rgb[0] = 20;
            rgb[1] = 20;
            rgb[2] = 205;
        } else if(balls[i] == 11) {
            rgb[0] = 205;
            rgb[1] = 20;
            rgb[2] = 20;
        } else if(balls[i] == 12) {
            rgb[0] = 90;
            rgb[1] = 20;
            rgb[2] = 205;
        } else if(balls[i] == 13) {
            rgb[0] = 205;
            rgb[1] = 90;
            rgb[2] = 20;
        } else if(balls[i] == 14) {
            rgb[0] = 20;
            rgb[1] = 205;
            rgb[2] = 20;
        } else{
            rgb[0] = 80;
            rgb[1] = 20;
            rgb[2] = 20;
        }
      
      // ------------------------------------------------------------------------ //
      //!! IMPORTANT: if needs to be while if no testing function! IMPORTANT !!
      if(rgb[0] <= 10 && rgb[1] <= 10  && rgb[2] <= 10) 
      {
        break;
      }
          // if white ball is detected
        if(rgb[0] >= 220 && rgb[1] >= 220  && rgb[2] >= 220)
        {
          Serial.println("white ball detected, opening hatch B");
          motorDriver.enMotorB(200, 1);
          delay(100);
          motorDriver.stopMotorB();
          // wait 1 sec for ball to pass
          delay(1000);
          motorDriver.enMotorB(200, 0);
          delay(100);
          motorDriver.stopMotorB();
          Serial.println("closing hatch B");
        }

        // solid ball identification
        if(rgb[0] == 245 && rgb[1] == 245  && rgb[2] == 20)
        { solidCount--;
          Serial.print("Yellow solid ball detected. Remaining solids: ");
          Serial.println(solidCount);
          delay(500);
        }
        if(rgb[0] == 20 && rgb[1] == 20  && rgb[2] == 245)
        { solidCount--;
          Serial.print("Blue solid ball detected. Remaining solids: ");
          Serial.println(solidCount);
          delay(500);
        }
        if(rgb[0] == 245 && rgb[1] == 20  && rgb[2] == 20)
        { solidCount--;
          Serial.print("Red solid ball detected. Remaining solids: ");
          Serial.println(solidCount);
          delay(500);
        }
        if(rgb[0] == 110 && rgb[1] == 20  && rgb[2] == 245)
        { solidCount--;
          Serial.print("Purple solid ball detected. Remaining solids: ");
          Serial.println(solidCount);
          delay(500);
        }
        if(rgb[0] == 245 && rgb[1] == 110  && rgb[2] == 20)
        { solidCount--;
          Serial.print("Orange solid ball detected. Remaining solids: ");
          Serial.println(solidCount);
          delay(500);
        }
        if(rgb[0] == 20 && rgb[1] == 245  && rgb[2] == 20)
        { solidCount--;
          Serial.print("Green solid ball detected. Remaining solids: ");
          Serial.println(solidCount);
          delay(500);
        }
        if(rgb[0] == 110 && rgb[1] == 20  && rgb[2] == 20)
        { solidCount--;
          Serial.print("Dark red solid ball detected. Remaining solids: ");
          Serial.println(solidCount);
          delay(500);
        }

        // Striped ball identification
        if(rgb[0] == 205 && rgb[1] == 205  && rgb[2] == 20)
        { stripeCount--;
          Serial.print("Yellow striped ball detected. Remaining stripes: ");
          Serial.println(stripeCount);
          delay(500);
        }
        if(rgb[0] == 20 && rgb[1] == 20  && rgb[2] == 205)
        { stripeCount--;
          Serial.print("Blue striped ball detected. Remaining stripes: ");
          Serial.println(stripeCount);
          delay(500);
        }
        if(rgb[0] == 205 && rgb[1] == 20  && rgb[2] == 20)
        { stripeCount--;
          Serial.print("Red striped ball detected. Remaining stripes: ");
          Serial.println(stripeCount);
          delay(500);
        }
        if(rgb[0] == 90 && rgb[1] == 20  && rgb[2] == 205)
        { stripeCount--;
          Serial.print("Purple striped ball detected. Remaining stripes: ");
          Serial.println(stripeCount);
          delay(500);
        }
        if(rgb[0] == 205 && rgb[1] == 90  && rgb[2] == 20)
        { stripeCount--;
          Serial.print("Orange striped ball detected. Remaining stripes: ");
          Serial.println(stripeCount);
          delay(500);
        }
        if(rgb[0] == 20 && rgb[1] == 205  && rgb[2] == 20)
        { stripeCount--;
          Serial.print("Green striped ball detected. Remaining stripes: ");
          Serial.println(stripeCount);
          delay(500);
        }
        if(rgb[0] == 80 && rgb[1] == 20  && rgb[2] == 20)
        { stripeCount--;
          Serial.print("Dark red striped ball detected. Remaining stripes: ");
          Serial.println(stripeCount);
          delay(500);
        }
      delay(500);
      }      
      Serial.println("Black ball has been detected. Game Ended!");
      Serial.println("-----------------------------------------");
      if(stripeCount == 0) {
        Serial.println("The winner is the person with the striped balls!");
      } else if(solidCount == 0) {
        Serial.println("The winner is the person with the solid balls!");
      } else {
        Serial.println("Noone won :/");
      }
      gamesPlayed++;
      //add game price to total and reset price 
      total = total + price;
      EEPROM.write(0, total);
      price = 0;
      Serial.print("Total amount in machine: ");
      Serial.print(total);
      Serial.print(".Total games played: ");
      Serial.println(gamesPlayed);
  }
}