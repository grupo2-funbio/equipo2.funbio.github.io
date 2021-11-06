
#include <I2Cdev.h>
#include <LiquidCrystal.h>
#include<Wire.h>
#include<MPU6050.h>

/*/problema 1
Las librerias a incluir. Solamente la LiquidCrystal se usa en el resto del proyecto porque maneja el LCD
las otras tres librerias, Wire, MPU6050 e I2Cdev se utilizan para lo del manejo de los IMUS al menos en el tutorial que encontré. Coordinar con Gabriel que librerias tienes que descargar para que funcione. Wire.h y LiquidCrystal.h ya vienen incluidas en el arduino.


*/
/*definicion de pines a colocar en el arduino. No se tocan a menos que sea necesario.
Si se modifican, coordinar con Natali para que se guie al realizar el ensamblaje y con Erick para cambiar el diseño del KiCad
*/
const int MPU2=0x69,MPU1=0x68;
LiquidCrystal lcd(6, 7, 5, 4, 3, 2);
const int BOTON_MAS = 8;  
const int BOTON_MENOS = 9;
const int BOTON_OK = 10;
const int CLK_EN= 12;
const int DT_EN = 11;

/*Variables relacionadas con la medicion de angulos a partir de IMUS. Probablemente se tengan que cambiar, coordinar con Gabriel.*/
int16_t AcX1,AcY1,AcZ1,GyX1,GyY1,GyZ1;
int16_t AcX2,AcY2,AcZ2,GyX2,GyY2,GyZ2;

long tiempo_prev_1;
float dt1;
float ang_x1, ang_y1, ang_z1;
float ang_x1_prev, ang_y1_prev, ang_z1_prev; 

long tiempo_prev_2;
float dt2;
float ang_x2, ang_y2, ang_z2;
float ang_x2_prev, ang_y2_prev, ang_z2_prev;



//Variables de almacenamiento de ángulos en dispositivo. Dependiendo de la salida del los IMUS de repente es necesario cambiar su tipo de dato de float a algo más

float flexion, extension, flexion_derecha, flexion_izquierda, a_fl, a_ex, a_fld, a_fli, guardar_flex, guardar_ext, guardar_fld, guardar_fli; 

//variables de almacenamiento y control de medición del dolor. Toma los datos del encoder. Se queda como int porque son numeros de 0 al 10
int dolor, guardar_dolor_f, guardar_dolor_e, guardar_dolor_r, guardar_dolor_l;

/*Variables relacionadas a debouncing. El debouncing se usa para evitar que el botón mande más de una señal https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce
Este es el primer problema. Más adelante una de las funciones que usa el debouncing no funciona. Tal vez sea más conveniente usar una libreria para reemplazar toda la funcion y reemplazarlo por algo simple.
como https://github.com/maykon/botonDebounce. No pude probarlo porque Tinkercad no permite instalar librerias. 
*/
const int RETRASO_DEBOUNCE = 10;
int ultimoEstadoEstable1 = LOW;       
int ultimoCambioEstado1 = LOW;  
int estadoActual1;

int ultimoEstadoEstable2 = LOW;       
int ultimoCambioEstado2 = LOW;  
int estadoActual2;

int ultimoEstadoEstable3 = LOW;       
int ultimoCambioEstado3 = LOW;  
int estadoActual3;
unsigned long ultimoTiempoDebounce1 = 0;  // the last time the output pin was toggled
unsigned long ultimoTiempoDebounce2 = 0;
unsigned long ultimoTiempoDebounce3 = 0;

//variables que controlan los datos que muestra el LCD. Dependiendo de como plantees los menus puedes cambiar esto.
byte cambio_pantalla_1= 1;
byte cambio_pantalla_2= 1;

