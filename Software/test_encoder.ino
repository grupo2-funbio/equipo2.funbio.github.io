  #define CLK    12
  #define DT     11
  #define SW     10

  int counter = 0; int currentCLK; int previousCLK; 
  int final_counter =0;
  int value;
  void setup()
  {  
    pinMode(CLK,INPUT); pinMode(DT,INPUT); pinMode(SW,INPUT);
    Serial.begin(9600);    
    previousCLK = digitalRead(CLK);
  } 
  //=========================================================
  void loop()
  {
    value=get_function ();    
    Serial.print (value);
  }
  
 int get_function (){   
    currentCLK = digitalRead(CLK);
    if(currentCLK != previousCLK){       
      if(digitalRead(DT) != currentCLK)
      { 
        counter++;
      }
      else
      {
        counter--; 
      }
      final_counter = final_counter + counter;
      if (final_counter<0){
        final_counter=0;      
      }
      if (final_counter>10){
        final_counter=10;
      }
    }
    previousCLK = currentCLK; 
    return final_counter; 
  }
