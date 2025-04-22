#include <WiFi.h>
#include <Servo.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* ssid     = "Rohilla";
const char* password = "87654321";
WiFiServer server(80);
String header;
unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

// Auxiliar variables to store the current output state
String output1State = "off";
String output2State = "off";
String output3State = "off";
String output4State = "off";
String output5State = "off";
String output6State = "off";
String output7State = "off";

#define IR1 32
#define IR2 33
#define IR3 34
#define IR4 35
#define IR5 27
#define IR6 14
int P1,P2,P3,P4,P5,E;
char S1,S2,S3,S4,S5;

#define SERVO_PIN 18
Servo servoMotor;

#define LED1 2
#define LED2 4
#define LED3 5
#define LED4 15
#define LED5 19
#define BUZZ 23

#define FLAME 13
int F;

#define Button 25
int B = 0;

void setup() {
  Serial.begin(115200);
  pinMode(IR1,INPUT);
  pinMode(IR2,INPUT);
  pinMode(IR3,INPUT);
  pinMode(IR4,INPUT);
  pinMode(IR5,INPUT);
  pinMode(IR6,INPUT);
  pinMode(FLAME, INPUT);
  pinMode(Button, INPUT);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  pinMode(LED5,OUTPUT);
  pinMode(BUZZ,OUTPUT);
  servoMotor.attach(SERVO_PIN);
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
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("WiFi Name: ");
  display.println(ssid);
  display.setCursor(0,10);
  display.print("Password: ");
  display.println(password);
  display.setCursor(0,28);
  display.println("IP address: ");
  display.setCursor(0,40);
  display.println(WiFi.localIP());
  display.display();
}

