#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* ssid = "NÁZEV_WIFÍ_SÍTĚ";
const char* password = "HESLO_WIFÍ_SÍTĚ";
const char* mqtt_server = "IP_ADRESA_MQTT_BROKERA";
const int mqtt_port = 1883;
const char* mqtt_user = "UŽIVATELSKÉ_JMÉNO";
const char* mqtt_password = "HESLO";

const int relayPin = 2;
const int pirPin = 4;
const int DHT_PIN = 5;
const int DHT_TYPE = DHT11;
const int encoderPinA = 18;
const int encoderPinB = 19;
volatile int lastEncoded = 0;
volatile long encoderValue = 0;
long lastencoderValue = 0;

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHT_PIN, DHT_TYPE);
RTC_DS3231 rtc;

void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  if (strcmp(topic, "topic/svetla") == 0) {
    if (message == "ON") {
      digitalWrite(relayPin, HIGH);
    } else if (message == "OFF") {
      digitalWrite(relayPin, LOW);
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
      client.subscribe("topic/svetla");
      client.subscribe("topic/teplota");
      client.subscribe("topic/vlhkost");
    } else {
      delay(5000);
    }
  }
}

void IRAM_ATTR handleEncoder() {
  int MSB = digitalRead(encoderPinA);
  int LSB = digitalRead(encoderPinB);
  int encoded = (MSB << 1) | LSB;
  int sum = (lastEncoded << 2) | encoded;
  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue++;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue--;
  lastEncoded = encoded;
}

void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(pirPin, INPUT);
  dht.begin();
  attachInterrupt(encoderPinA, handleEncoder, CHANGE);
  attachInterrupt(encoderPinB, handleEncoder, CHANGE);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  rtc.begin();
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(1000);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  DateTime now = rtc.now();
  String timeStr = String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
  
  int motionDetected = digitalRead(pirPin);
  if (motionDetected == HIGH) {
    client.publish("topic/pohyb", "Detekován pohyb");
  }

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (!isnan(temperature) && !isnan(humidity)) {
    String tempStr = String(temperature);
    String humStr = String(humidity);
    client.publish("topic/teplota", tempStr.c_str());
    client.publish("topic/vlhkost", humStr.c_str());
  }

  if (encoderValue != lastencoderValue) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("Teplota: ");
    display.print(temperature);
    display.print("C");
    display.setCursor(0, 10);
    display.print("Vlhkost: ");
    display.print(humidity);
    display.print("%");
    display.setCursor(0, 20);
    display.print("Nastavena teplota: ");
    display.print(encoderValue);
    display.print("C");
    display.setCursor(0, 30);
    display.print("Cas: ");
    display.print(timeStr);
    display.display();
    lastencoderValue = encoderValue;
  }
  delay(1000);
}
