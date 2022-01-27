#include <SoftwareSerial.h>

// CO2 SENSOR SETUP
// RX, TX pins on Ardunio
SoftwareSerial cozir(12, 13);
SoftwareSerial sprintir(10, 11);

// RELAY BOARD SETUP
const int pump = 6;
const int valve = 7;

// GLOBALS
int cozir_co2;
int temp;
int hum;
int sprintir_co2;

void setup() {
    Serial.begin(9600);

    cozir.listen();
    cozir.begin(9600);  // Start serial comms with cozir sensor
    cozir.println("M 4164");  // set mode for co2, temp, and humidity outputs
    cozir.println("K 2");  // set polling mode

    sprintir.listen();
    sprintir.begin(9600);  // Start serial comms with sprintir sensor
    sprintir.println("M 4");  // set mode for filtered co2 output
    sprintir.println("K 2");  // set polling mode

    pinMode(pump, OUTPUT);
    pinMode(valve, OUTPUT);

    cozir_co2 = 0;
    temp = 0;
    hum = 0;
}

void loop() {
    refresh_cozir();
    refresh_sprintir();
    Serial.println("COZIR READING\nCO2: " + String(cozir_co2) +
                   "\nTemp: " + String(temp) + "\nHum: " + String(hum) + "\n");
    Serial.println("SPRINTIR READING\nCO2: " + String(sprintir_co2) + "\n");

    if (cozir_co2 >= 1900) {
        digitalWrite(valve, HIGH);
    } else {
        digitalWrite(valve, LOW);
    }

    delay(1000);
}

void refresh_cozir() {
    cozir.listen();
    
    cozir.println("Q");
    String reading = cozir.readStringUntil('\n');
    String co2_in = reading.substring(19, 24);
    cozir_co2 = co2_in.toInt();

    String temp_in = reading.substring(11, 16);
    temp = (temp_in.toInt() - 1000) / 10;

    String hum_in = reading.substring(3, 8);
    hum = hum_in.toInt() / 10;
}

    void refresh_sprintir() {
    sprintir.listen();
    
    sprintir.println(".");
    String reading = sprintir.readStringUntil('\n');
    int multiplier = reading.substring(3,8).toInt();
    
    sprintir.println("Z");
    reading = sprintir.readStringUntil('\n');
    sprintir_co2 = multiplier * reading.substring(3, 8).toInt();
}
