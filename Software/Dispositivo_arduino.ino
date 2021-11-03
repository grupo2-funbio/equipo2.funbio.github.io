#include <I2Cdev.h>
#include <LiquidCrystal.h>
#include<Wire.h>
#include<MPU6050.h>

const int MPU2=0x69,MPU1=0x68;
int16_t AcX1,AcY1,AcZ1,GyX1,GyY1,GyZ1;
int16_t AcX2,AcY2,AcZ2,GyX2,GyY2,GyZ2;
LiquidCrystal lcd(6, 7, 5, 4, 3, 2);

long tiempo_prev_1;
float dt1;
float ang_x1, ang_y1, ang_z1;
float ang_x1_prev, ang_y1_prev, ang_z1_prev; 

long tiempo_prev_2;
float dt2;
float ang_x2, ang_y2, ang_z2;
float ang_x2_prev, ang_y2_prev, ang_z2_prev;

const int BUTTON_PLUS = 8;  
const int BUTTON_MINUS = 9;
const int BUTTON_OK = 10;
const int CLK_EN= 12;
const int DT_EN = 11;
const int DEBOUNCE_DELAY = 10;


double flexion, extension, right_lateral_flexion, left_lateral_flexion, a_fl, a_ex, a_rlf, a_llf, store_flex, store_ext, store_rlf, store_llf; 

int lastSteadyState1 = LOW;       
int lastFlickerableState1 = LOW;  
int currentState1;

int lastSteadyState2 = LOW;       
int lastFlickerableState2 = LOW;  
int currentState2;

int lastSteadyState3 = LOW;       
int lastFlickerableState3 = LOW;  
int currentState3;

byte cycle_screen_1= 1;
byte cycle_screen_2= 1;

unsigned long lastDebounceTime1 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime2 = 0;
unsigned long lastDebounceTime3 = 0;

int pain, store_pain_f, store_pain_e, store_pain_r, store_pain_l;
int answer=0;

void setup(){
  lcd.begin (16, 2);

  
  Wire.begin(); 
  Wire.beginTransmission(MPU1);
  Wire.write(0x6B);// PWR_MGMT_1 register 
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Wire.begin(); 
  Wire.beginTransmission(MPU2);
  Wire.write(0x6B);// PWR_MGMT_1 register 
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(57600); 

  pinMode(BUTTON_PLUS, INPUT_PULLUP);
  pinMode (BUTTON_MINUS, INPUT_PULLUP);
  pinMode (BUTTON_OK, INPUT_PULLUP);
  pinMode (CLK_EN, INPUT);
  pinMode (DT_EN, INPUT);
  lcd.setCursor (0,0);
  lcd.print ("Medicion");
  lcd.setCursor (0,1);
  lcd.print ("Rango mov.");
  delay (500);
  lcd.clear();
  lcd.print ("Sensores listos");
  lcd.setCursor (0,1);
  lcd.print ("y colocados");
  delay (500);
  menu1 ();
}

void loop (){
  buttoncont();
}


void menu1(){
  GetMpuValue1(MPU1);
  GetMpuValue2(MPU2);
  lcd.clear ();
  if (cycle_screen_1==1){

      flexion= angle_measure_f_e();  
        if (a_fl<flexion){
          a_fl=flexion;
        }
      pain= pain_measure ();
      lcd.setCursor (0,0);
      lcd.print ("Flexion: ");
      lcd.print (a_fl);
    
      lcd.setCursor (0,1);
      lcd.print ("Dolor: ");
      lcd.print (pain);
      lcd.print ("/10");
      buttonstore1();
      
    }
    if (cycle_screen_1==2){

      extension= angle_measure_f_e ();
        if (a_ex<extension){
          a_ex=extension;
        }
      pain= pain_measure ();
      lcd.setCursor (0,0);
      lcd.print ("Extension: ");
      lcd.print (a_ex);
    
      lcd.setCursor (0,1);
      lcd.print ("Dolor: ");
      lcd.print (pain);
      lcd.print ("/10");
      buttonstore2();

    }
    if (cycle_screen_1==3){

      right_lateral_flexion= angle_measure_r_l ();
        if (a_rlf<right_lateral_flexion){
          a_rlf=right_lateral_flexion;
        }
      pain= pain_measure ();
      lcd.setCursor (0,0);
      lcd.print ("Flexion: ");
      lcd.print (a_rlf);
    
      lcd.setCursor (0,1);
      lcd.print ("Flexion L Izq: ");
      lcd.print (pain);
      lcd.print ("/10");
      buttonstore3();

    }
    if (cycle_screen_1==4){

        if (a_llf<left_lateral_flexion){
          a_llf=left_lateral_flexion;
        }
      pain= pain_measure ();
      lcd.setCursor (0,0);
      lcd.print ("Flexion: ");
      lcd.print (a_llf);
    
      lcd.setCursor (0,1);
      lcd.print ("Dolor: ");
      lcd.print (pain);
      lcd.print ("/10");
      buttonstore4();
    }
    if (cycle_screen_1==5){
      
        lcd.print ("Transmitiendo");
        //asumiendo que realmente lo saquen del serial
        Serial.print (store_ext);
        Serial.print (store_rlf);
        Serial.print (store_llf);
        Serial.print (store_pain_f);
        Serial.print (store_pain_e);
        Serial.print (store_pain_r);
        Serial.println (store_pain_l);
        delay (10000);
        lcd.clear ();
        lcd.print ("Proceso");
        lcd.setCursor (0,1);
        lcd.print ("finalizado");       
        menu2access ();
        cycle_screen_1=1;      
      }
  }

