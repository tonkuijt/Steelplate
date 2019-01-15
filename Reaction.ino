/* Reaction Timer
 * 
 * Testing the levels that the Piezo sees when shooting the plate.
 * Using the basic setup (Piezo minus to gnd, plus to A(nalog)0, 680kOhm resistor parallel
 * the thresholds are as displayed.
 *
 * The program does as follows:
 *
 * It waits 10 seconds blinking the LED slow.. Then, it blinks 3 times to indicate it's going soon. 
 * Then it waits randomly between 2 and 10 seconds and lights the LED. This is the shoot signal, when the LED lights 
 * you have to shoot the plate as fast as possible.
 * When the plate is shot, the LED extinguishes and the serial monitor then show your reaction time. The 10 second load timer
 * starts again, and the whole sequence repeats itself.
 */



int ledPin = 13;
int knockSensor = 0;               
byte val = 0;
int statePin = LOW;
int THRESHOLD = 20;
int count = 0;

void setup() {
 pinMode(ledPin, OUTPUT);
 pinMode(4, OUTPUT);
 digitalWrite(4, LOW);
 Serial.begin(9600);
 Serial.println("Program started");
}

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

 // Wat randomly between 2 and 10 seonds
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
  int reaction = outtime - timer;
  Serial.print("Reacted in ");
  Serial.print(reaction);
  Serial.println(" ms");
 
 // Done, sleep 5 secs then start over
 delay(5000);

}
