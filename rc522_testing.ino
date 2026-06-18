#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN   10
#define RST_PIN  9
#define SCK_PIN  12
#define MISO_PIN 13
#define MOSI_PIN 11

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);
  delay(1000);

  SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN, SS_PIN);
  rfid.PCD_Init();

  byte v = rfid.PCD_ReadRegister(MFRC522::VersionReg);
  Serial.printf("Version: 0x%02X\n", v);
  rfid.PCD_DumpVersionToSerial();
  Serial.println("Scan a tag...");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  Serial.print("UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.printf("%02X ", rfid.uid.uidByte[i]);
  }
  Serial.println();

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  delay(500);
}
