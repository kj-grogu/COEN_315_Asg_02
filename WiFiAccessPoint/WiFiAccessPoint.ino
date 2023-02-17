/*
  WiFiAccessPoint.ino creates a WiFi access point and provides a web server on it.

  Steps:
  1. Connect to the access point "yourAp"
  2. Point your web browser to http://192.168.4.1/H to turn the LED on or http://192.168.4.1/L to turn it off
     OR
     Run raw TCP "GET /H" and "GET /L" on PuTTY terminal with 192.168.4.1 as IP address and 80 as port

  Created for arduino-esp32 on 04 July, 2018
  by Elochukwu Ifediora (fedy0)
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

#define LED_BUILTIN 2   // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED

// Set these to your desired credentials.
const char *ssid = "bharti";
const char *password = "";

AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
	<head>
		<meta name="viewport" content="width=device-width, initial-scale=1">
		<link rel="icon" href="data:,">
		<style>
			html { font-family: Consolas; display: inline-block; margin: 0px auto; text-align: center;}
			.button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;
			text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}
			.button2 {background-color: #555555;}
        </style>
	</head>
	<body>
		<h2>Bharti Prakash ESP32 Web Server</h2>
		<p>GIOP 26 - State on</p>
		<p><a href="/26/off"><button class="button button2">OFF</button></a></p>
		<p>GIOP 27 - State on</p>
		<p><a href="/27/off"><button class="button button2">OFF</button></a></p>
	</body>
</html>
)rawliteral";

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output26State = "off";
String output27State = "off";

// Assign output variables to GPIO pins
const int output26 = 26;
const int output27 = 27;


void setup() {
  Serial.begin(115200);
  
    // Initialize the output variables as outputs
  pinMode(output26, OUTPUT);
  pinMode(output27, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output26, LOW);
  digitalWrite(output27, LOW);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html);
  });

  // Start server
  server.begin();
}

void loop() {
}
