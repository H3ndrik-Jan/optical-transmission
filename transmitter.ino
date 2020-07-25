#define RECEIVE1_PIN 2
#define RECEIVE2_PIN 3
#define TRANSMIT1_PIN 4
#define TRANSMIT2_PIN 5

void sendByte(uint8_t outByte);
uint8_t getByte(void);

void setup() {
  pinMode(RECEIVE1_PIN, INPUT);
  pinMode(RECEIVE2_PIN, INPUT);
  pinMode(TRANSMIT1_PIN, OUTPUT);
  pinMode(TRANSMIT2_PIN, OUTPUT);
  Serial.begin(9600);
  // put your setup code here, to run once:
 // attachInterrupt(digitalPinToInterrupt(RECEIVE1_PIN), ISR_RECEIVE1, RISING);
 // attachInterrupt(digitalPinToInterrupt(RECEIVE1_PIN), ISR_RECEIVE2, RISING);
}

void loop() {
  static uint8_t counter = 0;
  uint8_t testByte =5;
  sendByte(counter);
  counter+=32;
  Serial.println(counter,BIN);
  Serial.println(counter);
  delay(500);
}

void sendByte(uint8_t outByte){
  digitalWrite(TRANSMIT1_PIN, HIGH);
  delayMicroseconds(200);
  digitalWrite(TRANSMIT1_PIN, LOW);
  delayMicroseconds(100);
  for(int8_t index = 7; index>=0; index--){
    digitalWrite(TRANSMIT1_PIN, (outByte >> index) & 0x01);
    delayMicroseconds(100);
  }

  digitalWrite(TRANSMIT1_PIN, LOW);
}
/*
uint8_t getByte(void){
  uint8_t inByte;

  for(uint8_t index = 0; index<8; index++){
    inByte << = 1; // Shift bits one to left
    inbyte |= digitalRead(RECEIVE1_PIN); //Write received bit on position
    delayMicroseconds(100);
  }
  return inByte;
}

void ISR_RECEIVE1(void){
  delayMicroseconds(300);
  
}
*/

