//Simple example program for receiving bytes from the fibre optic receiver.
//An interrupt is triggered when new data comes in. The data is then read and 
//sent to an 74HC595 in this example

//Pin connected to the output of the fibre optic receiver
#define RECEIVE1_PIN 2
//Pin connected to ST_CP (RCLK) of 74HC595 
#define latchclockPin 8
//Pin connected to SH_CP (SRCLK) of 74HC595 
#define clockPin 12
//Pin connected to DS (SER) of 74HC595
#define dataPin  11

//Transmission speed multiplier. Higher means lower speed
#define SPEED 10

void writeShiftRegister(uint8_t outbyte);
uint8_t getByte(void);

uint8_t newByte = 0xFF;
volatile bool receiveFlag = true;


void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchclockPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(RECEIVE1_PIN, INPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  attachInterrupt(digitalPinToInterrupt(RECEIVE1_PIN), ISR_RECEIVE1, RISING);
  Serial.begin(9600);
}

void loop() {
  if(receiveFlag){
    static uint8_t lastByte = 0;
    newByte = readByte();
    if(newByte != lastByte+1){
      digitalWrite(5, HIGH);
    }
    else digitalWrite(5, LOW);

    lastByte = newByte;
    writeShiftRegister(newByte);
    receiveFlag = false;

    interrupts();
    Serial.println(newByte);
  }
}

uint8_t readByte(void){
  uint8_t inByte = 0;
    digitalWrite(4, HIGH);
    while(digitalRead(RECEIVE1_PIN)); //  Wait for start pulse to end

    for(int i=0; i<8; i++){
      digitalWrite(4, !digitalRead(4));
      while(!digitalRead(RECEIVE1_PIN)); //Wait for bitpulse
      while(digitalRead(RECEIVE1_PIN)); //Wait for bitpulse to end
      delayMicroseconds(SPEED*4.5);  
      inByte = inByte | (!digitalRead(RECEIVE1_PIN)<<i);
    }
  digitalWrite(4, LOW);
  return inByte;
}

void ISR_RECEIVE1(void){
  noInterrupts();
  receiveFlag = true;
}

void writeShiftRegister(uint8_t outbyte){
  digitalWrite(latchclockPin, LOW);

    for(uint8_t index = 0; index<8; index++){
    digitalWrite(clockPin, HIGH); //Set clock high
        //  Optionally wait for minimum clock pulse length here
        
    digitalWrite(clockPin, LOW);  //Set clock low again
    digitalWrite(dataPin, (outbyte >> index) & 0x01); //Write bit to the data pin
        //  Optionally wait for minimum clock pulse length here
    }
  
  digitalWrite(latchclockPin, HIGH);
}
