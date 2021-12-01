int cycle_screen=0;
float st1, st3;
int sv4, sv2, value;
long output;
float test1=0, test3=0;

void setup() {
  pinMode (8, INPUT_PULLUP);
  pinMode (9, INPUT_PULLUP);
  pinMode (10, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  if(cycle_screen==0){
    float value1= analogRead (A3)/10;
      if(test1<value1){
      test1=value1;
    }
    int value2= analogRead (A3)/100;
    Serial.print ("flexion");
    Serial.print (" ");
    Serial.print (test1);
    Serial.print (" ");
    Serial.println (value2);
    value = digitalRead (8);    
    if (value==LOW){
      Serial.print ("pressed");      
      st1=test1;
      sv2=value2;  
      delay(500); 
      cycle_screen++;          
      }
    }
  
  if(cycle_screen==1){

    float value3= analogRead (A3)/10;
    if(test3<value3){
      test3=value3;
    }
    int value4 = analogRead (A3)/100;

    Serial.print ("extension");
    Serial.print (" ");
    Serial.print (test3);
    Serial.print (" ");
    Serial.println (value4);
    value = digitalRead (8);
    if (value==LOW){
      st3=test3;
      sv4=value4;
      cycle_screen++;
      delay(500);     
    }
  }   

  if (cycle_screen==2){
    Serial.print (st1);
    Serial.print ("\t");
    Serial.print (sv2);
    Serial.print ("\t");
    Serial.print (st3);
    Serial.print ("\t");
    Serial.print (sv4);
    Serial.println ();

  }

}
