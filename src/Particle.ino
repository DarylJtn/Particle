/*
Basic example of sending a SMS with Twilio and a Particle Electron.

Author: Paul Kamp, Twilio Developer Education
License: MIT
*/

int inPin = D4;
int ledPin = D7;
int val = 0;
String body = "Hey, this is your Particle Electron!";

void setup() {
  Serial.begin(115200);
  pinMode(inPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
    val = digitalRead(inPin);
    if(val){
    Serial.println("That's all!  You can restart or edit the code now.");
    digitalWrite(ledPin, HIGH);
    Particle.publish("twilio_sms", body, PRIVATE);

    delay(60000);
  }
      digitalWrite(ledPin, LOW);
}
