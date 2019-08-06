/*
 * WebSocketServer.ino
 *
 *  Created on: 22.05.2015
 *
 */

#include <Arduino.h>
#include <U8g2lib.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsServer.h>
#include <Hash.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

ESP8266WiFiMulti WiFiMulti;
WebSocketsServer webSocket = WebSocketsServer(81);
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ 16, /* clock=*/ 5, /* data=*/ 4); // for the oled screen

#define USE_SERIAL Serial

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) 
{
    switch(type) 
    {
        case WStype_DISCONNECTED:
        {
            USE_SERIAL.printf("[%u] Disconnected!\n", num);
        }
        break;
        case WStype_CONNECTED:
        {
          IPAddress ip = webSocket.remoteIP(num);
          USE_SERIAL.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
          // send message to client
          webSocket.sendTXT(num, "Connected");
        }
        break;
        case WStype_TEXT:
        {
          USE_SERIAL.printf("[%u] get Text: %s\n", num, payload);
          String inputString;
          inputString = (char*)payload;
          USE_SERIAL.print(inputString);
          if(inputString.equals("on"))
          {
            digitalWrite(5, HIGH); 
            USE_SERIAL.printf("LED on");
            webSocket.sendTXT(num, "Turn LED On\n");
          }
          else if(inputString.equals("off"))
          {
            digitalWrite(5, LOW);
            USE_SERIAL.printf("LED off\n"); 
            webSocket.sendTXT(num, "Turn LED Off");
          }
          else
          {
            USE_SERIAL.printf("Try again:\n");
            USE_SERIAL.print(inputString);
            
          }
          // send message to client
          // webSocket.sendTXT(num, "message here");
        }
        break;
        case WStype_BIN:
        {
          USE_SERIAL.printf("[%u] get binary length: %u\n", num, length);
          hexdump(payload, length);
          // send message to client
          // webSocket.sendBIN(num, payload, length);
        }
        break;
    }
}

void setup() 
{
    USE_SERIAL.begin(115200);
    //USE_SERIAL.setDebugOutput(true);
    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) 
    {
        USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    USE_SERIAL.printf(".");("Serial Coms begin");
    USE_SERIAL.printf(".");("OLED init");
    u8g2.begin();
    u8g2.clearBuffer();
    USE_SERIAL.printf(".");("Connecting to AP");

    WiFiMulti.addAP("LinksysWifi-2.4", "QUDXEBTQ");

    while(WiFiMulti.run() != WL_CONNECTED) 
    {
        delay(500);
        USE_SERIAL.printf(".");
    }
    USE_SERIAL.printf("Connected");
    USE_SERIAL.printf("Starting Webserver");
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
    USE_SERIAL.printf("Completed");
    pinMode(5, OUTPUT); 
    USE_SERIAL.printf("Initialisation Complete");
}

void loop() 
{
    webSocket.loop();
    
}
