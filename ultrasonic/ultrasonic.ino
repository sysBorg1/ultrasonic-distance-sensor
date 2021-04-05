#include <WiFi.h>





// defines pins numbers
#define trigPin 4
#define echoPin 5
#define ledPin 2
#define relay 14

// defines variables
long duration;
int distance;


void setup() {

  Serial.begin(115200);
  Serial.println("\n... Starting ESP32 ...");
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)\tHeatIndex (C)\t(F)");


  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  WiFi.begin("EVO-Charji-7FD2", "JHTVzpg7");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }

  Serial.println("connected");
  pinMode(ledPin, OUTPUT);
  pinMode(relay, OUTPUT);
}

void loop() {
  delay(1000);
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;
  if (distance < 6) {
    digitalWrite(ledPin, LOW);
    delay(70);
    digitalWrite(relay, LOW);
  }
  if (distance > 40) {
    digitalWrite(ledPin, HIGH);
    delay(70);
    digitalWrite(relay, HIGH);
  }

  // Prints the distance on the Serial Monitor
  Serial.print("Distance cm: ");
  Serial.println(distance);
}
