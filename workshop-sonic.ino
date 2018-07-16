

int led = 5;
int rx = 3;
int tx = 2;
int r = 13;
int g = 15;
int b = 14;

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(rx, INPUT);
  pinMode(tx, OUTPUT);
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  // pinMode(b, OUTPUT);



}

// the loop function runs over and over again forever
void loop() {

  long duration, cm;


  digitalWrite(tx, LOW);
  delayMicroseconds(2);
  digitalWrite(tx, HIGH);
  delayMicroseconds(5);
  digitalWrite(tx, LOW);
  duration = pulseIn(rx, HIGH);
  cm = microsecondsToCentimeters(duration);

  Serial.print(cm);
  Serial.print("\n");

  if (cm < 50)
  {
    digitalWrite(r, LOW); 
    digitalWrite(g, HIGH);   
    //      digitalWrite(b, HIGH);   
  } else {
    digitalWrite(r, HIGH);  
    digitalWrite(g, LOW);   
    //      digitalWrite(b, HIGH);   
  }

  digitalWrite(led, LOW);   
  delay(1000);                      // Wait for a second
  digitalWrite(led, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(2000);                      // Wait for two seconds (to demonstrate the active low LED)
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
