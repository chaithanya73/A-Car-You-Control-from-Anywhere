#include <WiFi.h>
#include <Arduino.h>
#include <Wire.h>

#define echopin 2
#define trigpin 4

long duration, distance;

const char* ssid = "chaithanya";
const char* password = "29092004";


WiFiServer server(80);

void setup() {
    Serial.begin(9600);

    pinMode(trigpin, OUTPUT);
    pinMode(echopin, INPUT);

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    server.begin();
}

void loop() {
    WiFiClient client = server.available();
    
    if (client) {
        distance = sensor();
          if(distance<100){
              distance= distance;
          }
          else{
              distance=0;
          }
        //Serial.println(distance);

        String currentLine = "";
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                Serial.write(c);

                if (c == '\n') {
                    if (currentLine.length() == 0) {
                        sendHttpResponse(client);
                        break;
                    } else {
                        currentLine = "";
                    }
                } else if (c != '\r') {
                    currentLine += c;
                }

                if (currentLine.endsWith("GET /F")) {
                    // Move forward logic
                    // Example: moveForward();
                }
                if (currentLine.endsWith("GET /B")) {
                    // Move backward logic
                    // Example: moveBackward();
                }
                if (currentLine.endsWith("GET /distance")) {
                    // Send current distance
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-type: text/plain");
                    client.println();
                    client.println(distance);
                    break;
                }
            }
        }
        client.stop();
    }
}

long sensor() {
    digitalWrite(trigpin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigpin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigpin, LOW);

    duration = pulseIn(echopin, HIGH);
    // Convert duration to distance in centimeters
    return duration * 0.034 / 2;
}

void sendHttpResponse(WiFiClient client) {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type: text/html");
    client.println();
    client.println("<!DOCTYPE html>");
    client.println("<html>");
    client.println("<head>");
    client.println("<style>");
    client.println(".button-container { display: grid; grid-template-columns: auto auto; gap: 10px; }");
    client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; }");
    client.println("</style>");
    client.println("<script>");
    client.println("function reloadDistance() {");
    client.println("  var xhttp = new XMLHttpRequest();");
    client.println("  xhttp.onreadystatechange = function() {");
    client.println("    if (this.readyState == 4 && this.status == 200) {");
    client.println("      document.getElementById('distance').innerHTML = this.responseText;");
    client.println("    }");
    client.println("  };");
    client.println("  xhttp.open('GET', '/distance', true);"); 
    client.println("  xhttp.send();");
    client.println("}");
    client.println("setInterval(reloadDistance, 1000);");
    client.println("</script>");
    client.println("</head>");
    client.println("<body>");
    client.println("<h1>Radar Data</h1>");
    client.println("<div id='distance'>" + String(distance) + "</div>");
    client.println("<div class='button-container'>");
    client.println("  <button class='button' onclick=\"location.href='/F1234 '\">Forward</button>");
    client.println("  <button class='button' onclick=\"location.href='/L1234 '\">Left</button>");
    client.println("</div>");
    client.println("<div class='button-container'>");
    client.println("  <button class='button' onclick=\"location.href='/B1234 '\">Backward</button>");
    client.println("  <button class='button' onclick=\"location.href='/R1234 '\">Right</button>");
    client.println("</div>");
    // Add the new buttons for automatic and manual modes
    client.println("<div class='button-container'>");
    client.println("  <button class='button' onclick=\"location.href='/A1234 '\">Automatic</button>");
    client.println("  <button class='button' onclick=\"location.href='/M12341111111111111111111 '\">Manual</button>");
    client.println("</div>");
    client.println("</body>");
    client.println("</html>");
}