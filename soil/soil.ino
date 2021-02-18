//pin conifg
int sensor_pin = A0;
int relay = 8;
volatile byte relayState = LOW;

int output_value ;

void setup() {
  // Pin for relay module set as output
  pinMode(relay, OUTPUT);
  pinMode(relay, LOW);

   Serial.begin(9600);

   Serial.println("Reading From the Sensor ...");

   delay(2000);

   }

void loop() {

   output_value= analogRead(sensor_pin);

   output_value = map(output_value,550,0,0,100);

   Serial.print("Mositure : ");

   Serial.print(output_value);

   Serial.println("%");

   if(output_value<10){
    pinMode(relay, HIGH);
    delay(3000);
    pinMode(relay, LOW);
   }

   delay(1000);

   }
