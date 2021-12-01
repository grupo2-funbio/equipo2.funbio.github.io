#include <MPU6050.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <I2Cdev.h>
LiquidCrystal lcd(6, 7, 5, 4, 3, 2);
MPU6050 MPU1(0x68);
MPU6050 MPU2(0x69);
//------------------------------------------------
const int BOTON_MAS = 8;  
const int BOTON_MENOS = 9;
const int BOTON_OK = 10;
const int CLK_EN= 12;
const int DT_EN = 11;
//-------------------------------------------------------
int16_t ax1,ay1,az1,Tmp1,gx1,gy1,gz1;
int16_t ax2,ay2,az2,Tmp2,gx2,gy2,gz2;
int i=0;

//Variables usadas por el filtro pasa bajos
long f_ax1,f_ay1, f_az1, f_ax2,f_ay2, f_az2;
int p_ax1, p_ay1, p_az1, p_ax2, p_ay2, p_az2;
int contador=0;

//Valor de los offsets
int ax1_o,ay1_o,az1_o,ax2_o,ay2_o,az2_o;

//Valores de filtro kallman
long tiempo_prev;
float dt;
float ang_x1, ang_y1, ang_x2, ang_y2;
float ang_x1_prev, ang_y1_prev, ang_x2_prev, ang_y2_prev;

int16_t ang_ref1;
int16_t ang_flex1;
int16_t ang_flex2;
int16_t ang_ref2;
int16_t dif;

//----------------------------------------------------------
int cycle_screen=1;
float st1, st3;
int sv4, sv2, value, valueminus;
int test1, value2, test3, value4; 
int test=0;

//-----------------------------------------------------------
int counter = 0;
int currentCLK;
int previousCLK;
int prevValue=0;
unsigned long lastTime, sampleTime;

void setup() {
  Serial.begin(57600);
  lcd.begin (16,2);  
  declare_input_1 ();
  declare_input_2 ();
  declare_wire_function ();
  read_offset();
  initial_writing();
}
 