void GetMpuValue1(const int MPU){ 
   
      Wire.beginTransmission(MPU); 
      Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) 
      Wire.endTransmission(false);
      Wire.requestFrom(MPU, 14, true); // request a total of 14 registers 
      AcX1=Wire.read()<<8| Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L) 
      AcY1=Wire.read()<<8|  Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
      AcZ1=Wire.read()<<8| Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L) 
 
      GyX1=Wire.read()<<8| Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L) 
      GyY1=Wire.read()<<8| Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L) 
      GyZ1=Wire.read()<<8| Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L) 
      
      tiempo_prev_1 = millis ();
      dt1= (millis()-tiempo_prev_1)/1000.0;     
      
      float accel_ang_x1=atan(AcX1/sqrt(pow(AcY1,2) + pow(AcZ1,2)))*(180.0/3.14);
      float accel_ang_y1=atan(AcY1/sqrt(pow(AcX1,2) + pow(AcZ1,2)))*(180.0/3.14);
      float accel_ang_z1=atan(AcZ1/sqrt(pow(AcX1,2) + pow(AcY1,2)))*(180.0/3.14);

      ang_x1 = 0.98*(ang_x1_prev+(GyX1/131)*dt1)+0.02*accel_ang_x1;
      ang_y1 = 0.98*(ang_y1_prev+(GyY1/131)*dt1)+0.02*accel_ang_y1;
      ang_z1 = 0.98*(ang_z1_prev+(GyZ1/131)*dt1)+0.02*accel_ang_z1;

      ang_x1_prev=ang_x1;
      ang_y1_prev=ang_y1;
      ang_z1_prev=ang_z1; 
     }
     
     
 void GetMpuValue2(const int MPU){ 
   
      Wire.beginTransmission(MPU); 
      Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) 
      Wire.endTransmission(false);
      Wire.requestFrom(MPU, 14, true); // request a total of 14 registers 
      AcX2=Wire.read()<<8| Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L) 
      AcY2=Wire.read()<<8|  Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
      AcZ2=Wire.read()<<8| Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L) 

      GyX2=Wire.read()<<8| Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L) 
      GyY2=Wire.read()<<8| Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L) 
      GyZ2=Wire.read()<<8| Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

      tiempo_prev_2 = millis ();
      dt2= (millis()-tiempo_prev_2)/1000.0;     
      
      float accel_ang_x2=atan(AcX2/sqrt(pow(AcY2,2) + pow(AcZ2,2)))*(180.0/3.14);
      float accel_ang_y2=atan(AcY2/sqrt(pow(AcX2,2) + pow(AcZ2,2)))*(180.0/3.14);
      float accel_ang_z2=atan(AcZ2/sqrt(pow(AcX2,2) + pow(AcY2,2)))*(180.0/3.14);

      ang_x2 = 0.98*(ang_x2_prev+(GyX2/131)*dt2)+0.02*accel_ang_x2;
      ang_y2 = 0.98*(ang_y2_prev+(GyY2/131)*dt2)+0.02*accel_ang_y2;
      ang_z2 = 0.98*(ang_z2_prev+(GyZ2/131)*dt2)+0.02*accel_ang_z2;

      ang_x2_prev=ang_x2;
      ang_y2_prev=ang_y2;
      ang_z2_prev=ang_z2; 

     }

float angle_measure_r_l (){
  float angle_z;
  angle_z=(ang_z2-ang_z1);
  return angle_z;
    
}

float angle_measure_f_e (){
 
  float angle_x;
  angle_x=(ang_x2-ang_x1);
  return angle_x;
}


  
int pain_measure(){
  int counter = 5;
  int aState;
  int aLastState;
    aState = digitalRead (CLK_EN);
    if (aState != aLastState){
      if (digitalRead (DT_EN)!= aState){
        counter ++;
      }
      else{
        counter --;
      }      
    }
    aLastState = aState;
    return counter;
}


void buttonstore1(){

  currentState3 = digitalRead(BUTTON_OK);  
    if (currentState3 != lastFlickerableState3) {
    lastDebounceTime3 = millis();
    lastFlickerableState3 = currentState3;
  }
  if ((millis() - lastDebounceTime3) > DEBOUNCE_DELAY) {
    if(lastSteadyState3 == LOW && currentState3 == HIGH)      
      if (lastSteadyState3 != currentState3){ 
          store_flex=a_fl;
          store_pain_f=pain;     
    }
    lastSteadyState3 = currentState3;
  }
}

