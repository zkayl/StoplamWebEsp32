#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include <SPIFFS.h>

const char* ssid = "ESP32-AP";
IPAddress ip(10, 10, 10, 10);
IPAddress gateway(10, 10, 10, 1);
IPAddress subnet(255, 255, 255, 0);

const int led1 = 13;
const int led2 = 12;
const int led3 = 17;
const int led4 = 16;
const int led5 = 15;
const int led6 = 2;
const int led7 = 4;
const int led8 = 5;
const int led9 = 18;
const int led10 = 19;
const int led11 = 21;
const int led12 = 22;
const int led13 = 23;

const int buttonPin = 34;    // Pin untuk tombol
const int ledPin = 14;       // Pin untuk LED

WebServer server(80);
Preferences preferences;
int currentMode = 1;
bool autoMode = false;
TaskHandle_t autoModeTaskHandle = NULL;

void setup() {
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
    pinMode(led5, OUTPUT);
    pinMode(led6, OUTPUT);
    pinMode(led7, OUTPUT);
    pinMode(led8, OUTPUT);
    pinMode(led9, OUTPUT);
    pinMode(led10, OUTPUT);
    pinMode(led11, OUTPUT);
    pinMode(led12, OUTPUT);
    pinMode(led13, OUTPUT);

    pinMode(buttonPin, INPUT);    // Pin untuk tombol sebagai input
    pinMode(ledPin, OUTPUT);      // Pin untuk LED sebagai output

    preferences.begin("mode", false);
    currentMode = preferences.getInt("currentMode", 1);
    autoMode = preferences.getBool("autoMode", false);

    if (!SPIFFS.begin(true)) {
        Serial.println("SPIFFS Mount Failed");
        return;
    }

    if (!WiFi.softAPConfig(ip, gateway, subnet)) {
        Serial.println("Failed to configure IP address");
    }

    Serial.begin(115200);
    Serial.println("Access Point created");
    Serial.println("AP IP address: " + WiFi.softAPIP().toString());

    server.on("/", HTTP_GET, []() {
        File file = SPIFFS.open("/index.html", "r");
        server.streamFile(file, "text/html");
        file.close();
    });

    server.on("/style.css", HTTP_GET, []() {
        File file = SPIFFS.open("/style.css", "r");
        server.streamFile(file, "text/css");
        file.close();
    });

    server.on("/script.js", HTTP_GET, []() {
        File file = SPIFFS.open("/script.js", "r");
        server.streamFile(file, "application/javascript");
        file.close();
    });

    server.on("/bg.jpg", HTTP_GET, []() {
        File file = SPIFFS.open("/bg.jpg", "r");
        server.streamFile(file, "image/jpeg");
        file.close();
        server.sendHeader("Cache-Control", "max-age=604800");
    });

    server.on("/font.ttf", HTTP_GET, []() {
        File file = SPIFFS.open("/font.ttf", "r");
        server.streamFile(file, "font/ttf");
        file.close();
    });

    for (int i = 1; i <= 17; i++) {
        server.on(String("/mode" + String(i)).c_str(), HTTP_POST, [i]() {
            handleModeChange(i);
            server.send(200, "text/plain", String(currentMode));
        });
    }

    server.on("/autoMode", HTTP_POST, []() {
        handleAutoMode();
        server.send(200, "text/plain", String(currentMode));
    });

    server.on("/currentMode", HTTP_GET, []() {
        server.send(200, "text/plain", String(currentMode));
    });

    server.on("/autoModeStatus", HTTP_GET, []() {
        server.send(200, "text/plain", String(autoMode));
    });

    if (autoMode) {
        startAutoMode();
    }

    server.begin();
}

