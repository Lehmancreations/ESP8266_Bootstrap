/*
 * Use as a bootstrap to get the ESP8266 up and going and allow firmware upload from Arduino IDE or from web
 * 
 * Note: After flashing the code once you can remotely access your device by going to http://HOSTNAMEOFDEVICE.local/firmware 
 * obviously replace HOSTNAMEOFDEVICE with whatever you defined below. The user name and password are also defined below.
 */

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ArduinoOTA.h>
#include <WiFiManager.h>

/* ---------- DO NOT EDIT ANYTHING ABOVE THIS LINE ---------- */

//Only edit the settings in this section


/* Web Updater Settings */
// Host Name of Device
const char* host = "ESP8266 Bootstrap";

// Path to access firmware update page (Not Neccessary to change)
const char* update_path = "/firmware";

// Username to access the web update page
const char* update_username = "firmware";

// Password to access the web update page
const char* update_password = "upload";



/* ---------- DO NOT EDIT ANYTHING BELOW THIS LINE ---------- */

 ESP8266WebServer server(80);
ESP8266HTTPUpdateServer httpUpdater;

void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  digitalWrite (2, LOW);
}

void setup() 
{
  Serial.begin(115200);
    pinMode(2, OUTPUT);

//wifi   //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wifiManager;
    wifiManager.setAPCallback(configModeCallback);
   // reset saved settings
   // wifiManager.resetSettings();
    

    wifiManager.autoConnect("ESP8266_Bootstrap");
    //or use this for auto generated name ESP + ChipID
    //wifiManager.autoConnect();
 
  MDNS.begin(host);


  httpUpdater.setup(&server, update_path, update_username, update_password);

  
  server.on("/reset_wlan", []() {
   server.send(200, "text/plain", "Resetting WLAN and restarting..." );
    delay(1000);
    WiFiManager wifiManager;
    wifiManager.resetSettings();
    delay(1000);
    ESP.restart();
  });
  
  
  
  server.begin();

  MDNS.addService("http", "tcp", 80);



  /**************************
 * Set OTA up
 **************************/

  
ArduinoOTA.setPassword("firmware");  
  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if      (error == OTA_AUTH_ERROR   ) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR  ) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR    ) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
}



void loop() 
{
  ArduinoOTA.handle(); // for OTA
  server.handleClient();
      digitalWrite(2, HIGH);
      delay(500);
      digitalWrite(2, LOW);
      delay(500);
      
}


