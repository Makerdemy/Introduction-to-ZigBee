
#include <XBee.h>
#include <SoftwareSerial.h>
#include "DHT.h"
#define DHTPIN 2 
#define DHTTYPE DHT11

XBee xbee = XBee();
uint8_t payload[] = { 0 };
XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x41B89DE6);
ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
ZBTxStatusResponse txStatus = ZBTxStatusResponse();
DHT dht(DHTPIN, DHTTYPE);


uint8_t ssRX = 15;
uint8_t ssTX = 5;
SoftwareSerial nss(ssRX, ssTX);

void setup() {
  Serial.begin(115200);
  xbee.begin(Serial);
  nss.begin(9600);
  dht.begin();            
}

void loop() {
  int temperature = dht.readTemperature();
  payload[0] = temperature;
  xbee.send(zbTx);
  xbee.getResponse().isError();
  nss.print("error code:");
  nss.println(xbee.getResponse().getErrorCode());
}
