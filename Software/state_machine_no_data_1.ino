int cycle_screen=1;
float st1, st3;
int sv4, sv2, value, valueminus;
int test1, value2, test3, value4; 
bool change;
int test=0; 
 
void setup() {
  declare_input_1 ();
  declare_input_2 ();
  Serial.begin(9600);
}
 
void loop() {
    state_machine();
}
 
void state_machine(){  
  switch (cycle_screen) {    
    case 1:
 
      value= get_value();
      test1 = test_value(value);  
      display_values_flex(test1);  
      if (digitalRead(10)==LOW){     
        st1=test1;
        test=0;
        delay (500);  
        cycle_screen=2;                 
        } 
      break; 
 
    case 2:
      value2= get_pain();
      display_values_f_p (value2);
      if (digitalRead(10)==LOW){
         sv2=value2;
         delay(500);
         cycle_screen=3;
         }
       break;
 
    case 3:
      value= get_value();
      test3 = test_value(value);  
      display_values_ext(test3);  
      if (digitalRead(10)==LOW){    
        st3=test3;
        test=0;  
        delay(500); 
        cycle_screen=4;
        }
       break;
 
    case 4:
      value4= get_pain();
      display_values_e_p (value4);
      if (digitalRead(10)==LOW){
         sv4=value4;
         delay(500);
         cycle_screen=5;
         }
       break;
 
    case 5:
      release_data_python(st1, sv2, st3, sv4);
      if (digitalRead(8)==LOW){
        cycle_screen=6;
        delay(500);
      } 
      break;
 
    case 6:
      display_saved_data_flex (st1,sv2);
      change = digitalRead (8);
      if (digitalRead(8)==LOW){
        cycle_screen++;
        delay (500);
      }
      break;    
 
    case 7:
      display_saved_data_ext (st3,sv4);
      if (digitalRead(9)==LOW){
      if (valueminus==LOW){
        cycle_screen--;
        delay (500);
      }
      break;
  }
}
}
 
 
void declare_input_1 (){
  pinMode (8, INPUT_PULLUP);
  pinMode (9, INPUT_PULLUP);  
}
 
void declare_input_2 (){
  pinMode (10, INPUT_PULLUP);   
}
 
int get_value (){
  int value;
  value=analogRead (A3)/10;
  return value;  
}
 
int test_value(int value){
  if(test<value){
  test=value;
  return test; 
  } 
}
 
int get_pain (){
  int pain= analogRead (A3)/100;
  return pain;
}
 
void display_values_flex(int test){
    Serial.print ("flexion");
    Serial.print (" ");
    Serial.println (test);
}
 
void display_values_f_p (int value){
    Serial.print ("Dolor Flexion:");
    Serial.print (" ");
    Serial.println (value);
}
 
void display_values_ext(int test){
    Serial.print ("extension");
    Serial.print (" ");
    Serial.println (test);
}
 
void display_values_e_p (int value){
    Serial.print ("Dolor Extension:");
    Serial.print (" ");
    Serial.println (value);
}
 
 
void release_data_python(int st1, int sv2, int st3, int sv4 ){
    Serial.print (st1);
    Serial.print (",");
    Serial.print (sv2);
    Serial.print (",");
    Serial.print (st3);
    Serial.print (",");
    Serial.println (sv4);
 
}
 
void display_saved_data_flex (int st1,int sv2){
    Serial.print ("datos flexion");
    Serial.print (" || ");
    Serial.print (st1);
    Serial.print (" ");
    Serial.println (sv2);
}
 
void display_saved_data_ext (int st3,int sv4){
    Serial.print ("datos extension");
    Serial.print (" || ");
    Serial.print (st3);
    Serial.print (" ");
    Serial.println (sv4);
}
