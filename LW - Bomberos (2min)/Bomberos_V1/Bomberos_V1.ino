int ledDone = 12;     //Green led 
int doorStatus = 35; //Door status
int master = 34;      //ON-OFF
int ledFlag = 14;     //Red led
int ledVent = 27;     //Yellow led
int lights1 = 5;     //Relay Luz AC;
int vent = 18;       //Relay Extractor AC

//Parameters

long int t1 = 80000; //Time of light exposure: 2min
long int msecs = 0;   //Time of action


bool masterStatus = false; //Button On/OFF

void setup() {
 
  
  Serial.begin(115200); 
  pinMode(ledDone, OUTPUT);
  pinMode(doorStatus, INPUT);
  pinMode(master, INPUT);
  pinMode(ledFlag, OUTPUT);
  pinMode(ledVent, OUTPUT);
  pinMode(lights1, OUTPUT);
  pinMode(vent, OUTPUT);
  //Each system must start OFF whe plugged in
  
  digitalWrite(lights1, LOW);
  digitalWrite(vent, LOW);  

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
    
    digitalWrite(lights1, LOW);
    digitalWrite(vent, LOW);
    
    //LED Status

    digitalWrite(ledDone, HIGH);
    digitalWrite(ledFlag, LOW);
    digitalWrite(ledVent, LOW);
    }

   // E2: Door is not closed

  if(digitalRead(doorStatus) == LOW){

    Serial.print("E2 \n");

    //Systems are OFF or gotta be turned OFF
    
    digitalWrite(lights1, LOW);  
   
    //LED Status

    digitalWrite(ledDone, LOW);
    digitalWrite(ledFlag, HIGH);
    }

  if(digitalRead(doorStatus)==HIGH and masterStatus == false){
    digitalWrite(lights1, LOW);
    digitalWrite(vent, LOW); 
   
    //LED Status

    digitalWrite(ledDone, HIGH);
    digitalWrite(ledFlag, LOW);
    digitalWrite(ledVent, LOW);
    } 
  
  //E3 Cycle starts: door is closed, master is pressed, t = 0

  if(digitalRead(doorStatus) == HIGH && masterStatus==true && msecs == 0){
    
    Serial.print("E3 \n");
    
    msecs += 1; //first millisecond is added to control
    delay(1);
    
    digitalWrite(lights1, HIGH);
    digitalWrite(vent, LOW); 

    //LED Status: Red light adverting that the machine is working

    digitalWrite(ledDone, LOW);
    digitalWrite(ledFlag, HIGH);
    digitalWrite(ledVent, LOW);
    }

  // E4 Cycle is running, lights ON, ventilation OFF
  
  if(digitalRead(doorStatus) == HIGH && masterStatus==true && msecs > 0 && msecs < t1){
    
    Serial.print("E4 \n");

    digitalWrite(lights1,HIGH);
    digitalWrite(vent, HIGH);  

    //LED Status: Red light adverting that the machine is working

    digitalWrite(ledDone, LOW);
    digitalWrite(ledFlag, HIGH);
    digitalWrite(ledVent, LOW);
    msecs += 1; //millisecond is added to control
    delay(1);
    }

 // E5 Cycle is running, transitions from lights to ventilation

  if(digitalRead(doorStatus) == HIGH && masterStatus==true && msecs == t1){

    Serial.print("E5 \n");
    
    digitalWrite(lights1, LOW);
    digitalWrite(vent, LOW); 

    //LED Status, Lights Stops, Yellow led is on.

    digitalWrite(ledDone, HIGH);
    digitalWrite(ledFlag, LOW);
    digitalWrite(ledVent, LOW);
    } 
}
