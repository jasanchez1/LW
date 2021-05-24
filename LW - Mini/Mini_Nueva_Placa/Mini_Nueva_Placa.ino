int ledDone = 12;     //Green led 
int unlockButton = 35;//Door unlock button 
int doorStatus = 23;  //Door status
int master = 34;      //ON-OFF
int ledFlag = 27;     //Red led
int ledVent = 14;     //Yellow led
int lights = 5;       //Relay Luz AC
int ventilation = 19; //Relay Extractor AC
int lock = 18;         //Relay DC Electromechanic

//Parameters

long int t1 = 80000; //Time of light exposure: 2 min
long int t2 = 120000; //Total time of action, including air system
long int msecs = 0;   //Time of action
bool masterStatus = false; //Helps restarting a cycle
bool unlocked = false;
void setup() {

  Serial.begin(115200); 
  pinMode(ledDone, OUTPUT);
  pinMode(unlockButton, INPUT);
  pinMode(doorStatus, INPUT);
  pinMode(master, INPUT);
  pinMode(ledFlag, OUTPUT);
  pinMode(ledVent, OUTPUT);
  pinMode(lights, OUTPUT);
  pinMode(ventilation, OUTPUT);
  pinMode(lock, OUTPUT);

  //Each system must start OFF whe plugged in
  
  digitalWrite(lights, LOW); 
  digitalWrite(ventilation, LOW); 
  digitalWrite(lock, LOW);

   //Led status: Ready to open or start

   digitalWrite(ledDone, HIGH);
   digitalWrite(ledFlag, LOW);
   digitalWrite(ledVent, LOW);

}

void loop() {

  if(digitalRead(master) == HIGH){
    masterStatus = true;
    }

  else if (digitalRead(master) == LOW){
    masterStatus = false;
    
    }
  
  Serial.print(msecs, DEC);
  Serial.print(" msecs \n");

  // E1: Master is LOW (Button in OFF)

  if(masterStatus == false){

    Serial.print("E1 \n");

    msecs = 0; //Time gotta be restarted or stay in 0

    //Systems are OFF or gotta be turned OFF
    
    digitalWrite(lights, LOW); 
    digitalWrite(ventilation, LOW); 


    if(msecs > 0 && msecs <t2 && digitalRead(doorStatus) == HIGH){
      msecs += 1;
      }

    //LED Status

    digitalWrite(ledDone, HIGH);
    digitalWrite(ledFlag, LOW);
    digitalWrite(ledVent, LOW);
    }

   // E2: Door is not closed

  if(digitalRead(doorStatus) == HIGH && msecs == (t1 - 10000) || msecs == t2){

    Serial.print("E2 \n");

    //Systems are OFF or gotta be turned OFF
    
    digitalWrite(lights, LOW); 
    digitalWrite(ventilation, LOW); 
   

    //LED Status
    if (msecs==0 | msecs==t2){
    masterStatus = false;
    
    
    digitalWrite(ledDone, HIGH);
    digitalWrite(ledFlag, LOW);
    digitalWrite(ledVent, LOW);}
    }

    else if(digitalRead(doorStatus) == HIGH && msecs < t1){
      digitalWrite(ledDone, LOW);
      digitalWrite(ledFlag, LOW);
      digitalWrite(ledVent, HIGH);
      digitalWrite(lights, LOW); 
      digitalWrite(ventilation, LOW); 
      
      }

  //E3 Cycle starts: door is closed, master is pressed, t = 0

  if(digitalRead(doorStatus) == LOW && masterStatus==true && msecs == 0){
    
    Serial.print("E3 \n");
    
    msecs += 1; //first millisecond is added to control
    delay(1);
    
    digitalWrite(lights, HIGH); 
    digitalWrite(ventilation, LOW); 

    //LED Status: Red light adverting that the machine is working

    digitalWrite(ledDone, LOW);
    digitalWrite(ledFlag, HIGH);
    digitalWrite(ledVent, LOW);
    }

  // E4 Cycle is running, lights ON, ventilation OFF
  
  if(digitalRead(doorStatus) == LOW && masterStatus==true && msecs > 0 && msecs < t1){
    
    Serial.print("E4 \n");

    digitalWrite(lights, HIGH); 
    digitalWrite(ventilation, LOW); 

    //LED Status: Red light adverting that the machine is working

    digitalWrite(ledDone, LOW);
    digitalWrite(ledFlag, HIGH);
    digitalWrite(ledVent, LOW);
    msecs += 1; //millisecond is added to control
    delay(1);
    }

 // E5 Cycle is running, transitions from lights to ventilation

  if(digitalRead(doorStatus) == LOW && masterStatus==true && msecs == t1){

    Serial.print("E5 \n");
    
    msecs += 1; //millisecond is added to control
    
    digitalWrite(lights, LOW); 
    digitalWrite(ventilation, HIGH); 

    //LED Status, Lights Stops, Yellow led is on.

    digitalWrite(ledDone, LOW);
    digitalWrite(ledFlag, LOW);
    digitalWrite(ledVent, HIGH);
    }

  //E6: Cycling in ventilation

  if(digitalRead(doorStatus) == LOW && masterStatus==true && msecs > t1 && msecs < t2){

    Serial.print("E6 \n");
    digitalWrite(lights, LOW); 
    digitalWrite(ventilation, HIGH);
  
    msecs += 1; //first millisecond is added to control
    delay(1);

    //LED Status, Lights Stops, Yellow led is on.

    digitalWrite(ledDone, LOW);
    digitalWrite(ledFlag, LOW);
    digitalWrite(ledVent, HIGH);
    }
    if(unlocked == false && masterStatus==true && msecs > t1 && msecs < t2){

    Serial.print("E7 \n");
    digitalWrite(lights, LOW); 
    digitalWrite(ventilation, HIGH);
  
    msecs += 1; //first millisecond is added to control
    delay(1);

    //LED Status, Lights Stops, Yellow led is on.

    digitalWrite(ledDone, LOW);
    digitalWrite(ledFlag, LOW);
    digitalWrite(ledVent, HIGH);
    }

  if(digitalRead(unlockButton) == HIGH && msecs > t1 ){
    unlocked = true;
    
    digitalWrite(ledDone, LOW);
    digitalWrite(ledFlag, LOW);
    digitalWrite(ledVent, LOW);

    digitalWrite(ledDone, HIGH);
    digitalWrite(ledFlag, LOW);
    digitalWrite(ledVent, LOW);

    
    unlocked = false;} 

  //E8: Stops cycling naturally, t = t2

  if(digitalRead(doorStatus) == LOW && masterStatus==true && msecs == t2){

    Serial.print("E8 \n");
    
    //Systems are OFF or gotta be turned OFF
    
    digitalWrite(lights, LOW); 
    digitalWrite(ventilation, LOW); 

    //LED Status, Lights Stops, Yellow led is on.

    digitalWrite(ledDone, HIGH);
    digitalWrite(ledFlag, LOW);
    digitalWrite(ledVent, LOW);
    
    }

      
  if(digitalRead(unlockButton) == HIGH && msecs > t1){

    Serial.print("E11 \n");

    digitalWrite(lock, HIGH); 
    delay(1000);
    digitalWrite(lock, LOW);
  }

  if(digitalRead(unlockButton) == HIGH && msecs == 0){

    Serial.print("E11 \n");

    digitalWrite(lock, HIGH); 
    delay(1000);
    digitalWrite(lock, LOW);
  } 

}
