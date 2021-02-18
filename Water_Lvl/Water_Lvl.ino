// Define Trig and Echo pin:
#define trigPin 2
#define echoPin 4
// Define variables:
long duration;
int distance;
int full = 11.5;
int low =14.5;
int high = 3;
void setup() {
  // Define inputs and outputs:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(12, OUTPUT);
  //Begin Serial communication at a baudrate of 9600:
  Serial.begin(9600);
}
void loop() {
  // Clear the trigPin by setting it LOW:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  // Trigger the sensor by setting the trigPin high for 10 microseconds:
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Read the echoPin, pulseIn() returns the duration (length of the pulse) in microseconds:
  duration = pulseIn(echoPin, HIGH);
  // Calculate the distance:
  distance = duration * 0.034 / 2;
  Serial.println(distance);

 /* //tank lvl
  int water_height = full-distance;
    if(water_height<4){
    Serial.print("LOW WATER LVL");
  }else if(water_height>8){
    Serial.print("Tank Full");
  }
  int pre = water_height*100/full;
    Serial.print("Water Lvl = ");
    Serial.print(pre);
    Serial.println("%");*/
    delay(1000);
}
