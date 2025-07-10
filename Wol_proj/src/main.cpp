#include <WiFi.h>
#include <WiFiUdp.h>
#include <WebServer.h> // <-- eklendi

const char* ssid = "Wifi Name";
const char* password = "WiFi Password";
byte macAddress[] = { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF }; // dummy mac adress

WiFiUDP udp;
WebServer server(80); // <-- eklendi

void sendWOL() {
  const int wolPort = 9;
  byte magicPacket[102];
  for (int i = 0; i < 6; i++) magicPacket[i] = 0xFF;
  for (int i = 1; i <= 16; i++) memcpy(&magicPacket[i * 6], macAddress, 6);

  udp.beginPacket("255.255.255.255", wolPort);
  udp.write(magicPacket, sizeof(magicPacket));
  udp.endPacket();

  Serial.println("Wake-on-LAN paketi gönderildi.");
}

// HTTP tetikleyici endpoint
void handleWOL() {
  sendWOL();
  server.send(200, "text/plain", "WOL sent!");
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.println(WiFi.localIP());

  server.on("/wake", handleWOL);  // <-- tetikleme için endpoint
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();  // <-- HTTP isteklerini dinle
}