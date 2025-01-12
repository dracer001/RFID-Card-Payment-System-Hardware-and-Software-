#include <ESP8266WiFi.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LCD_I2C.h>

LCD_I2C lcd(0x27, 16, 2);

#define SS_PIN D3   // Define the SDA (SS) pin
#define RST_PIN D4  // Define the RST pin

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create an MFRC522 instance


const char* ssid = "Nokia 2.0";
const char* password = "bluehost";
const char* serverHost = "http://dracer.pythonanywhere.com";
const int serverPort = 80; // HTTP default port
//http://192.168.133.184/
void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();
  lcd.begin(); // If you are using more I2C devices using the Wire library use lcd.begin(false)
                 // this stop the library(LCD_I2C) from calling Wire.begin()
  lcd.backlight();
  lcd.print("Initialzing....");
  
  SPI.begin();       // Initialize SPI communication
  mfrc522.PCD_Init(); // Initialize the MFRC522 reader

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  lcd.print("  Initialization     ");
  lcd.setCursor(2, 1);
  lcd.print("Complete");
}

void loop() {

  lcd.setCursor(0, 0);
  lcd.print("Scan rfid...      ");
  lcd.setCursor(0, 1);
  lcd.print("                 ");

  // Look for new cards
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    lcd.setCursor(0, 0);
    lcd.print("Card detected    ");
    String cardUid = getCard();
    lcd.setCursor(0, 0);
    lcd.print(" please wait...  ");
    lcd.setCursor(0, 1);
    lcd.print("making payment  ");
    String response = makePayment(cardUid);
    lcd.setCursor(0, 0);
    lcd.print(response+"                ");
    lcd.setCursor(0, 1);
    lcd.print("                 ");
    delay(5000);
  }

  
}

String makePayment(String key){
  
  // Use WiFiClient class to create a TCP connection
  WiFiClient client;
  if (!client.connect(serverHost, serverPort)) {
    Serial.println("Connection failed");
    delay(5000);
    return "server failed";
  }

  // Send a GET request to the server
  client.print("GET /admin/debit/"+key+" HTTP/1.1\r\n");
  client.print("Host: ");
  client.println(serverHost);
  client.println("Connection: close");
  client.println();

  // Read and print the response from the server
  String line;
  while (client.connected()) {
    if (client.available()) {
      line = client.readStringUntil('\r');
      Serial.print(line);
    }
  }

  Serial.println();
  Serial.println("Closing connection");
  client.stop();

  return line;
}

String getCard(){

    String cardUid = "";
    Serial.print("Card UID: ");
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      cardUid += String(mfrc522.uid.uidByte[i], HEX);
      cardUid.toUpperCase();
    }
    Serial.println(cardUid);
    mfrc522.PICC_HaltA(); // Halt the card to stop communication
  return cardUid;
}
