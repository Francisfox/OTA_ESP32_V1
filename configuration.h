#ifndef _configuration_
#define _configuration_

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>
#include <esp_task_wdt.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "Web.h"
#include "botao.h"

// Instatiate the AsyncWebServer object on port 80
AsyncWebServer webServer(80);
WebServer server(80);

const char* host = "esp32";
const char* ssid = "DESKTOP";
const char* password = "12345678";

void startRede(){  
    // Connect to WiFi network
    WiFi.begin(ssid, password);
  
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
    }
  
    /*use mdns for host name resolution*/
    if (!MDNS.begin(host)) { //http://esp32.local
      while (1) {
        delay(1000);
      }
    }
    /*return index page which is stored in serverIndex */
    server.on("/", HTTP_GET, []() {
      server.sendHeader("Connection", "close");
      server.send(200, "text/html", loginIndex);
    });
    server.on("/serverIndex", HTTP_GET, []() {
      server.sendHeader("Connection", "close");
      server.send(200, "text/html", serverIndex);
    });
    /*handling uploading firmware file */
    server.on("/update", HTTP_POST, []() {
      server.sendHeader("Connection", "close");
      server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
      ESP.restart();
    }, []() {
      HTTPUpload& upload = server.upload();
      if (upload.status == UPLOAD_FILE_START) {
        if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
          Update.printError(Serial);
        }
      } else if (upload.status == UPLOAD_FILE_WRITE) {
        /* flashing firmware to ESP*/
        if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
          Update.printError(Serial);
        }
      } else if (upload.status == UPLOAD_FILE_END) {
        if (Update.end(true)) { //true to set the size to the current progress
        } else {
          Update.printError(Serial);
        }
      }
    });
  server.begin();
}

#endif