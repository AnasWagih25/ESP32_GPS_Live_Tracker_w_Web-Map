#include <WiFi.h>
#include <WebServer.h>
#include <LiquidCrystal_I2C.h>

#define GPS_RX_PIN 16
#define GPS_TX_PIN 17

const char* ssid = "Mi";
const char* password = "123456789";

WebServer server(80);
HardwareSerial gpsSerial(2);

// I2C LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change 0x27 if needed

String latitude = "0.0";
String longitude = "0.0";
String altitude = "0.0";
String satellites = "00";
bool gpsConnected = false;  // Track if GPS is connected

// Convert ddmm.mmmm to decimal degrees
String convertToDecimal(String raw, String dir) {
  if (raw.length() < 6) return "0.0";
  int dot = raw.indexOf('.');
  int degLen = dot - 2;
  float deg = raw.substring(0, degLen).toFloat();
  float min = raw.substring(degLen).toFloat();
  float decimal = deg + (min / 60.0);
  if (dir == "S" || dir == "W") decimal *= -1;
  return String(decimal, 6);
}

void readGPS() {
  static String line = "";
  while (gpsSerial.available()) {
    char c = gpsSerial.read();
    if (c == '\n') {
      if (line.startsWith("$GPGGA")) {
        int idx = 0;
        String parts[15];
        for (int i = 0; i < 15; i++) parts[i] = "";
        for (int i = 0; i < line.length(); i++) {
          if (line[i] == ',') {
            if (idx < 14) idx++;
          } else {
            if (idx < 15) parts[idx] += line[i];
          }
        }

        if (parts[2].length() > 0 && parts[4].length() > 0) {
          latitude = convertToDecimal(parts[2], parts[3]);
          longitude = convertToDecimal(parts[4], parts[5]);
          altitude = parts[9];
          satellites = parts[7];

          if (!gpsConnected) {
            gpsConnected = true;
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("GPS Connected");
          }
        }
      }
      line = "";
    } else {
      line += c;
    }
  }
}

String buildHTML() {
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <meta http-equiv="refresh" content="5">
      <title>ESP32 GPS Live Map</title>
      <style>
        body { font-family: Arial; background: #ccc; text-align: center; }
        #map { height: 400px; margin: 10px auto; width: 90%; }
        .info { background: #eee; padding: 10px; border-radius: 10px; display: inline-block; }
      </style>
      <link rel="stylesheet" href="https://unpkg.com/leaflet@1.9.4/dist/leaflet.css" />
      <script src="https://unpkg.com/leaflet@1.9.4/dist/leaflet.js"></script>
    </head>
    <body>
      <h2>ESP32 GPS Live Map</h2>
      <div class="info">
        <p><strong>Latitude:</strong> )rawliteral" + latitude + R"rawliteral(</p>
        <p><strong>Longitude:</strong> )rawliteral" + longitude + R"rawliteral(</p>
        <p><strong>Altitude:</strong> )rawliteral" + altitude + R"rawliteral( m</p>
        <p><strong>Satellites:</strong> )rawliteral" + satellites + R"rawliteral(</p>
      </div>
      <div id="map"></div>
      <script>
        var map = L.map('map').setView([)rawliteral" + latitude + R"rawliteral(, )rawliteral" + longitude + R"rawliteral(], 15);
        L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
          maxZoom: 19
        }).addTo(map);
        L.marker([)rawliteral" + latitude + R"rawliteral(, )rawliteral" + longitude + R"rawliteral(]).addTo(map);
      </script>
    </body>
    </html>
  )rawliteral";
  return html;
}

void handleRoot() {
  server.send(200, "text/html", buildHTML());
}

void setup() {
  Serial.begin(115200);
  gpsSerial.begin(9600, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);

  // LCD init
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Waiting for GPS");

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected. IP: " + WiFi.localIP().toString());

  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  readGPS();
  server.handleClient();
}
