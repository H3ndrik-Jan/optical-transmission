//Simple example program for sending bytes using the optical transmitter board. 
//Continuously sends bytes from 0 to 255.
#define TRANSMIT1_PIN 4

//Transmission speed multiplier. Needs to match the receiver's speed
#define SPEED 10

void sendByte(uint8_t outByte);

void setup() {
  pinMode(TRANSMIT1_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  static uint8_t counter = 0;
  sendByte(counter);
  counter++;
  Serial.println(counter);
}

void sendByte(uint8_t outByte){
  digitalWrite(TRANSMIT1_PIN, HIGH);
  delayMicroseconds(SPEED*15);
  digitalWrite(TRANSMIT1_PIN, LOW);
  delayMicroseconds(SPEED*3);
  for(uint8_t index = 0; index<8; index++){
    digitalWrite(TRANSMIT1_PIN,LOW);
    digitalWrite(TRANSMIT1_PIN,HIGH);
    delayMicroseconds(SPEED*2);
    digitalWrite(TRANSMIT1_PIN,LOW);
    delayMicroseconds(SPEED);
    digitalWrite(TRANSMIT1_PIN, (outByte >> index) & 0x01);
    delayMicroseconds(SPEED*10);
  }

  digitalWrite(TRANSMIT1_PIN, LOW);
}
