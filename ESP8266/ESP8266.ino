/**********************************************************************************
  @file             Code for controlling Switch with Blynk Sync Button
  @author           Chung Dinh
  @version          V1.0.0
  ©Copyright 2018   D.V.C
*********************************************************************************/
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "*****";//enter auth

char ssid[] = "*****";//enter wifi name
char pass[] = "*****";//enter wifi password

const int ledPin = 16;
const int btnPin = 0;

BlynkTimer timer;
void checkPhysicalButton();

int ledState = LOW;
int btnState = HIGH;

BLYNK_CONNECTED() {
  Blynk.syncVirtual(V2);

  // Alternatively, you could override server state using:
//  Blynk.virtualWrite(V2, ledState);
}

// When App button is pushed - switch the state
BLYNK_WRITE(V2) {
  ledState = param.asInt();
  digitalWrite(ledPin, ledState);
}

void checkPhysicalButton()
{
  if (digitalRead(btnPin) == LOW) {
    // btnState is used to avoid sequential toggles
    if (btnState != LOW) {

      // Toggle LED state
      ledState = !ledState;
      digitalWrite(ledPin, ledState);

      // Update Button Widget
      Blynk.virtualWrite(V2, ledState);
    }
    btnState = LOW;
  } else {
    btnState = HIGH;
  }
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT);
  digitalWrite(ledPin, ledState);

  // Setup a function to be called every 100 ms
  timer.setInterval(100L, checkPhysicalButton);
}

void loop()
{
  Blynk.run();
  timer.run();
}