void loop() {
      // Realizar lecturas
      // Realizar lecturas
      MPU1.getAcceleration(&ax1, &ay1, &az1);
      MPU2.getAcceleration(&ax2, &ay2, &az2);

      //Es necesario obtener la rotación para aplicar filtro de Kallman
      MPU2.getRotation(&gx1, &gy1, &gz1);
      MPU2.getRotation(&gx2, &gy2, &gz2);

      //Definicion parametros de filtro
      dt = (millis()-tiempo_prev)/1000.0;
      tiempo_prev=millis();

      // Filtrar las lecturas
      f_ax1 = f_ax1-(f_ax1>>5)+ax1;
      p_ax1 = f_ax1>>5;
      f_ay1 = f_ay1-(f_ay1>>5)+ay1;
      p_ay1 = f_ay1>>5;
      f_az1 = f_az1-(f_az1>>5)+az1;
      p_az1 = f_az1>>5;

      f_ax2 = f_ax2-(f_ax2>>5)+ax2;
      p_ax2 = f_ax2>>5;
      f_ay2 = f_ay2-(f_ay2>>5)+ay2;
      p_ay2 = f_ay2>>5;
      f_az2 = f_az2-(f_az2>>5)+az2;
      p_az2 = f_az2>>5;

      //Cada 100 lecturas corregir el offset
      if (contador==100){
        //Calibrar acelerometros a 1g en el eje z (ajustar el offset)
        if (p_ax1>0) ax1_o--;
        else {ax1_o++;}
        if (p_ay1>0) ay1_o--;
        else {ay1_o++;}
        if (p_az1-16384>0) az1_o--;
        else {az1_o++;}
        if (p_ax2>0) ax2_o--;
        else {ax2_o++;}
        if (p_ay2>0) ay2_o--;
        else {ay2_o++;}
        if (p_az2-16384>0) az2_o--;
        else {az2_o++;}

        //Se asignan los nuevos offsets a sus respectivas variables
        MPU1.setXAccelOffset(ax1_o);
        MPU1.setYAccelOffset(ay1_o);
        MPU1.setZAccelOffset(az1_o);

        MPU2.setXAccelOffset(ax2_o);
        MPU2.setYAccelOffset(ay2_o);
        MPU2.setZAccelOffset(az2_o);

        //contador que permite corregir el offset cada 100 lecturas
        contador=0;
      }
      contador++;

      // Escalar las aceleraciones a m/s2
      float ax1_m_s2 = ax1 * (9.81/16384.0);
      float ay1_m_s2 = ay1 * (9.81/16384.0);
      float az1_m_s2 = az1 * (9.81/16384.0);
      float ax2_m_s2 = ax2 * (9.81/16384.0);
      float ay2_m_s2 = ay2 * (9.81/16384.0);
      float az2_m_s2 = az2 * (9.81/16384.0);

      //Calcular los angulos de inclinacion:
      float accel_ang_x1=atan(ax1/sqrt(pow(ay1,2) + pow(az1,2)))*(180.0/3.14);
      float accel_ang_y1=atan(ay1/sqrt(pow(ax1,2) + pow(az1,2)))*(180.0/3.14);
      float accel_ang_x2=atan(ax2/sqrt(pow(ay2,2) + pow(az2,2)))*(180.0/3.14);
      float accel_ang_y2=atan(ay2/sqrt(pow(ax2,2) + pow(az2,2)))*(180.0/3.14);


      if(i==0){
        ang_ref1 = accel_ang_x1;
        ang_ref2 = accel_ang_x2;
      }
      i++;
      
      ang_flex1 = accel_ang_x1 - ang_ref1;
      ang_flex2 = accel_ang_x2 - ang_ref2;
      
      //Obtener angulo final con filtro complementario
      ang_x1 = 0.98*(ang_x1_prev+(gx1/131)*dt) + 0.02*ang_flex1;
      ang_y1 = 0.98*(ang_y1_prev+(gy1/131)*dt) + 0.02*accel_ang_y1;
      ang_x2 = 0.98*(ang_x2_prev+(gx2/131)*dt) + 0.02*ang_flex2;
      ang_y2 = 0.98*(ang_y2_prev+(gy2/131)*dt) + 0.02*accel_ang_y2;

      ang_x1_prev=ang_x1;
      ang_y1_prev=ang_y1;
      ang_x2_prev=ang_x2;
      ang_y2_prev=ang_y2;
      dif = ang_y1 - ang_y2;

      delay(10);      
      state_machine();
}
 
