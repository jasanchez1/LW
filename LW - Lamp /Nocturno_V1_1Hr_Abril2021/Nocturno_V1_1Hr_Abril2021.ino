int movementSensor = 17;  //Door status
int lights = 5;
int lightsA = 19; //Relay Luz AC
int lightsB = 18; //Relay Luz AC

//Parameters

long int t1 = 3604000; //Time of light exposure
long int msecs = 0;
void setup() {

  Serial.begin(115200); 

  pinMode(lights, OUTPUT);
  pinMode(lightsA, OUTPUT);
  pinMode(lightsB, OUTPUT);

  //Each system must start OFF when plugged in
  
  digitalWrite(lights, LOW);
  digitalWrite(lightsA, LOW);
  digitalWrite(lightsB, LOW);  

Serial.print("START");
delay(60000);

}

void loop() {
  if(msecs < t1){
    msecs += 1;
    delay(1);
    }

  if(digitalRead(movementSensor) == HIGH){
    digitalWrite(lights, LOW); 
    digitalWrite(lightsA, LOW);
    digitalWrite(lightsB, LOW);  
    delay(10000);
    Serial.print("LOW");
    } 

 
 if(digitalRead(movementSensor) == LOW && msecs < t1){
  digitalWrite(lights, HIGH);
  digitalWrite(lightsA, HIGH);
  digitalWrite(lightsB, HIGH);  
  Serial.print("HIGH");
    }

 if(msecs == t1 || msecs > t1){
  digitalWrite(lights, LOW);
  digitalWrite(lightsA, LOW);
  digitalWrite(lightsB, LOW);  
  Serial.print("LOW");
    }  
}
