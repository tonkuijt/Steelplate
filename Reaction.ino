/* Knock Sensor

 * ----------------

 *

 * Program using a Piezo element as if it was a knock sensor.

 *

 * We have to basically listen to an analog pin and detect 

 * if the signal goes over a certain threshold. It writes

 * "knock" to the serial port if the Threshold is crossed,

 * and toggles the LED on pin 13.

 *

 * (cleft) 2005 D. Cuartielles for K3

 * edited by Scott Fitzgerald 14 April 2013

 */



int ledPin = 13;

int knockSensor = 0;               

byte val = 0;

int statePin = LOW;

int THRESHOLD = 20;



void setup() {

 pinMode(ledPin, OUTPUT);
 pinMode(4, OUTPUT);
 digitalWrite(4, LOW); 

 Serial.begin(9600);
 Serial.println("Program started");

}


int count = 0;

void loop() {
  
// Wait 10 secs for reload
// Slow LED for reload
Serial.println("10 seconds for reload...");
for (int a = 0; a < 5 ; a+=1){
  digitalWrite(4, HIGH);
  delay(1000);
  digitalWrite(4, LOW);
  delay(1000);
}

// Fast led for READY sugnal

int blin=0;
Serial.println("Get ready...");

while (blin < 10) {
  digitalWrite(4,HIGH);
  delay(200);
  digitalWrite(4,LOW);
  delay(200);
  blin +=1;
}

  int waittime=random(2000, 10000);
  Serial.print("Waiting for ");
  Serial.print(waittime);
  Serial.println(" mS");
  delay(waittime);

// OK, get time from somewhere and store it. Then turn LED HIGH and wait for knock...

int timer = millis();
digitalWrite(4, HIGH);

  val = analogRead(knockSensor);  

  while (val <= THRESHOLD) {
    delay(10);
    val = analogRead(knockSensor);
  }
  digitalWrite(4, LOW);

int outtime = millis();
int
reaction = outtime - timer;
Serial.print("Reacted in ");
Serial.print(reaction);
Serial.println(" ms");

delay(2000);

}
