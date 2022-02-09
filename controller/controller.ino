#include <SoftwareSerial.h>

#include "sensor.h"

// CO2 SENSOR SETUP
cozir cozir1(6, 7);
cozir cozir2(8, 9);
cozir cozir3(10, 11);
sprintir sprintir1(12, 13);
pressure pressure1(A0);
pressure pressure2(A1);

// RELAY BOARD PINS
const int pump = 3;
const int valve = 4;

void setup() {
    Serial.begin(9600);

    pinMode(pump, OUTPUT);
    pinMode(valve, OUTPUT);
    // Serial.println("index,cozir1_co2,cozir1_temp,cozir1_hum,cozir2_co2,cozir2_temp,cozir2_hum, cozir3_co2,cozir3_temp,cozir3_hum, sprintir_co2");
}

int index;
void loop() {
    refresh_all();
    print_sensors();
    // print_csv(index);

    if (cozir3.get_co2() >= 1900) {
        digitalWrite(valve, HIGH);
    } else {
        digitalWrite(valve, LOW);
    }

    delay(1000);
    ++index;
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
    Serial.println("PRESSURE 1 READING");
    pressure1.print_measurements();
    Serial.println();
    Serial.println("PRESSURE 2 READING");
    pressure2.print_measurements();
    Serial.println();
}

void print_csv(int index) {
    Serial.println(String(index) + ',' + cozir1.get_csv() + ',' + cozir2.get_csv() + ',' + cozir3.get_csv() + ',' + sprintir1.get_csv());
}
