//Pin connected to ST_CP of 74HC595 (RCLK)
int latchclockPin = 8;
//Pin connected to SH_CP of 74HC595 (SRCLK)
int clockPin = 12;
////Pin connected to DS (SER) of 74HC595
int dataPin = 11;

#define RECEIVE1_PIN 2
#define RECEIVE2_PIN 3

void writeShiftRegister(uint8_t outbyte);

uint8_t getByte(void);
volatile uint8_t newByte = 0xFF;
volatile bool receiveFlag = true;


char reverseBits(char original) {
  int8_t reversed = 0;
  for(uint8_t i=0;i<8;i++)
     reversed |= ((original>>i) & 0b1)<<(7-i);
   return reversed;
}

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchclockPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(RECEIVE1_PIN, INPUT);
  pinMode(RECEIVE2_PIN, INPUT);
  pinMode(4, OUTPUT);
//  attachInterrupt(digitalPinToInterrupt(RECEIVE1_PIN), ISR_RECEIVE1, RISING);
  Serial.begin(9600);
}

void loop() {
 // if(receiveFlag){
 while(!digitalRead(RECEIVE1_PIN));
 delayMicroseconds(200);
    newByte = getByte();
    writeShiftRegister(newByte);
    receiveFlag = false;
    Serial.println(newByte);
    interrupts();
//  }


  // count from 0 to 255 and display the number 
  // on the LEDs
 // for (int numberToDisplay = 0; numberToDisplay < 256; numberToDisplay++) {
 //   Serial.print(numberToDisplay);
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
   // digitalWrite(latchPin, LOW);
  //  writeShiftRegister(numberToDisplay);
    //take the latch pin high so the LEDs will light up:
  //  digitalWrite(latchPin, HIGH);
    // pause before next value:
 //   delay(250);
//  }
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

uint8_t getByte(void){
  unsigned char inByte = 0x00;

  for(uint8_t index = 0; index<8; index++){
   // (inByte >> index);// |= digitalRead(RECEIVE1_PIN);// =  // Shift bits one to left
    //inByte &= digitalRead(RECEIVE1_PIN); //Write received bit on position
    bitWrite(inByte, 7-index, digitalRead(RECEIVE1_PIN));
    delayMicroseconds(95);
    digitalWrite(4, !digitalRead(4));
  }

  Serial.println(inByte, BIN);
  return inByte;
  //return  (inByte)+((inByte>>8)&0x01)*128;//^((inByte>>0)&0x01))*128);
  //return (unsigned )reverseBits(inByte);
}

void ISR_RECEIVE1(void){
  noInterrupts();
  delayMicroseconds(200);
  //newByte = getByte();
  receiveFlag = true;
}
