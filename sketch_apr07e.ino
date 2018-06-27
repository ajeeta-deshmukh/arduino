#include <SoftwareSerial.h> //include the software serial library

SoftwareSerial esp8266(3,4); //set the software serial pins RX pin = 3, TX pin = 4 
//definition of variables
#define DEBUG true //show messages between ESP8266 and Arduino in serial port, when set to true
#define SSID "Keval" //replace x with your wifi network name
#define PASS "qwerty123" //replace x with your wifi network passwordj


String sendAT(String command, const int timeout, boolean debug)
{
  String response = "";
  esp8266.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (esp8266.available())
    {
      char c = esp8266.read();
      response += c;
    }
  }
  if (debug)
  {
    Serial.println(response);
  }
  return response;
}

void setup()
{

  Serial.begin(9600);// begin the serial communication with baud of 9600
  esp8266.begin(9600);// begin the software serial communication with baud rate 9600
  
  //sendAT("AT+RST\r\n", 2000, DEBUG); // call sendAT function to send reset AT command
  sendAT("AT\r\n", 1000, DEBUG);
  sendAT("AT+CWMODE=1\r\n", 1000, DEBUG); //call sendAT function to set ESP8266 to station mode
  sendAT("AT+CWJAP=\""SSID"\",\""PASS"\"\r\n", 2000, DEBUG); //AT command to connect wit the wifi network

  while(!esp8266.find("OK")) { //wait for connection
  } 
  sendAT("AT+CIFSR\r\n", 1000, DEBUG); //AT command to print IP address on serial monitor
  sendAT("AT+CIPMUX=0\r\n", 1000, DEBUG); //AT command to set ESP8266 to multiple connections

  
}

void loop(){
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(A0);
 // Serial.println(sensorValue);
  float millivolts= (sensorValue/1024.0) * 5000;
  float celsius= millivolts/10;
  Serial.print(celsius);
  delay(10);
  

  String Temp = String(celsius); //convert integer to string data type
  updateTS(Temp); //call the function to update ThingSpeak channel
  delay(3000);
}



void updateTS(String T){
  Serial.println("");
  sendAT("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n", 1000, DEBUG);    
  delay(2000);
  String cmdlen;
  String cmd="GET /update?key=Q701YY034Q1L4I0W&field1="+T+"\r\n"; // update the temprature and humidity values on thingspeak url,replace xxxxxxx with your write api key
   cmdlen = cmd.length();
  sendAT("AT+CIPSEND="+cmdlen+"\r\n", 2000, DEBUG);
   esp8266.print(cmd);
   Serial.println("");
   sendAT("AT+CIPCLOSE\r\n", 2000, DEBUG);
   Serial.println("");
   delay(15000);
   }
