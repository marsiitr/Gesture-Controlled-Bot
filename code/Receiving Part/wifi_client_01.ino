/*  Connects to the home WiFi network
 *  Asks some network parameters
 *  Sends and receives message from the server in every 2 seconds
 *  Communicates: wifi_server_01.ino
 */ 
#include <SPI.h>
#include <ESP8266WiFi.h>
#define M1_PIN1 16
#define M1_PIN2 5
#define M1_PWM 12

#define M2_PIN1 4 
#define M2_PIN2 0
#define M2_PWM 14

byte ledPin = 2;
char ssid[] = "MaRS_private";           // SSID of your home WiFi
char pass[] = "marsiitr1";            // password of your home WiFi

unsigned long askTimer = 0;

IPAddress server(192,168,0,80);       // the fix IP address of the server
WiFiClient client;

void setup() {
  Serial.begin(115200);               // only for debug
  WiFi.begin(ssid, pass);             // connects to the WiFi router
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
/*  Serial.println("Connected to wifi");
  Serial.print("Status: "); Serial.println(WiFi.status());    // Network parameters
  Serial.print("IP: ");     Serial.println(WiFi.localIP());
  Serial.print("Subnet: "); Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: "); Serial.println(WiFi.gatewayIP());
  Serial.print("SSID: "); Serial.println(WiFi.SSID());
  Serial.print("Signal: "); Serial.println(WiFi.RSSI());*/
pinMode(M1_PIN1, OUTPUT);
pinMode(M1_PIN2, OUTPUT);
pinMode(M1_PWM, OUTPUT);

pinMode(M2_PIN1, OUTPUT);
pinMode(M2_PIN2, OUTPUT);
pinMode(M2_PWM, OUTPUT);
pinMode(ledPin, OUTPUT);
}

void loop () {
  client.connect(server, 80);   // Connection to the server
  digitalWrite(ledPin, LOW);    // to show the communication only (inverted logic)
  Serial.println(".");
  client.println("Hello server! Are you sleeping?\r");  // sends the message to the server
  String answer = client.readStringUntil('\r');   // receives the answer from the sever
  Serial.println("from server: " + answer);
  int a= answer[1];
  int x= int(map(a,0,9,0,255));
  Serial.println(x);
  client.flush();
  digitalWrite(ledPin, HIGH);
  if(answer[0]=='b'){
//  void forward(){
  digitalWrite(M1_PIN1, HIGH);
  digitalWrite(M1_PIN2, LOW);
  analogWrite(M1_PWM, 600);

  digitalWrite(M2_PIN1, HIGH);
  digitalWrite(M2_PIN2, LOW);
  analogWrite(M2_PWM,600);
  
  //delay(100);
}
else
if(answer[0]=='f'){
  //void backward(){
  digitalWrite(M1_PIN1, LOW);
  digitalWrite(M1_PIN2, HIGH);
  analogWrite(M1_PWM, 600);
  digitalWrite(M2_PIN1, LOW);
  digitalWrite(M2_PIN2, HIGH);
  analogWrite(M2_PWM, 600);
  //delay(100);
  }
  else
  if(answer[0]=='r'){
  //void backward(){
  digitalWrite(M1_PIN1, HIGH);
  digitalWrite(M1_PIN2, LOW);
  analogWrite(M1_PWM, 600);
  digitalWrite(M2_PIN1, LOW);
  digitalWrite(M2_PIN2, LOW);
  analogWrite(M2_PWM, 600);
  //delay(100);
  }
  else
  if(answer[0]=='l'){
  //void backward(){
  digitalWrite(M1_PIN1, LOW);
  digitalWrite(M1_PIN2, LOW);
  analogWrite(M1_PWM, 600);
  digitalWrite(M2_PIN1, HIGH);
  digitalWrite(M2_PIN2, LOW);
  analogWrite(M2_PWM, 600);
  //delay(100);
  }
  delay(100);                  // client will trigger the communication after two seconds
}
