#include<math.h>
#include <Keypad.h>
#include <LiquidCrystal.h>


int val[5];
int i=0,k=0,l=0,j,t=0,tt=0,m;
unsigned long time1=0;
int x,freq;
const byte ROWS = 5; 
const byte COLS = 4;

 
char hexaKeys[ROWS][COLS] = 
{
  {'F','f','#','*'},
  {'1','2','3','^'},
  {'4','5','6','v'},
  {'7','8','9','e'},
  {'<','0','>','E'}
};

byte rowPins[ROWS] = {0,13,2,3,4}; 
byte colPins[COLS] = {8,7, 6, 5}; 

Keypad myKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
LiquidCrystal lcd(12,11,A0,A1,A2,A3 );
char customKey = myKeypad.getKey();
void setup() {
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  lcd.begin(16,4);
  Serial.begin(9600);
  lcd.setCursor(4,1);
  lcd.print("Welcome!");
  delay(2000);
   lcd.clear();
  lcd.print("Initializing!");
  analogWrite(9,0);
  analogWrite(10,255);
  l=0;
  time1 = millis();
  while((millis()-time1)<20000);  
  analogWrite(9,0);
  analogWrite(10,0);
}

void loop() {
  lcd.clear();
  lcd.noBlink();
  lcd.print("Press:-");
  lcd.setCursor(0,1);
  lcd.print("  1 - Frequency");
  lcd.setCursor(0,2);
  lcd.print("  2 - Totaltime");
  lcd.setCursor(0,3);
  lcd.print("  3 - Start");
  while(1){
   if(customKey=='1')
    { freq=0;
      lcd.clear();
      lcd.print("Enter");
      lcd.setCursor(13,1);
      lcd.print("uHz");
      lcd.setCursor(0,2);
      lcd.print("Max - 24,000 uHz");
      lcd.setCursor(0,3);
      lcd.print("Min - 8000 uHz");
      customKey=0;
      lcd.setCursor(8,1);
      lcd.blink();
      i=0;
      while(customKey!='E')
        {
        if(customKey)
        {
          lcd.print(customKey);
          val[i]=customKey;
          i++;
        }
        customKey=myKeypad.getKey(); 
        }  
      for(m=0;m<i;m++)
      { 
       k=0;
      for(j=48;j<58;j++)
      {
       if(val[m]==j)
      {
         
         break;
       }
       else if(val[m]>47  && val[m]<58)
       k++;
        
      }
      freq =(pow(10,i-1-m)*k)+freq;
      }
      freq = 0.42*freq;
      Serial.println(freq);
    
      }
  if(customKey=='2')
    {   t=0;
        lcd.clear();
        lcd.print("Enter");
        lcd.setCursor(13,1);
        lcd.print("sec");
        lcd.setCursor(8,1);
        lcd.blink();
        i=0;
        customKey=0;
        while(customKey!='E')
        {
    
          if(customKey)
          { 
            lcd.print(customKey);
            val[i]=customKey;
            i++;
          }
          customKey=myKeypad.getKey(); 
        }
        for(m=0;m<i;m++)
        { 
         k=0;
        for(j=48;j<58;j++)
        {
         if(val[m]==j)
        {
           
           break;
        }
         else if(val[m]>47  && val[m]<58)
         k++;  
        }
        t =(pow(10,i-1-m)*k)+t; 
        } 
   }
    if(customKey=='E')
    
    { 
      lcd.clear();
    customKey=0;
    break; 
    }
   
    if(customKey=='3')
    {
      if(freq<3200 || t==0 ||freq>11000)
      {
        customKey=0;
        lcd.clear();
        lcd.print("Error");
        delay(2000);
        break;
      }  
    lcd.clear();
    customKey=0;
    lcd.print("Coating Started");
    lcd.setCursor(0,3);
    lcd.print("Press F1 to Stop");
    x=freq*0.0245;
    Serial.println("the time in each cycle is");
    Serial.println((500000*2)/3*freq);
     tt=0;
    while(tt<t){
      analogWrite(9,x);
      analogWrite(10,0);
      l=0;
      while(l<=200000/freq)
      {time1=millis();if(tt>t || customKey=='F')break;l++;while((unsigned long)(millis()-time1)<1000){customKey=myKeypad.getKey();if(customKey=='F')break;}tt++;Serial.println(tt);}
      l=0;
      if(tt>t || customKey=='F')break;
      analogWrite(9,0);
      analogWrite(10,x);
      Serial.println("moving backward");
      while(l<=200000/freq)
      {time1=millis();if(tt>t || customKey=='F')break;while((unsigned long)(millis()-time1)<1000){customKey=myKeypad.getKey();if(customKey=='F')break;}l++;tt++;Serial.println(tt);} 
      if(tt>t || customKey=='F')break;
      } 
    i=0;lcd.clear();customKey=0;lcd.print("Coating Stopped");analogWrite(9,0);analogWrite(10,0);delay(1500);
    break; 
    }
    else
    customKey=myKeypad.getKey();  
      
    }
  }            
