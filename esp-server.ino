#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
// Replace with your network credentials
const char* ssid = "ssid";
const char* password = "wifi password";
 
ESP8266WebServer server(80);   //instantiate server at port 80 (http port)
 
String page = "";
String header = "";
String content = "";
String footer = "";
int RELAY = 13;

void setup(void){
  //the HTML of the web page
  header = "<html><link rel=\"stylesheet\" href=\"https://unpkg.com/purecss@1.0.0/build/pure-min.css\"><body style=\"text-align: center\">";
  content = "<h1>Frontdoor</h1><p><a class=\"pure-button pure-button-primary\" href=\"open\">Open door</a></p>";
  footer = "</body></html>";
  page = header + content + footer;
  //make the LED pin output and initially turned off
  pinMode(RELAY, INPUT);
  digitalWrite(RELAY, LOW);
   
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password); //begin WiFi connection
  Serial.println("");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
   
  server.on("/", [](){
    server.send(200, "text/html", page);
  });
  server.on("/open", [](){
    server.send(200, "text/html", page);
    pinMode(RELAY, OUTPUT);
    delay(1000);
    pinMode(RELAY, INPUT);
  });
  server.begin();
  Serial.println("Web server started!");
}
 
void loop(void){
  server.handleClient();
}
