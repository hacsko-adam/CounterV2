#include <Arduino.h>
#include <ESP8266WiFi.h> 
#include "Display.hpp"
#include "Button.hpp"
#include <EEPROM.h>
#include <ESP8266WiFi.h> 
#include <ESP8266WebServer.h>

Button btn = Button(D1);
Display display = Display();

const char* ssid = "TaDevRemote";
ESP8266WebServer server(80);

int currentNo = 0;
int displayedNo = 0;
long last_save_mills = 0;
int savedNo = 0;

void handleRoot() {
  String body = "<!DOCTYPE html>"\
				"<html>"\
				"<head>"\
					"<title>TaDev remote</title>"\
          "<meta charset='utf-8' />"\
					"<style>body{background:#34495e;color:#fff;text-align:center;font-family:Helvetica,Arial,sans-serif;font-size:10pt}h1{font-size:3em}form{width:500px;margin:0 auto;background:#fff;border-radius:10px;margin-bottom:20px}.floating-placeholder,input{font-family:Helvetica,Arial,sans-serif;font-size:20pt;line-height:2.6em;height:2.6em;margin:0;padding:0;width:100%}.floating-placeholder input:focus+label{color:#16abf0}.floating-placeholder input[value]+label{color:red}.floating-placeholder{position:relative}.floating-placeholder input{font-size:20pt;border:none;outline:0;position:absolute;top:0;left:0;display:block;background:0 0;z-index:2;border-bottom:1px solid #ccc;text-indent:20px}.floating-placeholder:last-child input{border-bottom:none}.floating-placeholder-float input{line-height:3.4em}</style>"\
				"</head>"\
				"<body>"\
				"<h1>Ta-Dev Counter</h1>"\
				"<h2>Mennyit mutasson a számláló?</h2>"\
				"<form method='get' action='set'>"\
					"<div class='floating-placeholder'>"\
					  "<input name='number' type='number' placeholder='";
            body += currentNo;
            body += "'/>"\
					"</div>"\
					"<div class='floating-placeholder'>"\
					  "<input id='kuldes' name='address' type='submit' value='Küldjed!' />"\
					"</div>"\
					"</form>"\
					"<span><u>by Adam Hacsko</u></span> "\
        "</body>"\
      "</html>";

  server.send(200, "text/html", body);
}
void set() {
    if(server.arg("number"))
    {
      int tmpnumber = server.arg("number").toInt();
      Serial.println(tmpnumber);
      if(tmpnumber >= 0 && tmpnumber <= 999){
        currentNo = tmpnumber;
      }
    }
    server.sendHeader("Location", String("/"), true);
    server.send ( 302, "text/plain", "");
}

void save_to_eeprom(int number){
  EEPROM.write(0,highByte(number));
  EEPROM.write(1,lowByte(number));
  EEPROM.commit();
  Serial.write(number);
  Serial.println(" saved to eeprom");
}

int read_from_eeprom(){
  byte high = EEPROM.read(0);
  byte low = EEPROM.read(1);
  int number=word(high,low);
  Serial.println(number);
  Serial.println(" found in eeprom");
  return number;
}

void setup() {
  EEPROM.begin(512);
  Serial.begin(9600);
  Serial.write("Szia! :)");
  
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, "",1, 1 );

  server.on("/", handleRoot);
  server.on("/set", set);
  server.begin();

  currentNo = read_from_eeprom();  

  if(currentNo > 999 || currentNo < 0){
    currentNo = 0;
  }
}

void loop() {
  server.handleClient();
  int input = btn.checkButton();
  if (input == 1)
  {
    currentNo++;
      Serial.write("Sima click\n");
  }

  if (input == 2)
  {
    Serial.write("hold \n");
    currentNo--;
  }

  if (input == 3)
  { 
    Serial.write("long hold\n");
    display.reset();
    currentNo = 0;
  }

  if(currentNo > 999) 
  {
     currentNo = 0;
     display.reset();
  }
  
  if(currentNo < 0) 
  {
    currentNo = 0;
    display.reset();
  }

  if(displayedNo != currentNo){
    display.reset();
    if(currentNo > 99){
      display.write(3, ((currentNo%1000)/100));
    }
    if(currentNo > 9){
      display.write(2,((currentNo%100)/10));
    }
    display.write(1, currentNo % 10);
    display.write(1, currentNo);
    displayedNo = currentNo;
  }
  if(millis() - last_save_mills > 600000 && savedNo != currentNo){
      save_to_eeprom(currentNo);
      last_save_mills = millis();
      savedNo = currentNo;
    }
}
