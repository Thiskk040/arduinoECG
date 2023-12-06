#include <Arduino.h>

unsigned long lastBeatTime = 0;
int beatCount = 0;
bool lastBeat = false;
int BPM = 0;
void setup() {
  Serial.begin(9600);
  pinMode(10, INPUT); // Setup for leads off detection LO +
  pinMode(11, INPUT); // Setup for leads off detection LO -
}

void loop() {
  if ((digitalRead(10) == 1) || (digitalRead(11) == 1)) {
    Serial.println('!');
  } else {
    int sensorValue = analogRead(A1);
    
    // Check for a beat (high signal)
    if (sensorValue > 512) {
      if (!lastBeat) {
        lastBeat = true;
        int timeSinceLastBeat = millis() - lastBeatTime;
        
        if (beatCount == 0) {
          lastBeatTime = millis();
        } else {
          int beatsPerMinute = 60000 / timeSinceLastBeat;
          BPM = (BPM + beatsPerMinute) / 2;
        }
        beatCount++;
      }
    } else {
      lastBeat = false;
    }
    Serial.print(sensorValue);
  }
  
  // Print BPM every 1000 ms (1 second)
  if (millis() - lastBeatTime >= 1000) {
    //Serial.print("BPM: ");
    //Serial.println(BPM);
    //BPM = 0;
    beatCount = 0;
  }
  Serial.print(',');
  Serial.print(BPM);
  Serial.println();
  
  // Wait for a bit to keep serial data from saturating
  delay(0);
}

