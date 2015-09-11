//"RBL_nRF8001.h/spi.h/boards.h" is needed in every new project
#include <SPI.h>
#include <EEPROM.h>
#include <boards.h>
#include <RBL_nRF8001.h>

int led = 2;
int engine = 5;

void setup() {
    // Set your BLE advertising name here, max. length 10
    ble_set_name("Remote Car");

    pinMode(led, OUTPUT);
    digitalWrite(led, LOW);
    
    pinMode(engine, OUTPUT);
    analogWrite(engine, 0);
    // Init. and start BLE library.
    ble_begin();
    Serial.begin(9600);
}

void loop() {
          
  if ( ble_available() )
  {
    while ( ble_available() )
    {
      byte cmd = ble_read();
      Serial.write(cmd);
      switch(cmd){
        case 't': 
          digitalWrite(led, HIGH);
        break;
        case 'o': 
          digitalWrite(led, LOW);
        break;
        case 'a':
          analogWrite(engine, 255);
        break;
        case 'b':
          analogWrite(engine, 0);
        break;
      }
    }
  }
  
  ble_do_events();
  
}

