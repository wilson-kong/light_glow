/* LED grow stronger the closer you get. With some smoothing.
*/

const int numReadings = 10; 
int readings[numReadings];       
int index = 0;                  
int total = 0;                  
int average = 0;    

const int minDistance = 30;
const int maxDistance = 70;

const int trigPin = 9;
const int echoPin = 10;
const int ledPin = 6;
const int ledPin2 = 3;
const int ledPin3 = 5;
const int ledPin4 = 11;
const int ledPin5 = A0;
const int ledPin6 = A1;
const int ledPin7 = A2;
const int ledPin8 = A3;
const int ledPin9 = A4;
const int ledPin10 = A5;

int fade = 0;

float duration, distance;

void setLEDs(int value);
void setExtraLEDs(int number);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(ledPin6, OUTPUT);
  pinMode(ledPin7, OUTPUT);
  pinMode(ledPin8, OUTPUT);
  pinMode(ledPin9, OUTPUT);
  pinMode(ledPin10, OUTPUT);
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
  
  // total = total - readings[index];
  // readings[index] = distance;
  // total= total + readings[index];
  // index = index + 1;

  // if (index >= numReadings) {
  //   index = 0;       
  // }        
  
  // average = total / numReadings;
  average = distance;
  
  if(average > maxDistance){
    average = maxDistance;
  }
  if(average < minDistance){
    average = minDistance;
  }

  fade = map(average, minDistance, maxDistance, 255, 0);
  Serial.print("Distance: ");
  Serial.println(fade);
  
  setLEDs(fade);
  if (fade > minDistance) {
    int extra = map(fade, 255, 0, 3, 0);
    if (extra) {
      setExtraLEDs(extra);
    }
  } else {
    setExtraLEDs(0);
  }
  // } else if (100 < average < 200) {
  //   setExtraLEDs(2);
  // } else if (50 < average < 100) {
  //   setExtraLEDs(1);
  // }
  

  // Serial.print("Distance2: ");
  // Serial.println(average);
  // Serial.println(fade);
  Serial.print("Glow: ");
  Serial.println(average);

  delay(100);
}

void setLEDs(int value) {
  analogWrite(ledPin, value);
  analogWrite(ledPin2, value);
  analogWrite(ledPin3, value);
  analogWrite(ledPin4, value);
}

void setExtraLEDs(int number) {
  Serial.println("number:");
  Serial.println(number);
  switch (number) {

    case 1:
      analogWrite(ledPin5, 255);
      analogWrite(ledPin6, 0);
      analogWrite(ledPin7, 0);
      break;
    case 2:
      analogWrite(ledPin5, 255);
      analogWrite(ledPin6, 255);
      analogWrite(ledPin7, 0);
      break;
    case 3:
      analogWrite(ledPin5, 255);
      analogWrite(ledPin6, 255);
      analogWrite(ledPin7, 255);
      break;
    default:
      analogWrite(ledPin5, 0);
      analogWrite(ledPin6, 0);
      analogWrite(ledPin7, 0);
      break;
  }
}