//setup es lo que corre el arduino al principio
void setup(){

  //inicializacion del lcd, no tocar.
  lcd.begin (16, 2);

  //inicializacion de los IMUS. Cambiar de acuerdo a lo coordinado con Gabriel.
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
  
  //inicialización del serial. Coordinar bien el baudrate (el numero entre parentesis que dice que tan rapido se renuevan los datos) Informar del baudrate escogido
  Serial.begin(57600); 

  //Declaracion de pines, no tocar
  pinMode(BOTON_MAS, INPUT_PULLUP);
  pinMode (BOTON_MENOS, INPUT_PULLUP);
  pinMode (BOTON_OK, INPUT_PULLUP);
  pinMode (CLK_EN, INPUT);
  pinMode (DT_EN, INPUT);
  
  //Introducción. Si se introduce calibración probablemente sea aqui. Coordinar con Gabriel. Pantalla dice "Medicion rango mov", pasa 0.5s y cambia a decir "Sensores listos y colocados" para pasar al menu.
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

void loop(){
  //Llama funciones que miden IMUs. Cambiar funcion de acuerdo a los cambios realizados.
  
  GetMpuValue1(MPU1);
  GetMpuValue2(MPU2);

  //limpia pantalla
  lcd.clear ();

  //variacion de pantallas de medicion. Retirar variables 2 y 3 si quitan flexion lateral derecha e izquierda para el preliminar. Puedes reemplazar con un switch-case de ser conveniente pero atentos al break.
  //se necesita que la función esté repitiendose porque mide los cambios en angulo y encoder de manera continua., un break rompe el ciclo.
  
  if (cambio_pantalla_1==1){
      
      //funcion que adquiere ángulo de inclinación final producto de ambos IMUS
      
      flexion= angulo_medido_f_e();  

      // a_fl actualiza el valor de flexion al máximo posible. Esto se realiza para que no se reescriba con ángulos menores una vez el paciente regrese a su posicion normal tras hacer el movimiento
        if (a_fl<flexion){
          a_fl=flexion;
        }

      //funcion que mide el valor de dolor. Se modifica con el encoder
      dolor= dolor_medido ();

      //pone el cursor del display en la esquina superior izquierda
      lcd.setCursor (0,0);

      //Se observa en la pantalla Flexion: y el valor del angulo maximo visto más arriba 
      lcd.print ("Flexion: ");
      lcd.print (a_fl);

      //cursor baja a segunda linea    
      lcd.setCursor (0,1);

      //Se visualiza el valor variable del encoder. "Dolor: x/10"
      lcd.print ("Dolor: ");
      lcd.print (dolor);
      lcd.print ("/10");
      
      //llama funcion. Funcion guarda los datos de a_fl y dolor en variables propias al movimiento de flexion y cambia a la pantalla de extension. Variable de cambio_pantalla_1 aumenta en uno y refresca la pantalla.
      botonguardar1();
      
    }
    //Hace exactamente lo mismo que la funcion de flexion, guarda los datos en variables especificas a extension.
    if (cambio_pantalla_1==2){

      extension= angulo_medido_f_e ();
        if (a_ex<extension){
          a_ex=extension;
        }
      dolor= dolor_medido ();
      lcd.setCursor (0,0);
      lcd.print ("Extension: ");
      lcd.print (a_ex);
    
      lcd.setCursor (0,1);
      lcd.print ("Dolor: ");
      lcd.print (dolor);
      lcd.print ("/10");
      botonguardar2();

    }

    //Hace lo mismo. Si solo se prueba flexion y extension esto se elimina. Cuidado con la variable de control.
    if (cambio_pantalla_1==3){

      flexion_derecha= angulo_medido_r_l ();
        if (a_fld<flexion_derecha){
          a_fld=flexion_derecha;
        }
      dolor= dolor_medido ();
      lcd.setCursor (0,0);
      lcd.print ("Flexion: ");
      lcd.print (a_fld);
    
      lcd.setCursor (0,1);
      lcd.print ("Flexion L Izq: ");
      lcd.print (dolor);
      lcd.print ("/10");
      botonguardar3();

    }

     //Hace lo mismo. Si solo se prueba flexion y extension esto se elimina. Cuidado con la variable de control.
    if (cambio_pantalla_1==4){

        if (a_fli<flexion_izquierda){
          a_fli=flexion_izquierda;
        }
      dolor= dolor_medido ();
      lcd.setCursor (0,0);
      lcd.print ("Flexion: ");
      lcd.print (a_fli);
    
      lcd.setCursor (0,1);
      lcd.print ("Dolor: ");
      lcd.print (dolor);
      lcd.print ("/10");
      botonguardar4();
    }

    //Parte de transmisión de datos. Aparece cuando ya se han realizado todas las mediciones. Cambiar variable a ==3 en caso de que eliminen las flexiones laterales.
    if (cambio_pantalla_1==5){
        //pantalla escribe "transmitiendo"
        lcd.print ("Transmitiendo");
        // tiempo de espera para inicio del serial.
        delay (2000);
        //Se muestran los datos del serial. Importante para transmisión de datos a python. Sujeto a cambio, consultar con Erick el fin de semana.
        
        Serial.print (guardar_ext);
        Serial.print (guardar_fld);
        Serial.print (guardar_fli);
        Serial.print (guardar_dolor_f);
        Serial.print (guardar_dolor_e);
        Serial.print (guardar_dolor_r);
        Serial.println (guardar_dolor_l);
        
        menu2access ();
            
      }
  }


//obtención de ángulos de MPU 1. Coordinar con Gabriel. Probablemente se cambie.
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

      //objetivo de la funcion es obtener los angulos en las rotaciones que nos importan para flexion y extension
      ang_x1_prev=ang_x1;
      ang_y1_prev=ang_y1;
      ang_z1_prev=ang_z1; 
     }
     
  //obtención de ángulos de MPU 2. Coordinar con Gabriel. Probablemente se cambie.   
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

      //objetivo de la funcion es obtener los angulos en las rotaciones que nos importan para flexion y extension
      ang_x2_prev=ang_x2;
      ang_y2_prev=ang_y2;
      ang_z2_prev=ang_z2; 

     }


