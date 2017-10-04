#include <RFID.h>

/* 
 PINOUT:
 RC522 MODULE    Uno/Nano    
 SDA             D10
 SCK             D13
 MOSI            D11
 MISO            D12
 IRQ             N/A
 GND             GND
 RST             D9
 3.3V            3.3V
 
 */

#include <SPI.h>
/* Vengono definiti PIN del RFID reader*/
#define SDA_DIO 10  // 53 per Arduino Mega
#define RESET_DIO 9
#define delayRead 1000 // Time of delay 

/* Viene creata una istanza della RFID libreria */
RFID RC522(SDA_DIO, RESET_DIO); 
#define LEDG 8
#define LEDR 7


void setup()
{ 
  Serial.begin(9600);
  /* Abilita SPI*/
  SPI.begin(); 
  /* Viene inizilizzato RFID reader */
  RC522.init();
  Serial.println("Setup");

  pinMode(LEDG, OUTPUT); 
  pinMode(LEDR, OUTPUT);
  

}

void loop()
{
  /* Temporary loop counter */
  byte i;

  // Se viene letta una tessera
  if (RC522.isCard())
  {
    // Viene letto il suo codice 
    RC522.readCardSerial();
    String codiceLetto ="";
    Serial.println("Codice delle tessera letto:");

    // Viene caricato il codice della tessera, all'interno di una Stringa
    for(i = 0; i <= 4; i++)
    {
      codiceLetto+= String (RC522.serNum[i],HEX);
      codiceLetto.toUpperCase();
    }

    if(codiceLetto!="524894109E")
    {
      Serial.println("NOn autorizzato");
       digitalWrite(LEDR, HIGH);  // accende il LED  
  delay(10000);              // aspetta un secondo  
  digitalWrite(LEDR, LOW); 
    }
    else
    {
      Serial.println("Autorizzato");
       digitalWrite(LEDG, HIGH);  // accende il LED  
  delay(10000);              // aspetta un secondo  
  digitalWrite(LEDG, LOW); 
    }

    Serial.println(codiceLetto);

  }
}