void loop(){
  P1 = digitalRead(IR1);
  P2 = digitalRead(IR2);
  P3 = digitalRead(IR3);
  P4 = digitalRead(IR4);
  P5 = digitalRead(IR5);
  E = digitalRead(IR6);
  F = digitalRead(FLAME);
  B = digitalRead(Button);
  if(P1==1){
  digitalWrite(LED1,LOW);
  }
  else{
  digitalWrite(LED1,HIGH);  
  }
  if(P2==1){
  digitalWrite(LED2,LOW);
  }
  else{ 
  digitalWrite(LED2,HIGH);
  }
  if(P3==1){
  digitalWrite(LED3,LOW);
  }
  else{  
  digitalWrite(LED3,HIGH);
  }
  if(P4==1){
  digitalWrite(LED4,LOW);
  }
  else{  
  digitalWrite(LED4,HIGH);
  }
  if(P5==1){
  digitalWrite(LED5,LOW);
  }
  else{ 
  digitalWrite(LED5,HIGH);
  }
  if(E==1){
  servoMotor.write(0);
  }
  else{
  servoMotor.write(90);  
  } 
  if(F==1){
  digitalWrite(BUZZ,HIGH);
  }
  else{ 
  if(B==1){
  digitalWrite(BUZZ,HIGH);
  }
  else{ 
  digitalWrite(BUZZ,LOW);
  }
  }
  WiFiClient client = server.available();   
  if (client) {                             
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          
    String currentLine = "";                
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  
      currentTime = millis();
      if (client.available()) {             
        char c = client.read();            
        Serial.write(c);                   
        header += c;
        if (c == '\n') {                    
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            if (header.indexOf("GET /1/on") >= 0) {
              output1State = "on";
              S1 = 'P';
            } 
            else if (header.indexOf("GET /1/off") >= 0) {
              output1State = "off";
              S1 = 'E';
            } 
            else if (header.indexOf("GET /2/on") >= 0) {
              output2State = "on";
              S2 = 'P';
            } 
            else if (header.indexOf("GET /2/off") >= 0) {
              output2State = "off";
              S2 = 'E';
            }
            else if (header.indexOf("GET /3/on") >= 0) {
              output3State = "on";
              S3 = 'P';
            } 
            else if (header.indexOf("GET /3/off") >= 0) {
              output3State = "off";
              S3 = 'E';
            } 
            else if (header.indexOf("GET /4/on") >= 0) {
              output4State = "on";
              S4 = 'P';
            } 
            else if (header.indexOf("GET /4/off") >= 0) {
              output4State = "off";
              S4 = 'E';
            }
            else if (header.indexOf("GET /5/on") >= 0) {
              output5State = "on";
              S5 = 'P';
            } 
            else if (header.indexOf("GET /5/off") >= 0) {
              output5State = "off";
              S5 = 'E';
            } 
            else if (header.indexOf("GET /6/on") >= 0) {
              output6State = "on";
              digitalWrite(BUZZ,HIGH);
            } 
            else if (header.indexOf("GET /6/off") >= 0) {
              output6State = "off";
              digitalWrite(BUZZ,LOW);
            }            
            else if (header.indexOf("GET /7/on") >= 0) {
              output7State = "on";
              servoMotor.write(90);
            } 
            else if (header.indexOf("GET /7/off") >= 0) {
              output7State = "off";
              servoMotor.write(0);
            }

            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            //Table
            client.println("<style>body { text-align: center; font-family: \"Trebuchet MS\", Arial;}");
            client.println("table { border-collapse: collapse; width:35%; margin-left:auto; margin-right:auto; }");
            client.println("th { padding: 12px; background-color: #0043af; color: white; }");
            client.println("tr { border: 1px solid #ddd; padding: 12px; }");
            client.println("tr:hover { background-color: #bcbcbc; }");
            client.println("td { border: none; padding: 12px; }");
            client.println(".sensor { color:white; font-weight: bold; background-color: #bcbcbc; padding: 1px; }");
            //Buttons
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");

            client.println("</style></head><body><h1>SMART PARKING SYSTEM</h1>");
            client.println("<table><tr><th>SLOT NO:</th><th>UPDATE</th></tr>");
            client.println("<tr><td>SLOT 1</td><td><span class=\"sensor\">");
            client.println(S1); 
            client.println("<tr><td>SLOT 2</td><td><span class=\"sensor\">");
            client.println(S2);      
            client.println("<tr><td>SLOT 3</td><td><span class=\"sensor\">");
            client.println(S3);
            client.println("<tr><td>SLOT 4</td><td><span class=\"sensor\">");
            client.println(S4); 
            client.println("<tr><td>SLOT 5</td><td><span class=\"sensor\">");
            client.println(S5); 
            client.println("</table>");
            // Display current state, and ON/OFF buttons   
            client.println("<p>SLOT1 - State " + output1State + "</p>");
            // If the output26State is off, it displays the ON button       
            if (output1State=="off") {
              client.println("<p><a href=\"/1/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/1/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
            client.println("<p>SLOT2 - State " + output2State + "</p>");
            // If the output26State is off, it displays the ON button       
            if (output2State=="off") {
              client.println("<p><a href=\"/2/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/2/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("<p>SLOT3 - State " + output3State + "</p>");
            // If the output26State is off, it displays the ON button       
            if (output3State=="off") {
              client.println("<p><a href=\"/3/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/3/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
            client.println("<p>SLOT4 - State " + output4State + "</p>");
            // If the output26State is off, it displays the ON button       
            if (output4State=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("<p>SLOT5 - State " + output5State + "</p>");
            // If the output26State is off, it displays the ON button       
            if (output5State=="off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
            client.println("<p>Buzzer - State " + output6State + "</p>");
            // If the output26State is off, it displays the ON button       
            if (output6State=="off") {
              client.println("<p><a href=\"/6/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/6/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("<p>Servo - State " + output7State + "</p>");
            // If the output26State is off, it displays the ON button       
            if (output7State=="off") {
              client.println("<p><a href=\"/7/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/7/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            client.println("</body></html>");          
            client.println();
            break;
          } 
          else { 
            currentLine = "";
          }
        } 
        else if (c != '\r') { 
          currentLine += c; 
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
