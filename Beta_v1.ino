#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);
LiquidCrystal lcd(9, 8, 7, 6, 5, 4);

int keypad_pin = A0;
int keypad_value = 0;

char btn_push;

byte mainMenuPage = 1;
byte mainMenuPageOld = 1;
byte mainMenuTotal = 4;

void setup()
{
  mySerial.begin(9600);
  lcd.begin(16, 2); //Initialize a 2x16 type LCD
  MainMenuDisplay();
  delay(1000);
}
void loop()
{
  btn_push = ReadKeypad();

  MainMenuBtn();

  if (btn_push == 'E') //enter selected menu
  {
    WaitBtnRelease();
    switch (mainMenuPage)
    {
      case 1:
        MenuA();
        break;
      case 2:
        MenuB();
        break;
      case 3:
        MenuC();
        break;
      case 4:
        MenuD();
        break;
    }

    MainMenuDisplay();
    WaitBtnRelease();
  }
  delay(10);

}//--------------- End of loop() loop ---------------------

void MenuA()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("JB Hills R-52");
  lcd.setCursor(0, 1);
  lcd.print("E: ON      X:OFF");

  while (ReadKeypad() != 'U')
  {
    if (ReadKeypad() == 'E') {
      lcd.setCursor(0, 1);
      lcd.print("----VALVE ON----");
      SendMessage();
      mySerial.println("JB Hills R-52 ON");// The SMS text you want to send
      delay(100);
      mySerial.println((char)26);// ASCII code of CTRL+Z
      delay(1000);}

    if (ReadKeypad() == 'X') {
      lcd.setCursor(0, 1);
      lcd.print("---VALVE OFF----");
      SendMessage();
      mySerial.println("JB Hills R-52 OFF");// The SMS text you want to send
      delay(100);
      mySerial.println((char)26);// ASCII code of CTRL+Z
      delay(1000);}
  }
}
void MenuB()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("JB Hills R-53");
  lcd.setCursor(0, 1);
  lcd.print("E: ON      X:OFF");

  while (ReadKeypad() != 'U')
  {
    if (ReadKeypad() == 'E') {
      lcd.setCursor(0, 1);
      lcd.print("----VALVE ON----");
      SendMessage();
      mySerial.println("JB Hills R-53 ON");// The SMS text you want to send
      delay(100);
      mySerial.println((char)26);// ASCII code of CTRL+Z
      delay(1000);}

    if (ReadKeypad() == 'X') {
      lcd.setCursor(0, 1);
      lcd.print("---VALVE OFF----");
      SendMessage();
      mySerial.println("JB Hills R-53 OFF");// The SMS text you want to send
      delay(100);
      mySerial.println((char)26);// ASCII code of CTRL+Z
      delay(1000);}
  }
}
void MenuC()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("JB Hills R-54");
  lcd.setCursor(0, 1);
  lcd.print("E: ON      X:OFF");

  while (ReadKeypad() != 'U')
  {
    if (ReadKeypad() == 'E') {
      lcd.setCursor(0, 1);
      lcd.print("----VALVE ON----");
      SendMessage();
      mySerial.println("JB Hills R-54 ON");// The SMS text you want to send
      delay(100);
      mySerial.println((char)26);// ASCII code of CTRL+Z
      delay(1000);}

    if (ReadKeypad() == 'X') {
      lcd.setCursor(0, 1);
      lcd.print("---VALVE OFF----");
      SendMessage();
      mySerial.println("JB Hills R-54 OFF");// The SMS text you want to send
      delay(100);
      mySerial.println((char)26);// ASCII code of CTRL+Z
      delay(1000);}
  }
}
void MenuD()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("JB Hills R-55");
  lcd.setCursor(0, 1);
  lcd.print("E: ON      X:OFF");

  while (ReadKeypad() != 'U')
  {
    if (ReadKeypad() == 'E') {
      lcd.setCursor(0, 1);
      lcd.print("----VALVE ON----");
      SendMessage();
      mySerial.println("JB Hills R-55 ON");// The SMS text you want to send
      delay(100);
      mySerial.println((char)26);// ASCII code of CTRL+Z
      delay(1000);}

    if (ReadKeypad() == 'X') {
      lcd.setCursor(0, 1);
      lcd.print("---VALVE OFF----");
      SendMessage();
      mySerial.println("JB Hills R-55 OFF");// The SMS text you want to send
      delay(100);
      mySerial.println((char)26);// ASCII code of CTRL+Z
      delay(1000);}
  }
}

void MainMenuDisplay()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  switch (mainMenuPage)
  {
    case 1:
      lcd.print("1.JB Hills R-52");
      break;
    case 2:
      lcd.print("2.JB Hills R-53");
      break;
    case 3:
      lcd.print("3.JB Hills R-54");
      break;
    case 4:
      lcd.print("4.JB Hills R-55");
      break;
  }
}

void MainMenuBtn()
{
  WaitBtnRelease();
  if (btn_push == 'U')
  {
    mainMenuPage++;
    if (mainMenuPage > mainMenuTotal)
      mainMenuPage = 1;
  }
  else if (btn_push == 'D')
  {
    mainMenuPage--;
    if (mainMenuPage == 0)
      mainMenuPage = mainMenuTotal;
  }

  if (mainMenuPage != mainMenuPageOld) //only update display when page change
  {
    MainMenuDisplay();
    mainMenuPageOld = mainMenuPage;
  }
}

char ReadKeypad()
{
  /* Keypad button analog Value
    no button pressed 1023
    select  741
    left    503
    down    326
    up      142
    right   0
  */
  keypad_value = analogRead(keypad_pin);

  if (keypad_value < 310)
    return 'U';
  else if (keypad_value < 360)
    return 'D';
  else if (keypad_value < 425)
    return 'X';
  else if (keypad_value < 520)
    return 'E';
  else
    return 'N';

}

void WaitBtnRelease()
{
  while ( analogRead(keypad_pin) < 520) {}
}

void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919963931414\"\r"); // Replace x with mobile number
  delay(1000);
}
