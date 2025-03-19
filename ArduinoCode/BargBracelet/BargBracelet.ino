#include "EspFactory.h"

unsigned long previousTime = 0;
const unsigned long responseTimeout =  30000;  // 30 seconds to wait for button press
const unsigned long ledFlashDuration = 20000; // 20 seconds LED flashing after press
const unsigned long ledFlashInterval = 500;  // LED toggle every 500ms

using namespace FuturIsTech;

EspFactory *Factory = new EspFactory();
Shared *SharedInfos = new Shared();

auto Esp8266Server = Factory->getEspServer();

const int buttonPin = 12;  // GPIO12 (D6)
const int ledPin = 4;     // GPIO4 (D2)
const int motorPin = 2;   // GPIO2 (D4)

bool callActive = false;
bool waitingForResponse = false;
bool ledFlashing = false;
unsigned long callStartTime = 0;
unsigned long ledFlashStartTime = 0;
unsigned long lastLedToggleTime = 0;
bool ledState = false;

void router(Target from, Target to, String msg) {
  Serial.printf("Received message from(%s), to(%s) : %s\n", SharedInfos->targetToString(from), SharedInfos->targetToString(to), msg.c_str());

  if (to == Target::EspServer) {
    handleTheServerMessage(from, to, msg);
  } else {
    Esp8266Server->sendMessage(from, to, msg);
  }
}

void handleTheServerMessage(Target from, Target to, String msg) {
  if (msg == "CALL" || msg == "VIBRATE") {
    activateBracelet();
  }
}

void activateBracelet() {
  digitalWrite(motorPin, HIGH);  // Start vibration
  callActive = true;
  waitingForResponse = true;
  callStartTime = millis();
  
  // Start LED flashing immediately
  ledFlashing = true;
  lastLedToggleTime = millis();
  ledFlashStartTime = millis();

  Serial.println("Vibration and LED flashing activated.");
}

void deactivateMotor() {
  digitalWrite(motorPin, LOW);  // Stop vibration
  Serial.println("Vibration stopped.");
}

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(motorPin, OUTPUT);

  digitalWrite(ledPin, LOW);
  digitalWrite(motorPin, LOW);
  // name: New net
  //pswrd: 1234567890
  Esp8266Server->setup(SharedInfos->getSsid(), SharedInfos->getPwd(), 115200);
  Esp8266Server->create(80);
  Esp8266Server->onMessage(router);

  randomSeed(analogRead(0));
}

void loop() {
  Esp8266Server->start();

  unsigned long currentTime = millis();

  // LED flashing logic (flashes while waiting for button press)
  if (ledFlashing) {
    if (currentTime - lastLedToggleTime >= ledFlashInterval) {
      ledState = !ledState;
      digitalWrite(ledPin, ledState);
      lastLedToggleTime = currentTime;
    }
  }

  // If a call is active
  if (callActive) {
    if (digitalRead(buttonPin) == LOW) {  // Button pressed
      deactivateMotor();
      callActive = false;
      waitingForResponse = false;
      //ledFlashing = true;
      //ledFlashStartTime = millis();
      Serial.println("Button pressed. Sending response...");
      Esp8266Server->sendMessage(Target::EspServer, Target::AndroidApp, "bracelet button clicked");
      delay(500);
    }

    if (waitingForResponse && (currentTime - callStartTime > responseTimeout)) {
      Serial.println("No response. Sending timeout notification...");
      deactivateMotor();
      Esp8266Server->sendMessage(Target::EspServer, Target::AndroidApp, "No response from bracelet");
      waitingForResponse = false;
      ledFlashing = false;
      digitalWrite(ledPin, LOW); // Stop LED if timeout occurs
    }
  }

  // Stop LED flashing after 5 seconds if button was pressed
  if (ledFlashing && (currentTime - ledFlashStartTime >= ledFlashDuration)) {
    ledFlashing = false;
    digitalWrite(ledPin, LOW);
    Serial.println("LED flashing stopped.");
  }
}
