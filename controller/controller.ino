#include <SoftwareSerial.h>

// CO2 SENSOR SETUP
SoftwareSerial sensor(12, 13);  // RX, TX pins on Ardunio
int co2 = 0;
int temp = 0;
int hum = 0;

void setup() {
  Serial.begin(9600);
  Serial.print("\n\n");
  Serial.println("AN128 Ardunio to Cozir CO2 Sensor Testing"); 
  sensor.begin(9600); // Start serial communications with sensor
  //sensor.println("K 0");  // Set Command mode
  sensor.println("M 4164"); // send Mode for Z and z outputs
  // "Z xxxxx z xxxxx" (CO2 filtered and unfiltered)
  sensor.println("K 2");  // set polling mode
}

void loop() {
  sensor.println("Q");
  set_values(sensor.readStringUntil("\r\n"));
  Serial.println("CO2: " + String(co2));
  Serial.println("Temp: " + String(temp));
  Serial.println("Hum: " + String(hum));
  Serial.println();
  delay(1000);
}

void set_values(String reading) {
  String co2_in = reading.substring(18, 24);
  co2 = co2_in.toInt();

  String temp_in = reading.substring(10, 16);
  temp = (temp_in.toInt() - 1000) / 10;

  String hum_in = reading.substring(2, 8);
  hum = hum_in.toInt() / 10;
}
