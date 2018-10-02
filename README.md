## ESP8266 Bootstrap
This software is what I load to fresh ESP8266 chips to make sure that it can get online and works. 
When you first boot this it will create an access point you can join on your phone or your computer.
The LED on the ESP will be on solid. Once you join a network it will blink.

To reset the saved settings visit the ip address of the ESP followed by /reset_wlan. for instance 192.168.1.100/reset_wlan