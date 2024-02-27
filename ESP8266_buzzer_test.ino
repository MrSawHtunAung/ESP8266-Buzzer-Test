/*
This code is to test buzzer sound.
Attach the buzzer at Pin D8.
You can enter frequency and timing continuelsy spreated by comma. 
Here is example format. " 2217,70 ,2349,47, 1480,100, 1661,23, 1760,23,1190,93,740,93,923,230 "
*/

#include <ESP8266WiFi.h>

const int buzzerPin = D8; // Buzzer pin

void setup() {
  Serial.begin(115200);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n'); // Read input until newline character
    generateTones(input);
  }
}

void generateTones(String input) {
  int frequencies[100]; // Array to store frequencies
  int timings[100]; // Array to store timings
  int count = 0; // Counter for frequencies and timings

  // Parse input string
  int pos = 0;
  while ((pos = input.indexOf(',')) != -1) {
    frequencies[count] = input.substring(0, pos).toInt(); // Extract frequency
    input = input.substring(pos + 1); // Remove extracted frequency from input string
    pos = input.indexOf(','); // Find position of next comma
    timings[count] = input.substring(0, pos).toInt(); // Extract timing
    input = input.substring(pos + 1); // Remove extracted timing from input string
    count++;
  }

  // Add the last frequency and timing
  frequencies[count] = input.toInt();
  timings[count] = Serial.parseInt();

  // Generate tones
  for (int i = 0; i <= count; i++) {
    tone(buzzerPin, frequencies[i]); // Generate tone
    delay(timings[i]); // Wait for the specified duration
    noTone(buzzerPin); // Stop the tone
    delay(50); // Add a small delay between tones
  }
}
