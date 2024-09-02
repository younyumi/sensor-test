#include <Arduino.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

// Define which pins you will use on the Arduino to communicate with your GPS
#define RXPIN 6
#define TXPIN 5

// Set this value equal to the baud rate of your GPS
#define GPSBAUD 9600

// Create an instance of the TinyGPSPlus object
TinyGPSPlus gps;

// Initialize the SoftwareSerial library to the pins you defined above
SoftwareSerial uart_gps(RXPIN, TXPIN);

// Function prototypes
void displayInfo();

// Setup function
void setup() {
  // Initialize serial communication with the terminal
  Serial.begin(9600);
  // Initialize serial communication with the GPS module
  uart_gps.begin(GPSBAUD);

  // Print initial messages
  Serial.println();
  Serial.println("GPS Shield QuickStart Example Sketch");
  Serial.println("       ...waiting for lock...           ");
  Serial.println();
}

// Main loop function
void loop() {
  // While there is data available on the RX pin...
  while (uart_gps.available()) {
    // Read the data into a variable
    char c = uart_gps.read();
    
    // If there is a new valid sentence...
    if (gps.encode(c)) {
      // Display the GPS information
      displayInfo();
    }
  }
}

// Function to display GPS information
void displayInfo() {
  if (gps.location.isValid()) {
    Serial.print("Lat/Long: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(", ");
    Serial.println(gps.location.lng(), 6);
  } else {
    Serial.println("Location: INVALID");
  }

  if (gps.date.isValid()) {
    Serial.print("Date: ");
    Serial.print(gps.date.month());
    Serial.print("/");
    Serial.print(gps.date.day());
    Serial.print("/");
    Serial.println(gps.date.year());
  } else {
    Serial.println("Date: INVALID");
  }

  if (gps.time.isValid()) {
    Serial.print("Time: ");
    Serial.print(gps.time.hour());
    Serial.print(":");
    Serial.print(gps.time.minute());
    Serial.print(":");
    Serial.print(gps.time.second());
    Serial.print(".");
    Serial.println(gps.time.centisecond());
  } else {
    Serial.println("Time: INVALID");
  }

  if (gps.altitude.isValid()) {
    Serial.print("Altitude (meters): ");
    Serial.println(gps.altitude.meters());
  } else {
    Serial.println("Altitude: INVALID");
  }

  if (gps.course.isValid()) {
    Serial.print("Course (degrees): ");
    Serial.println(gps.course.deg());
  } else {
    Serial.println("Course: INVALID");
  }

  if (gps.speed.isValid()) {
    Serial.print("Speed (kmph): ");
    Serial.println(gps.speed.kmph());
  } else {
    Serial.println("Speed: INVALID");
  }

  Serial.println();
  delay(1000);  // Adjust delay as needed
}
