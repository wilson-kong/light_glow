/* LED grow stronger the closer you get. With some smoothing.
*/

// Ultrasonic and LED pins
const int trigPin = 9;
const int echoPin = 10;
const int ledPin = 6;

const int numReadings = 10;
int readings[numReadings];
int index = 0;
int total = 0;
int average = 0;

int fade = 0;

float duration, distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  total = total - readings[index];
  readings[index] = distance;
  total= total + readings[index];
  index = index + 1;

  if (index >= numReadings) {
    index = 0;       
  }        
  
  average = total / numReadings;
  Serial.println(average, DEC);

  Serial.print("Distance: ");
  Serial.println(average);
  if(average > 100){
    average = 100;
  }

  fade = map(average, 0, 100, 255, 0);
  analogWrite(ledPin, fade);
  Serial.print("Distance2: ");
  Serial.println(average);
  Serial.println(fade);
  
  delay(100);
}
