#include <SoftwareSerial.h>

#include "sensor.h"

//hello

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
    print_sensors();

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

void print_sensors() {
    Serial.println("COZIR 1 READING");
    cozir1.print_measurements();
    Serial.println();
    Serial.println("COZIR 2 READING");
    cozir2.print_measurements();
    Serial.println();
    Serial.println("COZIR 3 READING");
    cozir3.print_measurements();
    Serial.println();
    Serial.println("SPRINTIR 1 READING");
    sprintir1.print_measurements();
    Serial.println();
}
