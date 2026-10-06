#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9
#define SEND_SIGNAL 4

MFRC522 rfid(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Your exact RFID UID
byte authorizedUID[] = {0x24, 0x16, 0x0C, 0x07};


bool checkUID() {

  if (rfid.uid.size != 4) {
    return false;
  }

  for (byte i = 0; i < 4; i++) {
    if (rfid.uid.uidByte[i] != authorizedUID[i]) {
      return false;
    }
  }

  return true;
}


void setup() {

  pinMode(SEND_SIGNAL, OUTPUT);
  digitalWrite(SEND_SIGNAL, LOW);

  SPI.begin();
  rfid.PCD_Init();

  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("IntelliTraffic");
  lcd.setCursor(0, 1);
  lcd.print("System Ready");
}


void loop() {

  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }


  if (checkUID()) {

    // Authorized card
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Granted");
    lcd.setCursor(0, 1);
    lcd.print("Emergency Vehicle");

    // Send emergency signal to Arduino 1
    digitalWrite(SEND_SIGNAL, HIGH);

    // Keep signal ON for 15 seconds
    delay(15000);

    // Stop emergency signal
    digitalWrite(SEND_SIGNAL, LOW);

    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("IntelliTraffic");
    lcd.setCursor(0, 1);
    lcd.print("System Ready");
  }

  else {

    // Unauthorized card
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Denied");
    lcd.setCursor(0, 1);
    lcd.print("Invalid RFID");

    delay(2000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("IntelliTraffic");
    lcd.setCursor(0, 1);
    lcd.print("System Ready");
  }


  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  delay(500);
}
