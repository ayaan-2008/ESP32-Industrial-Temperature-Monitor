#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#define WARNING_LED 18
#define ALARM_LED 19
#define AUTO_LED 21

#define ACK_BUTTON 15

const float threshold = 30.0;
const float warningRange = 3.0;
const float criticalRange = 10.0;

volatile bool ackPressed = false;

void IRAM_ATTR buttonISR() {
  ackPressed = true;
}

void setup() {

  Serial.begin(115200);
  sensors.begin();
  pinMode(WARNING_LED, OUTPUT);
  pinMode(ALARM_LED, OUTPUT);
  pinMode(AUTO_LED, OUTPUT);

  pinMode(ACK_BUTTON, INPUT_PULLUP);

  attachInterrupt(
    digitalPinToInterrupt(ACK_BUTTON),
    buttonISR,
    FALLING
  );

  Serial.println("Temperature Monitoring System Started");
}

float readTemperature() {

  sensors.requestTemperatures();

  float tempC = sensors.getTempCByIndex(0);

  if (tempC == DEVICE_DISCONNECTED_C) {
    Serial.println("DS18B20 Not Found!");
    return -999;
  }

  return tempC;
}
void loop() {

  float temp = readTemperature();
  if (temp == -999) {
  delay(1000);
  return;
}
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" C");

  digitalWrite(WARNING_LED, LOW);
  digitalWrite(ALARM_LED, LOW);
  digitalWrite(AUTO_LED, LOW);

  if (temp > threshold + warningRange &&
    temp <= threshold + criticalRange) { 

    digitalWrite(WARNING_LED, HIGH);

    Serial.println("WARNING: Temperature Near Limit");

  }

  else if (temp > threshold + criticalRange) {

    Serial.println("CRITICAL TEMPERATURE!");

    unsigned long startTime = millis();

    ackPressed = false;

    while (millis() - startTime < 10000) {
for(int i=0;i<5;i++)
{
    digitalWrite(ALARM_LED,HIGH);
    delay(100);

    digitalWrite(ALARM_LED,LOW);
    delay(100);
}

delay(500);

      if (ackPressed) {

        Serial.println("Human Acknowledged Alarm");
       digitalWrite(AUTO_LED, HIGH);
        digitalWrite(ALARM_LED, LOW);

        return;
      }
    }

    Serial.println("No Human Response");

    Serial.println("Auto-Acknowledgment Activated");

    digitalWrite(AUTO_LED, HIGH);

    delay(3000);
  }

  delay(1000);
}