void state_machine(){  
  switch (cycle_screen) {    
    case 1:
    lcd.clear();
    value= abs(dif);
    test1 = test_value(value);
    display_values_flex(value); 
      if (digitalRead(10)==LOW){     
        st1=test1;
        test=0;
        delay (500);
        lcd.clear();  
        cycle_screen=2;                 
        } 
      break; 
 
    case 2:
    
    value2= get_pain();
    prevValue=value2;
    display_values_pain (value2);
      if (digitalRead(10)==LOW){
         sv2=value2;
         delay(500);
         cycle_screen=3;
         lcd.clear();
         }
       break;
 
    case 3:
      
      value= abs(dif);
      test3 = test_value(value);  
      display_values_ext(test3);  
      if (digitalRead(10)==LOW){    
        st3=test3;
        test=0;  
        delay(500); 
        cycle_screen=4;
        lcd.clear();
        }
       break;
 
    case 4:
      
      value4= get_pain();
      prevValue=value4;
      display_values_pain (value4);
      if (digitalRead(10)==LOW){
         sv4=value4;
         delay(500);
         cycle_screen=5;
         lcd.clear();
         }
       break;
 
    case 5:
      
      /*lcd.print ("transmitiendo");*/
      release_data_python(st1, sv2, st3, sv4);
      if (digitalRead(8)==LOW){
        cycle_screen=6;
        delay(500);
        lcd.clear();
      } 
      break;
 
    case 6:
      
      display_saved_data_flex (st1,sv2);
      if (digitalRead(8)==LOW){
        cycle_screen++;
        delay (500);
        lcd.clear();
      }
      break;    
 
    case 7:
      
      display_saved_data_ext (st3,sv4);
      if (digitalRead(9)==LOW){
      if (valueminus==LOW){
        cycle_screen--;
        delay (500);
        lcd.clear();
      }
      break;
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
  MPU1.initialize();    
  MPU2.initialize();
  /*if (MPU1.testConnection()){
    //Serial.println("Sensor 1 iniciado correctamente");
    lcd.setCursor(0,0);
    lcd.print ("Sensor 1 OK");
    delay (1000);
  }
  else{
    //Serial.println("Error al iniciar el sensor");
    lcd.setCursor(0,0);
    lcd.print ("Sensor 1 Error");
    delay (1000);
  }
  if (MPU2.testConnection()){
   //Serial.println("Sensor 2 iniciado correctamente");
    lcd.setCursor(0,1);
    lcd.print ("Sensor 2 OK");
    delay (1000);
  }
  else{
    //Serial.println("Error al iniciar el sensor");
    lcd.setCursor(0,1);
    lcd.print ("Sensor 2 Error");
    delay (1000);
  }*/
}
void read_offset(){
      ax1_o=MPU1.getXAccelOffset();
      ay1_o=MPU1.getYAccelOffset();
      az1_o=MPU1.getZAccelOffset();
      ax2_o=MPU2.getXAccelOffset();
      ay2_o=MPU2.getYAccelOffset();
      az2_o=MPU2.getZAccelOffset();  
}

void initial_writing(){
      /*Serial.println("Offsets:");
      Serial.print(ax1_o); Serial.print("\t"); 
      Serial.print(ay1_o); Serial.print("\t"); 
      Serial.print(az1_o); Serial.print("\t"); 
      Serial.print(ax2_o); Serial.print("\t"); 
      Serial.print(ay2_o); Serial.print("\t");
      Serial.print(az2_o); Serial.print("\t");*/
      lcd.clear();      
      //Serial.println("Envie cualquier caracter para empezar la calibracion"); 
      lcd.setCursor (0,0);
      /*lcd.print("presione OK");
      lcd.setCursor(0,1);*/
      lcd.print("Calibrando"); 
      
      // Espera un caracter para empezar a calibrar
      while (true){
          if(digitalRead(10)==LOW){            
          break;
          }
        }  
      /*lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Calibrando");
      lcd.setCursor(0,1);
      lcd.print("no mover");*/
     //Serial.println("Calibrando, no mover IMU");
     delay (2000);
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

 
void display_values_flex(int test){
    Serial.print ("fld");
    Serial.print (" ");
    Serial.println (test);
    lcd.setCursor (0,0);
    lcd.print("FL. Der:");
    lcd.print(test);
}

void display_values_ext(int test){
    Serial.print ("fli");
    Serial.print (" ");
    Serial.println (test);
    lcd.setCursor (0,0);
    lcd.print("FL. Izq:");
    lcd.print(test);
}
 
void display_values_pain (int value){
    Serial.print ("Dolor: ");
    Serial.println (value);
    lcd.setCursor (0,0);
    lcd.print("Dolor: ");
    lcd.print(value);
}
 
 
void release_data_python(int st1, int sv2, int st3, int sv4 ){
    if (millis()-lastTime >= sampleTime){
        lastTime=millis();
        Serial.println (st1);
        Serial.println (sv2);
        Serial.println (st3);
        Serial.println (sv4);
        }
    }
 
void display_saved_data_flex (int st1,int sv2){
    /*Serial.print ("datos flexion");
    Serial.print (" || ");
    Serial.print (st1);
    Serial.print (" ");
    Serial.println (sv2);*/
    lcd.print("FL. Der: ");
    lcd.print(st1);
    lcd.setCursor (0,1);
    lcd.print("Dolor: ");
    lcd.print(sv2);
    lcd.print("/10");
    lcd.setCursor(0,0);
}
 
void display_saved_data_ext (int st3,int sv4){
    /*Serial.print ("datos extension");
    Serial.print (" || ");
    Serial.print (st3);
    Serial.print (" ");
    Serial.println (sv4);*/
    lcd.print("FL. Izq: ");
    lcd.print(st3);
    lcd.setCursor (0,1);
    lcd.print("Dolor: ");
    lcd.print(sv4);
    lcd.print("/10");    
    lcd.setCursor(0,0);
}
