#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f, 16, 2);
// variables
int LED = 13;
int BUTTON_GO = 8;
int BUTTON_STOP = 12;
boolean btn_go= false;
boolean btn_stop= false;
boolean prevent_btn_loop = false;
boolean prevent_do_loop = false;

int res[6] = {0, 0, 0, 0, 0, 0};
int i;
int temp = 0;

// ready to go
void setup() {
  // put your setup code here, to run once:
  lcd.begin();
  Serial.begin(9600);// baudrate=9600
  pinMode(BUTTON_STOP, INPUT);
  pinMode(BUTTON_GO, INPUT);
  pinMode(LED, OUTPUT);
  randomSeed(analogRead(0));
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!btn_go && !prevent_btn_loop){
    if(digitalRead(BUTTON_GO)==1){
      btn_go= true;
      prevent_btn_loop = true;
      prevent_do_loop = true;
    }
  }
  if(!btn_stop && !prevent_btn_loop)
  {
    if(digitalRead(BUTTON_STOP)==1){
      btn_stop= true;
      prevent_btn_loop = true;
      prevent_do_loop = true;   
    }
  }
  delay(100);// read button in 0.1s cycle
  
  if(btn_go && prevent_do_loop){
    btn_go = false;
    lcd.clear();
    
    // get 6 nums
    for (i = 0; i < 6; i++)
    {
        temp = random(1,46);
        res[i] = temp;
        for (int j = 0; j < i; j++)
        {
            if (res[j] == temp) // check duplication
            {
                i--;
                break;
            }
        }
    }
    // print 6 nums
    lcd.setCursor(0,0);// cols, rows
    lcd.print("Your");
    lcd.setCursor(7,0);
    lcd.print(res[0]);
    lcd.print(",");
    lcd.print(res[1]);
    lcd.print(",");
    lcd.print(res[2]);
    lcd.print(",");
    lcd.setCursor(1,1);
    lcd.print("NUMs");
    lcd.setCursor(8,1);
    lcd.print(res[3]);
    lcd.print(",");
    lcd.print(res[4]);
    lcd.print(",");
    lcd.print(res[5]);
    prevent_do_loop = false;
    prevent_btn_loop = false;
    Serial.flush();
  }
  else if(btn_stop && prevent_do_loop){
    btn_stop = false;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("PUSH GREEN BTN");
    lcd.setCursor(0,1);
    
    prevent_do_loop = false;
    prevent_btn_loop = false;
    Serial.flush();
  }
//  else {
//    lcd.clear();
//    lcd.setCursor(0,0);
//    lcd.print("READY");
//    Serial.flush();
//  }
  delay(1000);// 1초마다 루프
}
