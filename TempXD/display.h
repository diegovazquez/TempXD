#include <LiquidCrystal_I2C.h>

// Construct an LCD object and pass it the 
// I2C address, width (in characters) and
// height (in characters). Depending on the
// Actual device, the IC2 address may change.
LiquidCrystal_I2C lcd(DISPLAY_IC2_ADDRESS, 20, 4);

// Setup Display
void displayStart() {
  // The begin call takes the width and height. This
  // Should match the number provided to the constructor.
  lcd.begin(20,4);
  lcd.init();
  //lcd.backlight(); // Turn on the backlight.
  lcd.noBacklight(); // turn off backlight

  lcd.setCursor(0, 0);
  lcd.print("Liquor");
  lcd.setCursor(0, 1);      
  lcd.print("Mash");
  lcd.setCursor(0, 2);      
  lcd.print("Boil");  
}

// Show Temps in display
void displayTemperatures() {
    lcd.setCursor(13, 0);
    lcd.print(String(tempLiquor));
    lcd.setCursor(13, 1);
    lcd.print(String(tempMash));
    lcd.setCursor(13, 2);
    lcd.print(String(tempBoil));     
    // Update indicator
    lcd.setCursor(19, 0);
    lcd.print("U");   
    lcd.setCursor(19, 1);
    lcd.print("U");   
    lcd.setCursor(19, 2);
    lcd.print("U");      
    delay(200);
     // Update indicator
    lcd.setCursor(19, 0);
    lcd.print(" ");   
    lcd.setCursor(19, 1);
    lcd.print(" ");   
    lcd.setCursor(19, 2);
    lcd.print(" ");           
}
