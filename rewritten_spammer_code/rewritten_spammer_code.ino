/* Author:Matteo Kastler
 *  rewritten beacon frame spammer code 
 *  for nodemcu V2 ESP8266 
 *  in work: different modes(adcanced spam, random SSID spa),lcd display
 */
#include <ESP8266WiFi.h>


void setup() {
  delay(500);
  wifi_set_opmode(STATION_MODE);
  //monitormode for whatever reason
  wifi_promiscuous_enable(1); 
}

void loop() {
  //z.B. spambeacon("SSID");
  

}

void advancedSpam(char[] ssid, int number){
  
  
}