//funcion para obtener angulo final como diferencia de los angulos medidos en ambos IMUS. Este mide la rotacion en eje Z. Borrar si se elimina los movimientos de flexion lateral
float angulo_medido_r_l (){
  float angulo_z;
  //angulo como resultado de diferencia. IMPORTANTE. Se usan las variables obtenidas de los IMUS, y se tiene que trabajar con las mismas. Sujeto a cambio.
  angulo_z=abs((ang_z2-ang_z1));
  //entrega el resultado a la funcion principal;
  return angulo_z;
    
}
//funcion para obtener angulo final como diferencia de los angulos medidos en ambos IMUS. Este mide la rotacion en eje X.
float angulo_medido_f_e (){
 
  float angulo_x;
    //angulo como resultado de diferencia. IMPORTANTE. Se usan las variables obtenidas de los IMUS, y se tiene que trabajar con las mismas. Sujeto a cambio.
  angulo_x=(ang_x2-ang_x1);
  //entrega el resultado a la funcion principal;
  return angulo_x;
}


// funcion obtiene la medicion del dolor a partir del funcionamiento del encoder. Revisar funcionamiento https://create.arduino.cc/projecthub/vandenbrande/arduino-rotary-encoder-simple-example-ky-040-b78752
//Regular hasta que medicion pueda realizarse de 0 a 10.
int dolor_medido(){
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


//Funcion que controla el ciclado de menu 1. La primera parte es el debouncing. ATENCION, NO FUNCIONA EN TINKERCAD, no se si se deba a un error del mismo programa o a algo del mismo código.
//el error se manifiesta como una de las variables quedándose atascada en 1 y pasando rápido por las pantallas del menu de toma de muestra.
//preferentemente cambiar por alguna función de librería. 

void botonguardar1(){
//todo esto es el debouncing
  //se verifica el cambio de estado. Los botones pueden estar prendidos o apagados, variable que lee el arduino va a estar en 1 o en 0.
  //funcion estadoActual mide lo que lee el arduino del botón. Empieza igual que ultimoCambioEstado que por descripcion en el switch empieza con 0.
  estadoActual3 = digitalRead(BOTON_OK);
    Si estadoActual y ultimoCambioEstado son distintos siendo el primero 1 (boton se presiono) y el segundo 0, por indicacion inicial.
    if (estadoActual3 != ultimoCambioEstado3) {
      //se guarda un valor de tiempo
    ultimoTiempoDebounce3 = millis();
    //estado de ultimoCambioEstado cambia de 0 a 1. Esto también va a cambiar de 1 a 0 cuando el boton se deje de presionar, siguiendo el cambio en estadoActual.
    ultimoCambioEstado3 = estadoActual3;
  }
  //Se utiliza el contador definido en la linea anterior para comparar con el tiempo pasado. Si hay una diferencia de tiempo mayor al tiempo del boton presionado, se considera presionado. Es importante hacer el debounce porque sin eso el boton oscila muy rapido entre prendido y apagado.
  if ((millis() - ultimoTiempoDebounce3) > RETRASO_DEBOUNCE) {
    //Si se considera que el boton se presiono y se dejo de presionar se realiza la accion para la cual se presiona el boton.
    if(ultimoEstadoEstable3 == LOW && estadoActual3 == HIGH)      
      //en este caso lo que está haciendo es guardar el valor del ángulo medido en la flexion en la variable guardar_flex, y el valor del dolor marcado por el encoder en ese momento, en la variable guardar_dolor, aumenta el numero de la variable que controla el menu en 1 y resetea el menu para que se puedan medir las variables siguientes, en este caso extension
      if (ultimoEstadoEstable3 != estadoActual3){ 
          guardar_flex=a_fl;
          guardar_dolor_f=dolor;     
          cambio_pantalla_1= cambio_pantalla_1+1;

    }
    //se resetea el ultimoEstadoEstable para futura función.
    ultimoEstadoEstable3 = estadoActual3;
  }
}


//igual que el anterior, solo que guarda la funcion de extension.
void botonguardar2(){

  estadoActual3 = digitalRead(BOTON_OK);  
    if (estadoActual3 != ultimoCambioEstado3) {
    ultimoTiempoDebounce3 = millis();
    ultimoCambioEstado3 = estadoActual3;
  }
  if ((millis() - ultimoTiempoDebounce3) > RETRASO_DEBOUNCE) {
    if(ultimoEstadoEstable3 == LOW && estadoActual3 == HIGH)      
      if (ultimoEstadoEstable3 != estadoActual3){ 
          guardar_ext=a_ex;
          guardar_dolor_e=dolor;               
          cambio_pantalla_1= cambio_pantalla_1+1;
  
    }
    ultimoEstadoEstable3 = estadoActual3;
  }
}

//igual que el anterior, guarda flexion lateral derecha. Borrar si se quita para el preliminar
void botonguardar3(){

  estadoActual3 = digitalRead(BOTON_OK);  
    if (estadoActual3 != ultimoCambioEstado3) {
    ultimoTiempoDebounce3 = millis();
    ultimoCambioEstado3 = estadoActual3;
  }
  if ((millis() - ultimoTiempoDebounce3) > RETRASO_DEBOUNCE) {
    if(ultimoEstadoEstable3 == LOW && estadoActual3 == HIGH)      
      if (ultimoEstadoEstable3 != estadoActual3){ 
          guardar_fld=a_fld;
          guardar_dolor_r=dolor;     
          cambio_pantalla_1= cambio_pantalla_1+1;

    }
    ultimoEstadoEstable3 = estadoActual3;
  }
}

//igual que el anterior, guarda flexion lateral izquierda. Borrar si se quita para el preliminar
void botonguardar4(){

  estadoActual3 = digitalRead(BOTON_OK);  
    if (estadoActual3 != ultimoCambioEstado3) {
    ultimoTiempoDebounce3 = millis();
    ultimoCambioEstado3 = estadoActual3;
  }
  if ((millis() - ultimoTiempoDebounce3) > RETRASO_DEBOUNCE) {
    if(ultimoEstadoEstable3 == LOW && estadoActual3 == HIGH)      
      if (ultimoEstadoEstable3 != estadoActual3){ 
          guardar_fli=a_fli;
          guardar_dolor_l=dolor;     
          cambio_pantalla_1= cambio_pantalla_1+1;

    }
    ultimoEstadoEstable3 = estadoActual3;
  }
}


//menu2access llama a los dos botones que controlan la variable que manipula el segundo menu. Fue lo que les mostre en tinkercad en la tarde. Por alguna razon, usando la misma funcion no hay problemas de funcionamiento aqui. botonmas aumenta la variable y botonmenos la disminuye

void menu2access (){
  botonmas2 ();
  botonmenos ();
}

//Es la misma funcion que no funciona arriba, para hacer el debouncing pero por alguna razon funciona aqui. Al presionarlo disminuye la variable de control del menu, cambio_pantalla_2, en 1. Si variable disminuye a menos de 1, se coloca 4 automaticamente para dar la impresion de menu. Cambiar ese 4 por 2 si se borran las mediciones de flexion lateral.
void botonmenos(){
  estadoActual2 = digitalRead(BOTON_MENOS);

  if (estadoActual2 != ultimoCambioEstado2) {
    ultimoTiempoDebounce2 = millis();
    ultimoCambioEstado2 = estadoActual2;
  }
  if ((millis() - ultimoTiempoDebounce2) > RETRASO_DEBOUNCE)  {
    if(ultimoEstadoEstable2 == LOW && estadoActual2 == HIGH)      
      if (ultimoEstadoEstable2 != estadoActual2){
      cambio_pantalla_2= cambio_pantalla_2-1;
       if (cambio_pantalla_2<1){
         cambio_pantalla_2=4;
          }
      menu2();         
    }
    ultimoEstadoEstable2 = estadoActual2;
  }    
}

//Hace lo mismo que el otro solo que aumenta la variable de control en 1. Si la variable aumenta a mas de 4, esta programado para regresar a 1. Cambiar ese 4 por 2 si se borran las mediciones de flexion lateral.
void botonmas2(){

  estadoActual1 = digitalRead(BOTON_MAS);  
  if (estadoActual1 != ultimoCambioEstado1) {
    ultimoTiempoDebounce1 = millis();
    ultimoCambioEstado1 = estadoActual1;
  }
  if ((millis() - ultimoTiempoDebounce1) > RETRASO_DEBOUNCE) {
    if(ultimoEstadoEstable1 == LOW && estadoActual1 == HIGH)      
      if (ultimoEstadoEstable1 != estadoActual1){
        cambio_pantalla_2= cambio_pantalla_2+1;
        if (cambio_pantalla_2>4){
          cambio_pantalla_2= 1;
        }      
      menu2(); 
    }    
    ultimoEstadoEstable1 = estadoActual1;
  }
}


//Funcion de menu. Utiliza el cambio_pantalla_2 como variable de control, y se actualiza cada vez que se presiona alguno de los dos botones.
void menu2(){
  lcd.clear ();
  switch (cambio_pantalla_2){
    case 1:{
      //muestra flexion y el valor grabado de flexion
      lcd.print ("Flexion: ");
      lcd.print (guardar_flex);
      lcd.setCursor (0,1);
      //muestra dolor en el movimiento y valor grabado anteriormente
      lcd.print ("Dolor:");
      lcd.print (guardar_dolor_f);
      lcd.print ("/10");
      break;
    }
    //los otros casos son iguales, borrar caso 3 y 4 si ya no se trabaja con flexion lateral.
    case 2:{
      lcd.print ("Extension: ");
      lcd.print (guardar_ext);
      lcd.setCursor (0,1);
      lcd.print ("Dolor:");
      lcd.print (guardar_dolor_e);
      lcd.print ("/10");
      break;
    }
    case 3:{
      lcd.print ("Flexion Der: ");
      lcd.print (guardar_fld);
      lcd.setCursor (0,1);
      lcd.print ("Dolor:");
      lcd.print (guardar_dolor_r);
      lcd.print ("/10");
      break;
    }
    case 4:{
      lcd.print ("Flexion Izq: ");
      lcd.print (guardar_fli);
      lcd.setCursor (0,1);
      lcd.print ("Dolor:");
      lcd.print (guardar_dolor_l);
      lcd.print ("/10");
      break;
    }
  }
}