void buttonstore2(){

  currentState3 = digitalRead(BUTTON_OK);  
    if (currentState3 != lastFlickerableState3) {
    lastDebounceTime3 = millis();
    lastFlickerableState3 = currentState3;
  }
  if ((millis() - lastDebounceTime3) > DEBOUNCE_DELAY) {
    if(lastSteadyState3 == LOW && currentState3 == HIGH)      
      if (lastSteadyState3 != currentState3){ 
          store_ext=a_ex;
          store_pain_e=pain;     
    }
    lastSteadyState3 = currentState3;
  }
}

void buttonstore3(){

  currentState3 = digitalRead(BUTTON_OK);  
    if (currentState3 != lastFlickerableState3) {
    lastDebounceTime3 = millis();
    lastFlickerableState3 = currentState3;
  }
  if ((millis() - lastDebounceTime3) > DEBOUNCE_DELAY) {
    if(lastSteadyState3 == LOW && currentState3 == HIGH)      
      if (lastSteadyState3 != currentState3){ 
          store_rlf=a_rlf;
          store_pain_r=pain;     
    }
    lastSteadyState3 = currentState3;
  }
}

void buttonstore4(){

  currentState3 = digitalRead(BUTTON_OK);  
    if (currentState3 != lastFlickerableState3) {
    lastDebounceTime3 = millis();
    lastFlickerableState3 = currentState3;
  }
  if ((millis() - lastDebounceTime3) > DEBOUNCE_DELAY) {
    if(lastSteadyState3 == LOW && currentState3 == HIGH)      
      if (lastSteadyState3 != currentState3){ 
          store_llf=a_llf;
          store_pain_l=pain;     
    }
    lastSteadyState3 = currentState3;
  }
}

//funcion de pase menu 1. No funciona!
void buttoncont(){

  currentState1 = digitalRead(BUTTON_PLUS);  
  if (currentState1 != lastFlickerableState1) {
    lastDebounceTime1 = millis();
    lastFlickerableState1 = currentState1;
  }
  if ((millis() - lastDebounceTime1) > DEBOUNCE_DELAY) {
    if(lastSteadyState1 == LOW && currentState1 == HIGH)      
      if (lastSteadyState1 != currentState1){        
        if (cycle_screen_1<5){
        cycle_screen_1= cycle_screen_1+1;
        menu1 ();
        }
        if (cycle_screen_1==5){
          cycle_screen_1=5;        
        }       
    }    
    lastSteadyState1 = currentState1;
  }
}


void menu2access (){
  buttonplus2 ();
  buttonminus ();
}


void buttonminus(){
  currentState2 = digitalRead(BUTTON_MINUS);

  if (currentState2 != lastFlickerableState2) {
    lastDebounceTime2 = millis();
    lastFlickerableState2 = currentState2;
  }
  if ((millis() - lastDebounceTime2) > DEBOUNCE_DELAY)  {
    if(lastSteadyState2 == LOW && currentState2 == HIGH)      
      if (lastSteadyState2 != currentState2){
      cycle_screen_2= cycle_screen_2-1;
       if (cycle_screen_2<1){
         cycle_screen_2=4;
          }
      menu2();         
    }
    lastSteadyState2 = currentState2;
  }    
}

//funcion de 2
void buttonplus2(){

  currentState1 = digitalRead(BUTTON_PLUS);  
  if (currentState1 != lastFlickerableState1) {
    lastDebounceTime1 = millis();
    lastFlickerableState1 = currentState1;
  }
  if ((millis() - lastDebounceTime1) > DEBOUNCE_DELAY) {
    if(lastSteadyState1 == LOW && currentState1 == HIGH)      
      if (lastSteadyState1 != currentState1){
        cycle_screen_2= cycle_screen_2+1;
        if (cycle_screen_2>4){
          cycle_screen_2= 1;
        }      
      menu2(); 
    }    
    lastSteadyState1 = currentState1;
  }
}

//funcion de 2
void menu2(){
  lcd.clear ();
  switch (cycle_screen_2){
    case 1:{
      lcd.print ("Flexion: ");
      lcd.print (store_flex);
      lcd.setCursor (0,1);
      lcd.print ("Dolor:");
      lcd.print (store_pain_f);
      lcd.print ("/10");
      break;
    }
    case 2:{
      lcd.print ("Extension: ");
      lcd.print (store_ext);
      lcd.setCursor (0,1);
      lcd.print ("Dolor:");
      lcd.print (store_pain_e);
      lcd.print ("/10");
      break;
    }
    case 3:{
      lcd.print ("Flexion Der: ");
      lcd.print (store_rlf);
      lcd.setCursor (0,1);
      lcd.print ("Dolor:");
      lcd.print (store_pain_r);
      lcd.print ("/10");
      break;
    }
    case 4:{
      lcd.print ("Flexion Izq: ");
      lcd.print (store_llf);
      lcd.setCursor (0,1);
      lcd.print ("Dolor:");
      lcd.print (store_pain_l);
      lcd.print ("/10");
      break;
    }
  }
}
