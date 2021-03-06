#include <SoftwareSerial.h>

class cozir {
   public:
    // REQUIRES: type is "COZIR" or "SPRINTIR"
    cozir(int rx, int tx) : sensor(rx, tx), co2(0), temp(0), hum(0) {
        sensor.listen();
        sensor.begin(9600);  // Start serial comms with cozir3 sensor
        sensor.println("M 4164");  // set mode for co2, temp, and humidity outputs
        sensor.println("K 2");  // set polling mode
    }

    // return co2 in ppm
    int get_co2() const {
        return co2;
    }

    // returns temperature in °C
    int get_temp() const {
        return temp;
    }

    // return % humidity
    int get_hum() const {
        return hum;
    }

    void refresh() {
        sensor.listen();

        sensor.println("Q");
        String reading = sensor.readStringUntil('\n');
        String co2_in = reading.substring(19, 24);
        co2 = co2_in.toInt();

        String temp_in = reading.substring(11, 16);
        temp = (temp_in.toInt() - 1000) / 10;

        String hum_in = reading.substring(3, 8);
        hum = hum_in.toInt() / 10;
    }

    void print_measurements() {
        Serial.println("CO2: " + String(co2) + " ppm");
        Serial.println("Temp: " + String(temp) + " °C");
        Serial.println("Hum: " + String(hum) + "%");
    }

    String get_csv() {
        return String(co2) + ',' + String(temp) + ',' + String(hum);
    }

   private:
    SoftwareSerial sensor;
    int co2;
    int temp;
    int hum;
};

class sprintir {
   public:
    // REQUIRES: type is "COZIR" or "SPRINTIR"
    sprintir(int rx, int tx) : sensor(rx, tx), co2(0) {
        sensor.listen();
        sensor.begin(9600);  // Start serial comms with sprintir sensor
        sensor.println("M 4");  // set mode for filtered co2 output
        sensor.println("K 2");  // set polling mode
    }

    // returns co2 in ppm
    int get_co2() const {
        return co2;
    }

    void refresh() {
        sensor.listen();

        sensor.println(".");
        String reading = sensor.readStringUntil('\n');
        int multiplier = reading.substring(3, 8).toInt();

        sensor.println("Z");
        reading = sensor.readStringUntil('\n');
        co2 = multiplier * reading.substring(3, 8).toInt();
    }

    void print_measurements() {
        Serial.println("CO2: " + String(co2) + " ppm");
    }

    String get_csv() {
        return String(co2);
    }

   private:
    SoftwareSerial sensor;
    int co2;
};

class pressure {
   public:
    pressure(uint8_t pin_in) : pin(pin_in) {}

    // returns pressure in psi
    double get_pressure() {
        double reading = analogRead(pin);
        double voltage = reading / 1023 * 5;
        return voltage * 44.5 / 4 - 20.0625;
    }

    void print_measurements() {
        Serial.println("Pressure: " + String(get_pressure()) + " psi");
    }

   private:
    uint8_t pin;
};