// This #include statement was automatically added by the Spark IDE.#include "Adafruit_SSD1306/Adafruit_SSD1306.h"

//SYSTEM_MODE(SEMI_AUTOMATIC);
/* ============== MAIN =====================*/


/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 by Daniel Eichhorn
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

// Include the display library
#include <SH1106.h>
#include <CellularHelper.h>
#include "Particle.h"

STARTUP(cellular_credentials_set("TM", "", "", NULL));
// Initialize the OLED display
SYSTEM_MODE(SEMI_AUTOMATIC);
SH1106 display(0x3c);
//SYSTEM_MODE(MANUAL)
//SYSTEM_THREAD(ENABLED)

#define DEMO_DURATION 3000
typedef void (*Demo)(void);
FuelGauge fuel;
int demoMode = 0;
int counter = 1;
int previousBattLevel = 0;
int inPin = D4;
int ledPin = D7;
int alarmTriggered = 0;
 String body = "Hey, this is your Particle Electron!";
 CellularSignal sig;
 bool alarmSent = false;
 bool callFailed = false;
void callStatus(int status);

void callStatus(int Status){



}
void connectingDisplay(){

  // draw the current demo method
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, "Connecting...");
    display.display();
    //SYSTEM_MODE(AUTOMATIC);
}
void displayString(String msg){
  display.clear();
  // draw the current demo method
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, msg);
    display.display();
}
void displayLine2(String msg){
  // draw the current demo method
        display.setColor(BLACK);
        display.fillRect(0, 16, 128, 24);
        display.display();

        display.setColor(WHITE);
          display.display();
        display.drawString(0, 16, msg);
          display.display();

}

void displayBattery(){
  if ((int)fuel.getSoC() != previousBattLevel){
        display.setColor(BLACK);
    display.fillRect(50, 0,  78, 30);
    display.display();
    display.setColor(WHITE);
  previousBattLevel = (int)fuel.getSoC();
  String message = "Batt: "+(String)(int)fuel.getSoC()+"%  ";
  display.drawString(57, 0, message);
    display.display();
  }
}

void setup() {

  //Serial.begin(115200);
  Serial.println();
  Serial.println();
  // Initialising the UI will init the display too.
  display.init();
//Particle.function("callStatus", callStatus);
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  pinMode(inPin, INPUT);
  pinMode(ledPin, OUTPUT);
  CellularSignal sig = Cellular.RSSI();
Particle.keepAlive(6 * 60);

}

void displaySignal(){
CellularHelperLocationResponse locResp = CellularHelper.getLocation();
    CellularSignal sig = Cellular.RSSI();
    display.setColor(BLACK);
    display.fillRect(0, 35, 128, 24);
    display.display();
    display.setColor(WHITE);
    CellularHelperRSSIQualResponse rssiQual = CellularHelper.getRSSIQual();
    display.drawString(0, 40, (String)rssiQual.rssi);
      display.display();


  }



void loop() {
  // clear the display

displayBattery();
displaySignal();
alarmTriggered = digitalRead(inPin);
    Serial.println(Particle.connected());
 if(alarmTriggered){
 digitalWrite(ledPin, HIGH);
 Particle.connect();
 if (Particle.connected() == 1){
     displayLine2("Connected!");
     if(!alarmSent|| callFailed){
     Particle.publish("twilio_sms", body, PRIVATE);
     alarmSent = true;
   }
 }else{
    displayLine2("Connecting...");
 }
Serial.println("That's all!  You can restart or edit the code now.");
}else{
   digitalWrite(ledPin, LOW);
  Particle.disconnect();
  Cellular.off();
  displayLine2("Ready!");
}
}
