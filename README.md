## ESP8266 Bootstrap
This software is what I load to fresh ESP8266 chips to make sure that it can get online and works.
It is also the starting point for our new software that runs on ESP8266.
 
When you first boot this it will create an access point you can join on your phone or your computer.
You can use this access point to set settings including the MQTT topic and server to send commands.

To reset the saved settings visit the ip address of the ESP followed by /reset_wlan. for instance 192.168.1.100/reset_wlan