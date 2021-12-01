#include <MPU6050_light.h>
#include <LiquidCrystal.h>
#include <Wire.h>
LiquidCrystal lcd(6, 7, 5, 4, 3, 2);
//-------------------------------------------------------
const int BOTON_MAS = 8;  
const int BOTON_MENOS = 9;
const int BOTON_OK = 10;
const int CLK_EN= 12;
const int DT_EN = 11;
//------------------------------------------------------
MPU6050 mpu(Wire);
unsigned long timer = 0;
int first_measure, first_x, first_y, first_z, measuring_x, measuring_y, measuring_z, difference_x, difference_y, difference_z;

//-----------------------------------------------------------------

int cycle_screen=0;
int st1, st3;
int sv4, sv2, value, valueminus;
int test=0;
int change;
//------------------------------------------------------------
int counter = 0;
int currentCLK;
int previousCLK;
int prevValue=0;
int value2=0;
int value4=0;

void setup() {
  Serial.begin(115200);  
  declare_input_1 ();
  declare_input_2 ();
  declare_wire_function ();
  lcd.begin (16,2);
  initial_writing();
}

void loop() {

  if(cycle_screen==0){
    lcd.clear();
    int value= get_value();
    int test1 = test_value(value);
    display_values_flex(value);
    change = digitalRead(10);    
    if (change==LOW){     
      st1=test1; 
      test=0;  
      delay(500); 
      cycle_screen++;          
      }
    }
    
  else if (cycle_screen==1){
    value2= get_pain();
    prevValue=value2;
    display_values_pain(value2);
    change = digitalRead(10);    
    if (change==LOW){   
      sv2=value2;
      delay(500); 
      cycle_screen++;          
      }
  }
  
  else if(cycle_screen==2){ 
    int value= get_value();
    int test3 = test_value(value); 
    display_values_ext(value);
    change = digitalRead(10);    
    if (change==LOW){  
      st3=test3;
      test=0;
      cycle_screen++;
      delay(500);     
    }
  }   
  
  else if (cycle_screen==3){
    value4= get_pain();
    prevValue=value4;
    display_values_pain(value4);
    change = digitalRead(10);    
    if (change==LOW){   
      sv4=value4;
      delay(500); 
      cycle_screen++;          
      }
  }
  
  else if (cycle_screen==4){
    release_data_python(st1, sv2, st3, sv4);
    change = digitalRead (8);
    if (change==LOW){
      cycle_screen++;
      delay(500);
    }  
  }

  else if (cycle_screen==5){

    display_saved_data_flex (st1,sv2);
    change = digitalRead (8);
    if (change==LOW){
      cycle_screen++;
      delay (500);
    }    
  }
  
  else if (cycle_screen==6){   
    display_saved_data_ext (st3,sv4);
    valueminus = digitalRead (9);
    if (valueminus==LOW){
      cycle_screen--;
      delay (500);
    }
  }  
}

void declare_input_1 (){
  pinMode (BOTON_MAS, INPUT_PULLUP);
  pinMode (BOTON_MENOS, INPUT_PULLUP);  
}

void declare_input_2 (){
  pinMode (BOTON_OK, INPUT_PULLUP);
  pinMode (CLK_EN, INPUT);
  pinMode (DT_EN, INPUT);
  previousCLK = digitalRead(CLK_EN);   
}

void declare_wire_function (){
  Wire.begin(); 
}

void initial_writing(){
  byte status = mpu.begin();
  lcd.setCursor (0,0);
  lcd.print ("Estado del");
  lcd.setCursor (0,1);
  lcd.print ("sensor ");
  lcd.print (status);
  
  while(status!=0){}
  lcd.setCursor (0,0);
  lcd.print ("Calc. offset");
  lcd.setCursor (0,1);
  lcd.print ("no mover");  
  delay (2000);
  mpu.calcOffsets();
  lcd.clear();
  lcd.print ("Hecho!");
  delay (2000);
  lcd.clear();
  lcd.print ("Sensores listos");
  lcd.setCursor (0,1);
  lcd.print ("y colocados");
  delay (200);
}

int get_value (){
 mpu.update(); 
  /*Serial.print("X : ");
  Serial.print(mpu.getAngleX());
  Serial.print("\tY : ");
  Serial.print(mpu.getAngleY());
  Serial.print("\tZ : ");
  Serial.println(mpu.getAngleZ());*/
  if (first_measure==0){
    first_x=mpu.getAngleX();
    first_y=mpu.getAngleY();
    first_z=mpu.getAngleZ();
    first_measure=1;
  }
  measuring_x=mpu.getAngleX();
  measuring_y=mpu.getAngleY();
  measuring_z=mpu.getAngleZ();
  difference_x=abs(measuring_x-first_x);
  difference_y=abs(measuring_y-first_y);
  difference_z=abs(measuring_z-first_z);
  /*Serial.print (difference_x);
  Serial.print (" || ");
  Serial.print (difference_y);
  Serial.print (" || ");
  Serial.println(difference_z);*/
  timer = millis();
  return difference_x; 
}

int test_value(int value){
  if(test<value){
  test=value;
  return test; 
  } 
}

int get_pain (){  
  currentCLK = digitalRead(CLK_EN);
  if(currentCLK != previousCLK)
  {       
    if(digitalRead(DT_EN) != currentCLK)
    { 
      counter++;
    }
    else
    {
      counter--; 
    }         
    if (counter<0){
      counter=0;
    }
    else if (counter>10){
      counter=10;
    }
  }
  previousCLK = currentCLK;
  return counter; 
}

void display_values_flex(float test){
    Serial.print ("flexion");
    Serial.print (" ");
    Serial.print (test);
    Serial.print (" ");
    Serial.println (value);
    lcd.setCursor (0,0);
    lcd.print("Flexion: ");
    lcd.print(test);
}

void display_values_ext(float test){
    Serial.print ("extension");
    Serial.print (" ");
    Serial.print (test);
    Serial.print (" ");
    Serial.println (value);
    lcd.setCursor (0,0);
    lcd.print("Extension: ");
    lcd.print(test);
}

void display_values_pain (int value){
    lcd.setCursor (0,0);
    lcd.print("Dolor: ");
    lcd.print(value);
    lcd.print("/10");
}

void release_data_python(float st1, int sv2, float st3, int sv4 ){
    lcd.setCursor(0,0);
    lcd.print("transmitiendo");   
    Serial.print (st1);
    Serial.print ("\t");
    Serial.print (sv2);
    Serial.print ("\t");
    Serial.print (st3);
    Serial.print ("\t");
    Serial.print (sv4);
    Serial.println ();
    lcd.setCursor(0,0);
}
void display_saved_data_flex (float st1,int sv2){
    Serial.print ("datos flexion");
    Serial.print (" || ");
    Serial.print (st1);
    Serial.print (" ");
    Serial.println (sv2);
    lcd.print("Flexion: ");
    lcd.print(st1);
    lcd.setCursor (0,1);
    lcd.print("Dolor: ");
    lcd.print(sv2);
    lcd.print("/10");
    lcd.setCursor(0,0);
}

void display_saved_data_ext (float st3,int sv4){
    Serial.print ("datos extension");
    Serial.print (" || ");
    Serial.print (st3);
    Serial.print (" ");
    Serial.println (sv4);
    lcd.print("Extension: ");
    lcd.print(st3);
    lcd.setCursor (0,1);
    lcd.print("Dolor: ");
    lcd.print(sv4);
    lcd.print("/10");    
    lcd.setCursor(0,0);
}
