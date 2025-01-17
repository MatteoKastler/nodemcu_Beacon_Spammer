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
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, OUTPUT);
}

void loop() {
sendBeaconFrame("test");
}

void advancedSpam(char[] ssid){
  for(int i = 0; i < 32 - strlen(ssid); i ++)
    if(random(3) % 2 == 0){
    ssid += " ";
    }else{
      ssid += "\t";
    }
    sendBeaconFrame(ssid);
  
}

void sendBeaconFrame(char* ssid){

  int ssidLength = strlen(ssid);
  int beaconSize = 51 + ssidLength;
  int channel = random(1,12);
  
  //set random channel  
  wifi_set_channel(channel);

  uint8_t afterSSID[13] = {0x01, 0x08, 0x82, 0x84, 0x8b, 0x96, 0x24, 0x30, 0x48, 0x6c, //supported rate
                        0x03, 0x01, 0x04}; //channel?

  uint8_t beacon[128] = {
                       0x80, 0x00, //Frame Control 
                       0x00, 0x00, //dauer
               /*4*/   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, //Zieladresse 
               /*10*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, //Senderadresse
               /*16*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, //SSID aka name des netzwerks
               /*22*/  0xc0, 0x6c, //Seq-ctl
               /*24*/  0x83, 0x51, 0xf7, 0x8f, 0x0f, 0x00, 0x00, 0x00, //timestamp- millisekunden Access point ist aktiv
               /*32*/  0xFF, 0x00, //Beacon interval
               /*34*/  0x01, 0x04, //irgendwas für staukontrolle oder so 
               /* SSID */
               /*36*/  0x00 // ssid anfang
               };
               
  //length dings mit länge von ssid füllen             
  beacon[37] = ssidLength;

  //ssid reinschreiben
  for(int i = 0; i < ssidLength; i++){
    beacon[38 + i] = ssid[i];
  }
  
  //zeug nach ssid in das beacon
  for(int i = 0; i < 12; i++) {
      beacon[38 + ssidLength + i] = afterSSID[i];
  }
  
  //channel feld setzen
  beacon[50 + ssidLength] = channel;

  //Sender Mac- adresse randomisieren
  for(int i = 10;i <= 15;i++){
      beacon[i] = beacon[i + 6] = random(256);
  }
  
  //beacon,beacongröße,sequenznummern(true/false)
    for(int i = 0; i < 3; i++){
      wifi_send_pkt_freedom(beacon, beaconSize, 0);
      delay(1);
    }
}

void sendRandomBeacon(int length) {
  char ssid[length+1];
  randomString(length, ssid);
  sendBeaconFrame(ssid);
}

void randomString(int length, char* ssid) {
  String characters = "1234567890qwertyuiopasdfghjkklzxcvbnm QWERTYUIOPASDFGHJKLZXCVBNM_";
  for(int i = 0; i < length; i++) {
    ssid[i] = alfa[random(65)];
  }
}

void rickRoll() {
  sendBeaconFrame("01 Never gonna give you up,");
  sendBeaconFrame("02 never gonna let you down");
  sendBeaconFrame("03 Never gonna run around");
  sendBeaconFrame("04  and desert you");
  sendBeaconFrame("05 Never gonna make you cry,");
  sendBeaconFrame("06 never gonna say goodbye");
  sendBeaconFrame("07 Never gonna tell a lie");
  sendBeaconFrame("08  and hurt you");
}


