#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Manager";
const char* password = "marauder";

WebServer server(80);

String receivedText = "";

// Maximum number of lines in receivedText
const int maxLines = 30;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Manually assign IP address, subnet mask, and gateway
  IPAddress ip(10, 10, 1, 1);
  IPAddress subnet(255, 255, 255, 0);
  IPAddress gateway(10, 10, 1, 1);
  WiFi.softAPConfig(ip, gateway, subnet);

  // Configure ESP32 as Access Point
  WiFi.softAP(ssid, password);

  // Setup routes
  server.on("/", HTTP_GET, []() {
    String html = "<style>body{text-align:center;}</style>";
    html += "<div style='border: 1px solid black; padding: 10px; margin-bottom: 10px; text-align: left; display: inline-block;'>";
    html += "<p>" + receivedText + "</p></div>";
    html += "<form id='cmdForm' method='post' action='/command'>";
    html += "<div style='margin-bottom: 10px;'>";
    html += "<label for='cmd'>Enter Command:</label><input type='text' name='cmd'>";
    html += "<input type='submit' value='Send'></div></form>";
    html += "<div>";
    html += "<button type='button' onclick=\"document.getElementsByName('cmd')[0].value='stopscan';\">STOP</button>";
    html += "<button type='button' onclick=\"document.getElementsByName('cmd')[0].value='ssid -a -n WiFi';\">ADD SSID</button>";
    html += "<button type='button' onclick=\"document.getElementsByName('cmd')[0].value='scanap';\">SCAN AP</button>";
    html += "<select id='blespam' onchange=\"document.getElementsByName('cmd')[0].value=this.value;\">";
    html += "<option value=''>BLE Spam</option>";
    html += "<option value='blespam -t apple'>Spam Apple Devices</option>";
    html += "<option value='blespam -t all'>Spam All Devices</option>";
    html += "<option value='blespam -t samsung'>Spam Samsung Devices</option>";
    html += "</select>";
    html += "<select id='beaconspam' onchange=\"document.getElementsByName('cmd')[0].value=this.value;\">";
    html += "<option value=''>Beacon Spam</option>";
    html += "<option value='attack beacon -t rickroll'>Rickroll</option>";
    html += "<option value='attack -t beacon -r'>Random</option>";
    html += "<option value='attack -t beacon -l'>SSID List</option>";
    html += "<option value='attack -t beacon -a'>AP List</option>";
    html += "</select>";
    html += "</div>";
    server.send(200, "text/html", html);
  });

  server.on("/command", HTTP_POST, []() {
    String command = server.arg("cmd");
    Serial.println(command);
  });

  server.begin();
}

void loop() {
  server.handleClient();

  // Check for incoming serial data
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      receivedText += "<br>";
      // Check if number of lines exceeds the maximum
      int numLines = countLines(receivedText);
      if (numLines > maxLines) {
        // Find the position of the first <br> tag
        int brPosition = receivedText.indexOf("<br>");
        // Remove everything up to and including the first <br> tag
        receivedText = receivedText.substring(brPosition + 4);
      }
    } else {
      receivedText += c;
    }
  }
}

// Function to count the number of lines in a string
int countLines(String text) {
  int count = 0;
  int index = -1;
  while ((index = text.indexOf("<br>", index + 1)) != -1) {
    count++;
  }
  return count;
}
