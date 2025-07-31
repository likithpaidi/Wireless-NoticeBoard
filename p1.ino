#include <Wire.h>
#include <LiquidCrystal_I2C_Hangul.h>
LiquidCrystal_I2C_Hangul lcd(0x27, 16, 2);

void setup() {
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Waiting for Data");

  // Initialize Serial communication
  Serial.begin(9600); // Baud rate should match HC-05 default (typically 9600)
}

void loop() {
  // Check if data is available from HC-05
  if (Serial.available()) {
    lcd.clear(); // Clear the display

    // Read incoming data
    String data = "";
    while (Serial.available()) {
      char c = Serial.read();
      data += c; // Append characters to the string
      delay(5);  // Small delay to ensure all data is read
    }

    // Display the data on the LCD
    lcd.clear();
    lcd.setCursor(0, 0); // Start from the first row
    lcd.print("Received:");
    lcd.setCursor(0, 1); // Move to the second row
    lcd.print(data);
    //    while (true)
    //    {
    scrollText(data);
    //}
  }

}

// Function to scroll text on the LCD
void scrollText(String message) {
  int messageLength = message.length();
  int displayWidth = 16; // Width of the LCD
  int totalScroll = messageLength - displayWidth;

  // Display the first part of the message
//    lcd.setCursor(0, 0);
//    lcd.print(message.substring(0, displayWidth));
//    delay(1000); // Wait before starting the scroll

  // Scroll through the remaining text if it's longer than the display width
  if (totalScroll > 0) {
    for (int i = 0; i <= totalScroll; i++) {
      lcd.setCursor(0, 1);
      lcd.print(message.substring(i, i + displayWidth));
      delay(300); // Adjust delay for scrolling speed
    }
  }

  // After scrolling, display the message statically if needed
    lcd.setCursor(0, 1);
    lcd.print(message.substring(max(0, messageLength - displayWidth)));
}
