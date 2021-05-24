
//Outputs

int ledDone = 12;      //Green led: Indicates when the system is ON
int ledWarning = 14;   //Yellow led: indicates a safety sensor was triggered
int ledModeOpen = 27;  //Led which indactes Mode Close is Running
int ledModeClose = 21; //Led which indactes Mode Open is Running

//Inputs 

int modeOpen = 35;     //Triggers mode Open
int modeClose = 34;    //Triggers mode Close
int master = 23;       //ON-OFF
int microswitch = 16;  //Triggers security mesures when the doors are opened in an unintended moment
int movement = 17;     //Triggers security mesures when movement is detected in an unintended moment
                      
//AC Relays

int lightsA = 5;       //Relay Lights 72W
int lightsB = 19;      //Relay Lights 72W
int air = 18;  //Relay DC Electromechanic

//Parameters

bool safety = true;           //Turns true when there isn't safety sensors triggered
bool ventilation = false;          //Turns true when ventilation are supposed to be working
bool lights = false;          //Turns true when lights are supposed to be working
bool masterStatus = false;    //Represents weather the Master Button is in HIGH status or in LOW status
bool modeOpenStatus = false;  //Represents weather the Open Status is in HIGH status or in LOW status
bool modeCloseStatus = false; //Represents weather the Close Status is in HIGH status or in LOW status

//Time control

long int tOpen = 134400;     //Time of light exposure (10 minutes)
long int msecs = 0;           //General time of action
long int tpulse = 0;          //Time pulse
long int await = 14000;       // Await for Open Mode
long int tawait = 0;          // Time await control
int functionPulse;            // makes a led pulse


void setup() {

  //Serial monitor 
  
  Serial.begin(115200); 

  //Setting outputs 
  
  pinMode(ledDone, OUTPUT);
  pinMode(ledWarning, OUTPUT);
  pinMode(ledModeOpen, OUTPUT);
  pinMode(ledModeClose, OUTPUT);
  pinMode(lightsA, OUTPUT);
  pinMode(lightsB, OUTPUT);
  pinMode(air, OUTPUT);
  
  //Setting inputs

  pinMode(modeOpen, INPUT);
  pinMode(modeClose, INPUT);
  pinMode(master, INPUT);
  pinMode(microswitch, INPUT);
  pinMode(movement, INPUT);

  //Each system must start OFF whe plugged in
  
  digitalWrite(lightsA, LOW); 
  digitalWrite(ventilation, LOW); 

   //Led status: Ready to open or start

   digitalWrite(ledDone, LOW);
   digitalWrite(ledWarning, LOW);
   digitalWrite(ledModeOpen, LOW);
   digitalWrite(ledModeClose, LOW);

}

