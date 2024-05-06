/* LED grow stronger the closer you get. With some smoothing.
*/

const int numReadings = 10; 
int readings[numReadings];       
int index = 0;                  
int total = 0;                  
int average = 0;                

const int trigPin = 9;
const int echoPin = 10;
const int ledPin = 6;
const int redPin = 11;
const int greenPin = 5;// 10;
const int bluePin = 3;//9;

int fade = 0;

float duration, distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
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
  setColor(fade, fade, fade); // White
  Serial.print("Distance2: ");
  Serial.println(average);
  Serial.println(fade);
  
  delay(100);
}

void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
