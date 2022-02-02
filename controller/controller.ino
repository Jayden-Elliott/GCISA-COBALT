#include <SoftwareSerial.h>
#include "sensor.h"

// CO2 SENSOR SETUP
cozir cozir1(6, 7);
cozir cozir2(8, 9);
cozir cozir3(10, 11);
sprintir sprintir1(12, 13);

// RELAY BOARD PINS
const int pump = 3;
const int valve = 4;

void setup() {
    Serial.begin(9600);

    pinMode(pump, OUTPUT);
    pinMode(valve, OUTPUT);
}

void loop() {
    refresh_all();
    Serial.println("COZIR READING\nCO2: " + String(cozir3.get_co2()) +
                   "\nTemp: " + String(cozir3.get_temp()) +
                   "\nHum: " + String(cozir3.get_hum()) + "\n");
    Serial.println("SPRINTIR READING\nCO2: " + String(sprintir1.get_co2()) + "\n");

    if (cozir3.get_co2() >= 1900) {
        digitalWrite(valve, HIGH);
    } else {
        digitalWrite(valve, LOW);
    }

    delay(1000);
}

void refresh_all() {
    cozir1.refresh();
    cozir2.refresh();
    cozir3.refresh();
    sprintir1.refresh();
}