void loop(){

Serial.print(msecs, DEC);
Serial.print("\n");
  

// E1: Master button setup

if(digitalRead(master) == HIGH){
  Serial.print("\n E1 high");
  masterStatus = true;}

if(digitalRead(master) == LOW){
  Serial.print("\n E1 low");
  masterStatus = false;
  digitalWrite(lightsA, LOW);
  digitalWrite(lightsB, LOW);
  digitalWrite(air, LOW);
  modeOpenStatus = false;
  modeCloseStatus = false;
  msecs = 0;
  tawait = 0;
  }


 if(digitalRead(modeOpen) == HIGH && modeOpenStatus == false && modeCloseStatus == false){
  
    modeOpenStatus = true;
    digitalWrite(ledModeOpen, HIGH);
    digitalWrite(ledDone, LOW);
    delay(2000);
    }

  else if (digitalRead(modeOpen) == HIGH && modeOpenStatus == true){

    digitalWrite(lightsA, LOW);
    digitalWrite(lightsB, LOW);
    digitalWrite(air, LOW);
    modeOpenStatus = false;
    modeCloseStatus = false;
    msecs = 0;
    tawait = 0;
    digitalWrite(ledModeOpen, LOW);
    digitalWrite(ledDone, HIGH);
    delay(2000);
    
    }

 if(digitalRead(modeClose) == HIGH && modeCloseStatus == false && modeOpenStatus == false){
  
    modeCloseStatus = true;
    digitalWrite(ledModeClose, HIGH);
    digitalWrite(ledDone, LOW);
    modeOpenStatus = false;
    delay(2000);
    }

  else if (digitalRead(modeClose) == HIGH && modeCloseStatus == true){

    modeCloseStatus = false;
    digitalWrite(lightsA, LOW);
    digitalWrite(lightsB, LOW);
    digitalWrite(air, LOW);
    digitalWrite(ledModeClose, LOW);
    digitalWrite(ledDone, HIGH);
    delay(2000);
    
    }
 
// E2: Pulse LED'S Behavior wheng plugged in, but not turned ON

if(masterStatus == true && modeCloseStatus == false && modeOpenStatus == false){

  Serial.print("\n E2.1");

  digitalWrite(ledModeOpen, LOW);
  digitalWrite(ledModeClose, LOW);
  digitalWrite(ledDone, HIGH);
  digitalWrite(ledWarning, LOW);
  
} else if(masterStatus == false){
  Serial.print("\n E2.2");
  Serial.print("\n tpulse:");
  Serial.print(tpulse, DEC);
  Serial.print("\n");
  
  lights = false;
  ventilation = false;
  modeOpenStatus = false;
  modeCloseStatus = false;

  if(tpulse <= 100){
    tpulse += 1;
    digitalWrite(ledModeOpen, HIGH);
    digitalWrite(ledModeClose, LOW);
    digitalWrite(ledDone, LOW);
    digitalWrite(ledWarning, LOW);
    
  } else if(tpulse > 100 && tpulse <= 200){
    
    tpulse += 1;
    digitalWrite(ledModeOpen, LOW);
    digitalWrite(ledModeClose, HIGH);
    digitalWrite(ledDone, LOW);
    digitalWrite(ledWarning, LOW);
    
  } else if(tpulse > 200 && tpulse <= 300){
    
    tpulse += 1;
    digitalWrite(ledModeOpen, LOW);
    digitalWrite(ledModeClose, LOW);
    digitalWrite(ledDone, HIGH);
    digitalWrite(ledWarning, LOW);
    
  } else if(tpulse > 300 && tpulse < 400){
    
    tpulse += 1;
    digitalWrite(ledModeOpen, LOW);
    digitalWrite(ledModeClose, LOW);
    digitalWrite(ledDone, LOW);
    digitalWrite(ledWarning, HIGH);
  } else {
    
    tpulse=0;
    digitalWrite(ledModeOpen, LOW);
    digitalWrite(ledModeClose, LOW);
    digitalWrite(ledDone, LOW);
    digitalWrite(ledWarning, LOW);
  }
  
} else {
  Serial.print("\n E2.3");
  digitalWrite(ledDone, LOW);
}

// E3: Seting up turn on and turn off of Relays

if(lights == true){
  Serial.print("\n E3.1");
  digitalWrite(lightsA, HIGH);
  digitalWrite(lightsB, HIGH);
  
} else {

  Serial.print("\n E3.2");
  digitalWrite(lightsA, LOW);
  digitalWrite(lightsB, LOW);
}

if(ventilation == true){

  Serial.print("\n E3.3");
  digitalWrite(air, HIGH);

} else {

  Serial.print("\n E3.4");
  digitalWrite(air, LOW);
}

//Setting up functions operations

// E4: Mode Open set up

if(modeOpenStatus == true){ //Mode open begins 

  Serial.print("\n E4.1");
  digitalWrite(ledModeOpen, HIGH);
  digitalWrite(ledModeClose, LOW);
  digitalWrite(ledDone, LOW);
  digitalWrite(ledWarning, LOW);
}

// E5: Mode Close set up

if(modeCloseStatus == true){ //Mode close begins

  Serial.print("\n E5.1");
  digitalWrite(ledModeClose, HIGH);
  digitalWrite(ledModeOpen, LOW);
  digitalWrite(ledDone, LOW);
  digitalWrite(ledWarning, LOW);  
} 
  

// E6 Safety readings

if(digitalRead(movement)== HIGH && modeOpenStatus == true && tawait > await){

  Serial.print("\n E6.1");
  safety = false;
  digitalWrite(ledWarning, HIGH);
  
} else if(digitalRead(microswitch) == LOW && modeCloseStatus == true){

  Serial.print("\n E6.2");
  safety = false;
  digitalWrite(ledWarning, HIGH);
  
} else {

  Serial.print("\n E6.3");
  safety = true;
  digitalWrite(ledWarning, LOW);
}

// E7 Safety mesures: Everything gotta be off

if(safety == false){

  Serial.print("\n E7.1");
  lights = false;
  ventilation = false;
}

if(modeCloseStatus == true && safety){

  Serial.print("\n E7.2");
  lights = true;
  ventilation =  true; 
  
} else if (modeCloseStatus== false && modeOpenStatus == false){

  Serial.print("\n E7.3");
  lights = false;
  ventilation =  false; 
  
}

if(modeOpenStatus == true && msecs == 0 && tawait <= await && digitalRead(microswitch) == LOW) {

  Serial.print("\n E7.4");
  tawait += 1;
  lights = false; 
  ventilation = false;
  if (functionPulse <= 70 ){

    functionPulse += 1;
    digitalWrite(ledModeOpen, LOW);
    
    } else if(functionPulse > 70 && functionPulse < 140) {

      functionPulse += 1;
      digitalWrite(ledModeOpen, HIGH);
    } else {
      
      functionPulse = 0;
      }

} else if (modeOpenStatus == true && msecs == 0 && tawait > await && digitalRead(microswitch) == HIGH && safety) {

  Serial.print("\n E7.5");
  digitalWrite(ledModeOpen, HIGH);
  digitalWrite(ledWarning, LOW);
  msecs += 1;
  
  
  } else if(modeOpenStatus == true && msecs <= tOpen && tawait > await && safety == true && digitalRead(microswitch) == LOW) {

  Serial.print("\n E7.6");
  msecs += 1;
  lights = true; 
  ventilation = true;
  digitalWrite(ledWarning, LOW);
  
} else if(modeOpenStatus == true && msecs > tOpen && safety == true){

  Serial.print("\n E7.7");
  lights = false;
  ventilation = false;
  modeOpenStatus = false;
  msecs = 0;
  tawait = 0;
  digitalWrite(ledWarning, LOW);
  
 } else if (modeOpenStatus == true && msecs == 0 && tawait < await && digitalRead(microswitch) == HIGH && safety) {

  Serial.print("\n E7.5");
  digitalWrite(ledModeOpen, HIGH);
  digitalWrite(ledWarning, HIGH);
    
 
  }
  
}