void loop() {
    server.handleClient();

    // Baca status tombol
    int buttonState = digitalRead(buttonPin);

    // Jika tombol ditekan (dan ESP aktif), matikan ESP dan hidupkan LED
    if (buttonState == HIGH) {
        digitalWrite(ledPin, HIGH);    // Hidupkan LED


        // Matikan ESP
        ESP.deepSleep(0);
    }

    switch (currentMode) {
        case 1:
          /*SET OFF ALL LED*/
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);

          /*START*/

          digitalWrite(led1, HIGH);
          digitalWrite(led13, HIGH);
          delay(50);
          digitalWrite(led2, HIGH);
          digitalWrite(led12, HIGH);
          delay(50);
          digitalWrite(led3, HIGH);
          digitalWrite(led11, HIGH);
          delay(50);
          digitalWrite(led4, HIGH);
          digitalWrite(led10, HIGH);
          delay(50);
          digitalWrite(led5, HIGH);
          digitalWrite(led9, HIGH);
          delay(50);
          digitalWrite(led6, HIGH);
          digitalWrite(led8, HIGH);
          delay(50);
          digitalWrite(led7, HIGH);
          delay(300);
          digitalWrite(led7, LOW);
          delay(50);
          digitalWrite(led6, LOW);
          digitalWrite(led8, LOW);
          delay(50);
          digitalWrite(led5, LOW);
          digitalWrite(led9, LOW);
          delay(50);
          digitalWrite(led4, LOW);
          digitalWrite(led10, LOW);
          delay(50);
          digitalWrite(led3, LOW);
          digitalWrite(led11, LOW);
          delay(50);
          digitalWrite(led2, LOW);
          digitalWrite(led12, LOW);
          delay(50);
          digitalWrite(led1, LOW);
          digitalWrite(led13, LOW);
          delay(300);
          break;

        case 2:
          /*SET OFF ALL LED*/
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);

          /*START*/

          digitalWrite(led1, HIGH);
          digitalWrite(led13, HIGH);
          delay(30);
          digitalWrite(led1, LOW);
          digitalWrite(led13, LOW);
          delay(30);
          digitalWrite(led2, HIGH);
          digitalWrite(led12, HIGH);
          delay(30);
          digitalWrite(led2, LOW);
          digitalWrite(led12, LOW);
          delay(30);
          digitalWrite(led3, HIGH);
          digitalWrite(led11, HIGH);
          delay(30);
          digitalWrite(led3, LOW);
          digitalWrite(led11, LOW);
          delay(30);
          digitalWrite(led4, HIGH);
          digitalWrite(led10, HIGH);
          delay(30);
          digitalWrite(led4, LOW);
          digitalWrite(led10, LOW);
          delay(30);
          digitalWrite(led5, HIGH);
          digitalWrite(led9, HIGH);
          delay(30);
          digitalWrite(led5, LOW);
          digitalWrite(led9, LOW);
          delay(30);
          digitalWrite(led6, HIGH);
          digitalWrite(led8, HIGH);
          delay(30);
          digitalWrite(led6, LOW);
          digitalWrite(led8, LOW);
          delay(30);
          digitalWrite(led7, HIGH);
          delay(30);
          digitalWrite(led7, LOW);
          delay(30);
          digitalWrite(led7, HIGH);
          delay(30);
          digitalWrite(led7, LOW);
          delay(30);
          digitalWrite(led6, HIGH);
          digitalWrite(led8, HIGH);
          delay(30);
          digitalWrite(led6, LOW);
          digitalWrite(led8, LOW);
          delay(30);
          digitalWrite(led5, HIGH);
          digitalWrite(led9, HIGH);
          delay(30);
          digitalWrite(led5, LOW);
          digitalWrite(led9, LOW);
          delay(30);
          digitalWrite(led4, HIGH);
          digitalWrite(led10, HIGH);
          delay(30);
          digitalWrite(led4, LOW);
          digitalWrite(led10, LOW);
          delay(30);
          digitalWrite(led3, HIGH);
          digitalWrite(led11, HIGH);
          delay(30);
          digitalWrite(led3, LOW);
          digitalWrite(led11, LOW);
          delay(30);
          digitalWrite(led2, HIGH);
          digitalWrite(led12, HIGH);
          delay(30);
          digitalWrite(led2, LOW);
          digitalWrite(led12, LOW);
          delay(30);
          digitalWrite(led1, HIGH);
          digitalWrite(led13, HIGH);
          delay(30);
          digitalWrite(led1, LOW);
          digitalWrite(led13, LOW);
          delay(30);
          break;

        case 3:
          /*SET OFF ALL LED*/
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);

          /*START*/

          digitalWrite(led1, HIGH);
          delay(30);
          digitalWrite(led2, HIGH);
          delay(30);
          digitalWrite(led1, LOW);
          delay(30);
          digitalWrite(led2, LOW);
          delay(30);
          digitalWrite(led3, HIGH);
          delay(30);
          digitalWrite(led4, HIGH);
          delay(30);
          digitalWrite(led3, LOW);
          delay(30);
          digitalWrite(led4, LOW);
          delay(30);
          digitalWrite(led5, HIGH);
          delay(30);
          digitalWrite(led6, HIGH);
          delay(30);
          digitalWrite(led5, LOW);
          delay(30);
          digitalWrite(led6, LOW);
          delay(30);
          digitalWrite(led7, HIGH);
          delay(30);
          digitalWrite(led8, HIGH);
          delay(30);
          digitalWrite(led7, LOW);
          delay(30);
          digitalWrite(led8, LOW);
          delay(30);
          digitalWrite(led9, HIGH);
          delay(30);
          digitalWrite(led10, HIGH);
          delay(30);
          digitalWrite(led9, LOW);
          delay(30);
          digitalWrite(led10, LOW);
          delay(30);
          digitalWrite(led11, HIGH);
          delay(30);
          digitalWrite(led12, HIGH);
          delay(30);
          digitalWrite(led11, LOW);
          delay(30);
          digitalWrite(led12, LOW);
          delay(30);
          digitalWrite(led13, HIGH);
          delay(30);
          digitalWrite(led13, LOW);
          delay(30);
          digitalWrite(led13, HIGH);
          delay(30);
          digitalWrite(led13, LOW);
          delay(30);
          digitalWrite(led12, HIGH);
          delay(30);
          digitalWrite(led11, HIGH);
          delay(30);
          digitalWrite(led12, LOW);
          delay(30);
          digitalWrite(led11, LOW);
          delay(30);
          digitalWrite(led10, HIGH);
          delay(30);
          digitalWrite(led9, HIGH);
          delay(30);
          digitalWrite(led10, LOW);
          delay(30);
          digitalWrite(led9, LOW);
          delay(30);
          digitalWrite(led8, HIGH);
          delay(30);
          digitalWrite(led7, HIGH);
          delay(30);
          digitalWrite(led8, LOW);
          delay(30);
          digitalWrite(led7, LOW);
          delay(30);
          digitalWrite(led6, HIGH);
          delay(30);
          digitalWrite(led5, HIGH);
          delay(30);
          digitalWrite(led6, LOW);
          delay(30);
          digitalWrite(led5, LOW);
          delay(30);
          digitalWrite(led4, HIGH);
          delay(30);
          digitalWrite(led3, HIGH);
          delay(30);
          digitalWrite(led4, LOW);
          delay(30);
          digitalWrite(led3, LOW);
          delay(30);
          digitalWrite(led2, HIGH);
          delay(30);
          digitalWrite(led1, HIGH);
          delay(30);
          digitalWrite(led2, LOW);
          delay(30);
          digitalWrite(led1, LOW);
          delay(30);
          break;

        case 4:
          /*SET OFF ALL LED*/
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);

          /*START*/

          digitalWrite(led1, HIGH);
          delay(15);
          digitalWrite(led2, HIGH);
          delay(15);
          digitalWrite(led3, HIGH);
          delay(15);
          digitalWrite(led4, HIGH);
          delay(15);
          digitalWrite(led5, HIGH);
          delay(15);
          digitalWrite(led6, HIGH);
          delay(15);
          digitalWrite(led7, HIGH);
          delay(15);
          digitalWrite(led8, HIGH);
          delay(15);
          digitalWrite(led9, HIGH);
          delay(15);
          digitalWrite(led10, HIGH);
          delay(15);
          digitalWrite(led11, HIGH);
          delay(15);
          digitalWrite(led12, HIGH);
          delay(15);
          digitalWrite(led13, HIGH);
          delay(15);
          digitalWrite(led13, LOW);
          delay(15);
          digitalWrite(led12, LOW);
          delay(15);
          digitalWrite(led11, LOW);
          delay(15);
          digitalWrite(led10, LOW);
          delay(15);
          digitalWrite(led9, LOW);
          delay(15);
          digitalWrite(led8, LOW);
          delay(15);
          digitalWrite(led7, LOW);
          delay(15);
          digitalWrite(led6, LOW);
          delay(15);
          digitalWrite(led5, LOW);
          delay(15);
          digitalWrite(led4, LOW);
          delay(15);
          digitalWrite(led3, LOW);
          delay(15);
          digitalWrite(led2, LOW);
          delay(15);
          digitalWrite(led1, LOW);
          delay(15);
          digitalWrite(led13, HIGH);
          delay(15);
          digitalWrite(led12, HIGH);
          delay(15);
          digitalWrite(led11, HIGH);
          delay(15);
          digitalWrite(led10, HIGH);
          delay(15);
          digitalWrite(led9, HIGH);
          delay(15);
          digitalWrite(led8, HIGH);
          delay(15);
          digitalWrite(led7, HIGH);
          delay(15);
          digitalWrite(led6, HIGH);
          delay(15);
          digitalWrite(led5, HIGH);
          delay(15);
          digitalWrite(led4, HIGH);
          delay(15);
          digitalWrite(led3, HIGH);
          delay(15);
          digitalWrite(led2, HIGH);
          delay(15);
          digitalWrite(led1, HIGH);
          delay(15);
          digitalWrite(led1, LOW);
          delay(15);
          digitalWrite(led2, LOW);
          delay(15);
          digitalWrite(led3, LOW);
          delay(15);
          digitalWrite(led4, LOW);
          delay(15);
          digitalWrite(led5, LOW);
          delay(15);
          digitalWrite(led6, LOW);
          delay(15);
          digitalWrite(led7, LOW);
          delay(15);
          digitalWrite(led8, LOW);
          delay(15);
          digitalWrite(led9, LOW);
          delay(15);
          digitalWrite(led10, LOW);
          delay(15);
          digitalWrite(led11, LOW);
          delay(15);
          digitalWrite(led12, LOW);
          delay(15);
          digitalWrite(led13, LOW);
          delay(15);
          break;

        case 5:
          /*SET OFF ALL LED*/
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);

          /*START*/

          digitalWrite(led1, HIGH);
          digitalWrite(led2, HIGH);
          digitalWrite(led3, HIGH);
          digitalWrite(led7, HIGH);
          digitalWrite(led11, HIGH);
          digitalWrite(led12, HIGH);
          digitalWrite(led13, HIGH);
          delay(35);
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);
          delay(35);
          digitalWrite(led1, HIGH);
          digitalWrite(led2, HIGH);
          digitalWrite(led3, HIGH);
          digitalWrite(led7, HIGH);
          digitalWrite(led11, HIGH);
          digitalWrite(led12, HIGH);
          digitalWrite(led13, HIGH);
          delay(35);
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);
          delay(35);
          digitalWrite(led1, HIGH);
          digitalWrite(led2, HIGH);
          digitalWrite(led3, HIGH);
          digitalWrite(led7, HIGH);
          digitalWrite(led11, HIGH);
          digitalWrite(led12, HIGH);
          digitalWrite(led13, HIGH);
          delay(35);
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);
          delay(35);
          digitalWrite(led1, HIGH);
          digitalWrite(led2, HIGH);
          digitalWrite(led3, HIGH);
          digitalWrite(led7, HIGH);
          digitalWrite(led11, HIGH);
          digitalWrite(led12, HIGH);
          digitalWrite(led13, HIGH);
          delay(35);
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);
          delay(400);

          digitalWrite(led4, HIGH);
          digitalWrite(led5, HIGH);
          digitalWrite(led6, HIGH);
          digitalWrite(led8, HIGH);
          digitalWrite(led9, HIGH);
          digitalWrite(led10, HIGH);
          delay(35);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          delay(35);
          digitalWrite(led4, HIGH);
          digitalWrite(led5, HIGH);
          digitalWrite(led6, HIGH);
          digitalWrite(led8, HIGH);
          digitalWrite(led9, HIGH);
          digitalWrite(led10, HIGH);
          delay(35);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          delay(35);
          digitalWrite(led4, HIGH);
          digitalWrite(led5, HIGH);
          digitalWrite(led6, HIGH);
          digitalWrite(led8, HIGH);
          digitalWrite(led9, HIGH);
          digitalWrite(led10, HIGH);
          delay(35);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          delay(35);
          digitalWrite(led4, HIGH);
          digitalWrite(led5, HIGH);
          digitalWrite(led6, HIGH);
          digitalWrite(led8, HIGH);
          digitalWrite(led9, HIGH);
          digitalWrite(led10, HIGH);
          delay(35);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          delay(400);
          break;

        case 6:
          /*SET OFF ALL LED*/
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);

          /*START*/

          digitalWrite(led4, HIGH);
          delay(35);
          digitalWrite(led10, HIGH);
          delay(35);
          digitalWrite(led7, HIGH);
          delay(35);
          digitalWrite(led4, LOW);
          delay(35);
          digitalWrite(led10, LOW);
          delay(35);
          digitalWrite(led7, LOW);
          delay(35);
          digitalWrite(led2, HIGH);
          delay(35);
          digitalWrite(led12, HIGH);
          delay(35);
          digitalWrite(led2, LOW);
          delay(35);
          digitalWrite(led12, LOW);
          delay(35);
          digitalWrite(led6, HIGH);
          delay(35);
          digitalWrite(led8, HIGH);
          delay(35);
          digitalWrite(led6, LOW);
          delay(35);
          digitalWrite(led8, LOW);
          delay(35);
          digitalWrite(led1, HIGH);
          delay(35);
          digitalWrite(led13, HIGH);
          delay(35);
          digitalWrite(led1, LOW);
          delay(35);
          digitalWrite(led13, LOW);
          delay(35);
          digitalWrite(led5, HIGH);
          delay(35);
          digitalWrite(led9, HIGH);
          delay(35);
          digitalWrite(led5, LOW);
          delay(35);
          digitalWrite(led9, LOW);
          delay(35);
          digitalWrite(led3, HIGH);
          delay(35);
          digitalWrite(led11, HIGH);
          delay(35);
          digitalWrite(led3, LOW);
          delay(35);
          digitalWrite(led11, LOW);
          delay(35);
          break;

        case 7:
          /*SET OFF ALL LED*/
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);

          /*START*/

          digitalWrite(led13, HIGH);
          delay(150);
          digitalWrite(led1, HIGH);
          delay(150);
          digitalWrite(led12, HIGH);
          delay(150);
          digitalWrite(led2, HIGH);
          delay(150);
          digitalWrite(led11, HIGH);
          delay(150);
          digitalWrite(led3, HIGH);
          delay(150);
          digitalWrite(led10, HIGH);
          delay(150);
          digitalWrite(led4, HIGH);
          delay(150);
          digitalWrite(led9, HIGH);
          delay(150);
          digitalWrite(led5, HIGH);
          delay(150);
          digitalWrite(led8, HIGH);
          delay(150);
          digitalWrite(led6, HIGH);
          delay(150);
          digitalWrite(led7, HIGH);
          delay(600);
          digitalWrite(led7, LOW);
          delay(15);
          digitalWrite(led6, LOW);
          delay(15);
          digitalWrite(led8, LOW);
          delay(15);
          digitalWrite(led5, LOW);
          delay(15);
          digitalWrite(led9, LOW);
          delay(15);
          digitalWrite(led4, LOW);
          delay(15);
          digitalWrite(led10, LOW);
          delay(15);
          digitalWrite(led3, LOW);
          delay(15);
          digitalWrite(led11, LOW);
          delay(15);
          digitalWrite(led2, LOW);
          delay(15);
          digitalWrite(led12, LOW);
          delay(15);
          digitalWrite(led1, LOW);
          delay(15);
          digitalWrite(led13, LOW);
          delay(250);
          break;

        case 8:
          /*SET OFF ALL LED*/
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);

          /*START*/

          digitalWrite(led1, HIGH);
          digitalWrite(led7, HIGH);
          digitalWrite(led13, HIGH);
          delay(20);
          digitalWrite(led1, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led13, LOW);
          delay(20);
          digitalWrite(led1, HIGH);
          digitalWrite(led7, HIGH);
          digitalWrite(led13, HIGH);
          delay(20);
          digitalWrite(led1, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led13, LOW);
          delay(20);
          digitalWrite(led3, HIGH);
          digitalWrite(led11, HIGH);
          digitalWrite(led6, HIGH);
          digitalWrite(led8, HIGH);
          delay(20);
          digitalWrite(led3, LOW);
          digitalWrite(led1, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led8, LOW);
          delay(20);
          digitalWrite(led3, HIGH);
          digitalWrite(led11, HIGH);
          digitalWrite(led6, HIGH);
          digitalWrite(led8, HIGH);
          delay(20);
          digitalWrite(led3, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led8, LOW);
          delay(20);
          digitalWrite(led5, HIGH);
          digitalWrite(led9, HIGH);
          digitalWrite(led4, HIGH);
          delay(20);
          digitalWrite(led5, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led4, LOW);
          delay(20);
          digitalWrite(led10, HIGH);
          digitalWrite(led2, HIGH);
          digitalWrite(led12, HIGH);
          delay(20);
          digitalWrite(led10, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led12, LOW);
          delay(20);
          break;

        case 9:
          /*SET OFF ALL LED*/
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);

          /*START*/

          digitalWrite(led3, HIGH);
          delay(40);
          digitalWrite(led3, LOW);
          delay(40);
          digitalWrite(led3, HIGH);
          delay(40);
          digitalWrite(led3, LOW);
          delay(40);
          digitalWrite(led3, HIGH);
          delay(40);
          digitalWrite(led11, HIGH);
          delay(40);
          digitalWrite(led11, LOW);
          delay(40);
          digitalWrite(led11, HIGH);
          delay(40);
          digitalWrite(led11, LOW);
          delay(40);
          digitalWrite(led11, HIGH);
          delay(40);
          digitalWrite(led6, HIGH);
          delay(40);
          digitalWrite(led6, LOW);
          delay(40);
          digitalWrite(led6, HIGH);
          delay(40);
          digitalWrite(led6, LOW);
          delay(40);
          digitalWrite(led6, HIGH);
          delay(40);
          digitalWrite(led8, HIGH);
          delay(40);
          digitalWrite(led8, LOW);
          delay(40);
          digitalWrite(led8, HIGH);
          delay(40);
          digitalWrite(led8, LOW);
          delay(40);
          digitalWrite(led8, HIGH);
          delay(40);
          digitalWrite(led1, HIGH);
          delay(40);
          digitalWrite(led1, LOW);
          delay(40);
          digitalWrite(led1, HIGH);
          delay(40);
          digitalWrite(led1, LOW);
          delay(40);
          digitalWrite(led1, HIGH);
          delay(40);
          digitalWrite(led7, HIGH);
          delay(40);
          digitalWrite(led7, LOW);
          delay(40);
          digitalWrite(led7, HIGH);
          delay(40);
          digitalWrite(led7, LOW);
          delay(40);
          digitalWrite(led7, HIGH);
          delay(40);
          digitalWrite(led13, HIGH);
          delay(40);
          digitalWrite(led13, LOW);
          delay(40);
          digitalWrite(led13, HIGH);
          delay(40);
          digitalWrite(led13, LOW);
          delay(40);
          digitalWrite(led13, HIGH);
          delay(40);
          digitalWrite(led2, HIGH);
          delay(40);
          digitalWrite(led2, LOW);
          delay(40);
          digitalWrite(led2, HIGH);
          delay(40);
          digitalWrite(led2, LOW);
          delay(40);
          digitalWrite(led2, HIGH);
          delay(40);
          digitalWrite(led12, HIGH);
          delay(40);
          digitalWrite(led12, LOW);
          delay(40);
          digitalWrite(led12, HIGH);
          delay(40);
          digitalWrite(led12, LOW);
          delay(40);
          digitalWrite(led12, HIGH);
          delay(40);
          digitalWrite(led5, HIGH);
          delay(40);
          digitalWrite(led5, LOW);
          delay(40);
          digitalWrite(led5, HIGH);
          delay(40);
          digitalWrite(led5, LOW);
          delay(40);
          digitalWrite(led5, HIGH);
          delay(40);
          digitalWrite(led10, HIGH);
          delay(40);
          digitalWrite(led10, LOW);
          delay(40);
          digitalWrite(led10, HIGH);
          delay(40);
          digitalWrite(led10, LOW);
          delay(40);
          digitalWrite(led10, HIGH);
          delay(40);
          digitalWrite(led4, HIGH);
          delay(40);
          digitalWrite(led4, LOW);
          delay(40);
          digitalWrite(led4, HIGH);
          delay(40);
          digitalWrite(led4, LOW);
          delay(40);
          digitalWrite(led4, HIGH);
          delay(40);
          digitalWrite(led9, HIGH);
          delay(40);
          digitalWrite(led9, LOW);
          delay(40);
          digitalWrite(led9, HIGH);
          delay(40);
          digitalWrite(led9, LOW);
          delay(40);
          digitalWrite(led9, HIGH);
          delay(200);
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);
          delay(40);
          digitalWrite(led1, HIGH);
          digitalWrite(led2, HIGH);
          digitalWrite(led3, HIGH);
          digitalWrite(led4, HIGH);
          digitalWrite(led5, HIGH);
          digitalWrite(led6, HIGH);
          digitalWrite(led7, HIGH);
          digitalWrite(led8, HIGH);
          digitalWrite(led9, HIGH);
          digitalWrite(led10, HIGH);
          digitalWrite(led11, HIGH);
          digitalWrite(led12, HIGH);
          digitalWrite(led13, HIGH);
          delay(40);
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);
          delay(40);
          digitalWrite(led1, HIGH);
          digitalWrite(led2, HIGH);
          digitalWrite(led3, HIGH);
          digitalWrite(led4, HIGH);
          digitalWrite(led5, HIGH);
          digitalWrite(led6, HIGH);
          digitalWrite(led7, HIGH);
          digitalWrite(led8, HIGH);
          digitalWrite(led9, HIGH);
          digitalWrite(led10, HIGH);
          digitalWrite(led11, HIGH);
          digitalWrite(led12, HIGH);
          digitalWrite(led13, HIGH);
          delay(40);
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);
          delay(40);
          digitalWrite(led1, HIGH);
          digitalWrite(led2, HIGH);
          digitalWrite(led3, HIGH);
          digitalWrite(led4, HIGH);
          digitalWrite(led5, HIGH);
          digitalWrite(led6, HIGH);
          digitalWrite(led7, HIGH);
          digitalWrite(led8, HIGH);
          digitalWrite(led9, HIGH);
          digitalWrite(led10, HIGH);
          digitalWrite(led11, HIGH);
          digitalWrite(led12, HIGH);
          digitalWrite(led13, HIGH);
          delay(200);
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);
          delay(40);
          break;

        case 10:
          /*SET OFF ALL LED*/
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);

          /*START*/

          digitalWrite(led1, HIGH);
          delay(60);
          digitalWrite(led2, HIGH);
          delay(60);
          digitalWrite(led3, HIGH);
          delay(60);
          digitalWrite(led4, HIGH);
          delay(60);
          digitalWrite(led5, HIGH);
          delay(60);
          digitalWrite(led6, HIGH);
          delay(60);
          digitalWrite(led7, HIGH);
          delay(60);
          digitalWrite(led8, HIGH);
          delay(60);
          digitalWrite(led9, HIGH);
          delay(60);
          digitalWrite(led10, HIGH);
          delay(60);
          digitalWrite(led11, HIGH);
          delay(60);
          digitalWrite(led12, HIGH);
          delay(60);
          digitalWrite(led13, HIGH);
          delay(200);
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);
          delay(60);
          digitalWrite(led13, HIGH);
          delay(60);
          digitalWrite(led12, HIGH);
          delay(60);
          digitalWrite(led11, HIGH);
          delay(60);
          digitalWrite(led10, HIGH);
          delay(60);
          digitalWrite(led9, HIGH);
          delay(60);
          digitalWrite(led8, HIGH);
          delay(60);
          digitalWrite(led7, HIGH);
          delay(60);
          digitalWrite(led6, HIGH);
          delay(60);
          digitalWrite(led5, HIGH);
          delay(60);
          digitalWrite(led4, HIGH);
          delay(60);
          digitalWrite(led3, HIGH);
          delay(60);
          digitalWrite(led2, HIGH);
          delay(60);
          digitalWrite(led1, HIGH);
          delay(200);
          break;

        case 11:
          /*SET OFF ALL LED*/
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);

          /*START*/

          digitalWrite(led1, HIGH);
          digitalWrite(led2, HIGH);
          digitalWrite(led3, HIGH);
          digitalWrite(led4, HIGH);
          digitalWrite(led5, HIGH);
          digitalWrite(led6, HIGH);
          digitalWrite(led7, HIGH);
          delay(100);
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led7, LOW);
          delay(100);
          digitalWrite(led1, HIGH);
          digitalWrite(led2, HIGH);
          digitalWrite(led3, HIGH);
          digitalWrite(led4, HIGH);
          digitalWrite(led5, HIGH);
          digitalWrite(led6, HIGH);
          digitalWrite(led7, HIGH);
          delay(100);
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led7, LOW);
          delay(100);
          digitalWrite(led1, HIGH);
          digitalWrite(led2, HIGH);
          digitalWrite(led3, HIGH);
          digitalWrite(led4, HIGH);
          digitalWrite(led5, HIGH);
          digitalWrite(led6, HIGH);
          digitalWrite(led7, HIGH);
          delay(100);
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led7, LOW);
          delay(100);
          digitalWrite(led1, HIGH);
          digitalWrite(led2, HIGH);
          digitalWrite(led3, HIGH);
          digitalWrite(led4, HIGH);
          digitalWrite(led5, HIGH);
          digitalWrite(led6, HIGH);
          digitalWrite(led7, HIGH);
          delay(100);
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led7, LOW);
          delay(100);

          digitalWrite(led7, HIGH);
          digitalWrite(led8, HIGH);
          digitalWrite(led9, HIGH);
          digitalWrite(led10, HIGH);
          digitalWrite(led11, HIGH);
          digitalWrite(led12, HIGH);
          digitalWrite(led13, HIGH);
          delay(100);
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);
          delay(100);
          digitalWrite(led7, HIGH);
          digitalWrite(led8, HIGH);
          digitalWrite(led9, HIGH);
          digitalWrite(led10, HIGH);
          digitalWrite(led11, HIGH);
          digitalWrite(led12, HIGH);
          digitalWrite(led13, HIGH);
          delay(100);
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);
          delay(100);
          digitalWrite(led7, HIGH);
          digitalWrite(led8, HIGH);
          digitalWrite(led9, HIGH);
          digitalWrite(led10, HIGH);
          digitalWrite(led11, HIGH);
          digitalWrite(led12, HIGH);
          digitalWrite(led13, HIGH);
          delay(100);
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);
          delay(100);
          digitalWrite(led7, HIGH);
          digitalWrite(led8, HIGH);
          digitalWrite(led9, HIGH);
          digitalWrite(led10, HIGH);
          digitalWrite(led11, HIGH);
          digitalWrite(led12, HIGH);
          digitalWrite(led13, HIGH);
          delay(100);
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);
          delay(100);
          break;

        case 12:
          /*SET OFF ALL LED*/
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);

          /*START*/

          digitalWrite(led1, HIGH);
          digitalWrite(led2, HIGH);
          digitalWrite(led3, HIGH);
          digitalWrite(led4, HIGH);
          digitalWrite(led5, HIGH);
          digitalWrite(led6, HIGH);
          digitalWrite(led7, HIGH);
          digitalWrite(led8, HIGH);
          digitalWrite(led9, HIGH);
          digitalWrite(led10, HIGH);
          digitalWrite(led11, HIGH);
          digitalWrite(led12, HIGH);
          digitalWrite(led13, HIGH);
          delay(20);

          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);
          delay(1000);
          break;

        case 13:
          /*SET OFF ALL LED*/
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);

          /*START*/

          digitalWrite(led1, HIGH);
          digitalWrite(led3, HIGH);
          digitalWrite(led11, HIGH);
          digitalWrite(led13, HIGH);
          delay(70);
          digitalWrite(led1, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led13, LOW);
          delay(70);

          digitalWrite(led3, HIGH);
          digitalWrite(led5, HIGH);
          digitalWrite(led11, HIGH);
          digitalWrite(led9, HIGH);
          delay(70);
          digitalWrite(led3, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led9, LOW);
          delay(70);

          digitalWrite(led5, HIGH);
          digitalWrite(led7, HIGH);
          digitalWrite(led9, HIGH);
          delay(70);
          digitalWrite(led5, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led9, LOW);
          delay(70);

          digitalWrite(led5, HIGH);
          digitalWrite(led3, HIGH);
          digitalWrite(led9, HIGH);
          digitalWrite(led11, HIGH);
          delay(70);
          digitalWrite(led5, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led11, LOW);
          delay(70);

          digitalWrite(led1, HIGH);
          digitalWrite(led3, HIGH);
          digitalWrite(led11, HIGH);
          digitalWrite(led13, HIGH);
          delay(70);
          digitalWrite(led1, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led13, LOW);
          delay(70);
          break;

        case 14:
          /*SET OFF ALL LED*/
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);

          /*START*/

          digitalWrite(led1, HIGH);
          digitalWrite(led13, HIGH);
          delay(50);
          digitalWrite(led1, LOW);
          digitalWrite(led13, LOW);
          delay(50);
          break;

        case 15:
          /*SET OFF ALL LED*/
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);

          /*START*/

          digitalWrite(led2, HIGH);
          digitalWrite(led12, HIGH);
          delay(50);
          digitalWrite(led2, LOW);
          digitalWrite(led12, LOW);
          delay(50);
          break;

        case 16:
          /*SET OFF ALL LED*/
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);

          /*START*/

          digitalWrite(led3, HIGH);
          digitalWrite(led11, HIGH);
          delay(50);
          digitalWrite(led3, LOW);
          digitalWrite(led11, LOW);
          delay(50);
          break;

        case 17:
          /*SET OFF ALL LED*/
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);

          /*START*/

          digitalWrite(led4, HIGH);
          digitalWrite(led10, HIGH);
          delay(50);
          digitalWrite(led4, LOW);
          digitalWrite(led10, LOW);
          delay(50);
          break;

        case 18:
          /*SET OFF ALL LED*/
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          digitalWrite(led10, LOW);
          digitalWrite(led11, LOW);
          digitalWrite(led12, LOW);
          digitalWrite(led13, LOW);

          /*START*/

          digitalWrite(led5, HIGH);
          digitalWrite(led9, HIGH);
          delay(50);
          digitalWrite(led5, LOW);
          digitalWrite(led9, LOW);
          delay(50);
          break;
    }
}

void saveCurrentMode(int mode) {
    preferences.putInt("currentMode", mode);
}

void handleModeChange(int newMode) {
    currentMode = newMode;
    saveCurrentMode(currentMode);
    if (autoMode) {
        autoMode = false;
        preferences.putBool("autoMode", autoMode);
        vTaskDelete(autoModeTaskHandle);
    }
}

void handleAutoMode() {
    if (!autoMode) {
        autoMode = true;
        preferences.putBool("autoMode", autoMode);
        startAutoMode();
    } else {
        autoMode = false;
        preferences.putBool("autoMode", autoMode);
        vTaskDelete(autoModeTaskHandle);
    }
}

void startAutoMode() {
    xTaskCreate(autoModeTask, "AutoModeTask", 2048, NULL, 1, &autoModeTaskHandle);
}

void autoModeTask(void * parameter) {
    while (autoMode) {
        currentMode = random(1, 18);
        saveCurrentMode(currentMode);
        vTaskDelay(5000 / portTICK_PERIOD_MS); // Change mode every 5 seconds
    }
    vTaskDelete(NULL);
}
