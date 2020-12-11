
#include <XBee.h>
#include <LCD_I2C.h>
#include <SoftwareSerial.h>

XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
ZBRxResponse rx = ZBRxResponse();
ModemStatusResponse msr = ModemStatusResponse();

LCD_I2C lcd(0x3F); 

uint8_t ssRX = 15;
uint8_t ssTX = 2;
SoftwareSerial nss(ssRX, ssTX);

void setup() {
  Serial.begin(115200);
  xbee.begin(Serial);
  nss.begin(9600);
  lcd.begin();              
}


void loop() {
    
   xbee.readPacket();
    
    if (xbee.getResponse().isAvailable()) {
      // got something
           
      if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
        // got a zb rx packet
        
        // now fill our zb rx class
        xbee.getResponse().getZBRxResponse(rx);
      
        nss.println("Got an rx packet!");
            
        if (rx.getOption() == ZB_PACKET_ACKNOWLEDGED) {
            // the sender got an ACK
            nss.println("packet acknowledged");
        } else {
          nss.println("packet not acknowledged");
        }
        
        nss.print("checksum is ");
        nss.println(rx.getChecksum(), HEX);

        nss.print("packet length is ");
        nss.println(rx.getPacketLength(), DEC);
        String payload;
         for (int i = 0; i < rx.getDataLength(); i++) {
          nss.println(payload = rx.getData()[i]);
        }
        lcd.clear();
        lcd.backlight();
        lcd.print(payload);
        delay(2000);
        
      }
    } else if (xbee.getResponse().isError()) {
      nss.print("error code:");
      nss.println(xbee.getResponse().getErrorCode());
    }
}
