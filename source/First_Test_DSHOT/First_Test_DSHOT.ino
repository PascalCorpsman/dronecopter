
unsigned long previousMillis; 

#define nop() asm volatile("nop")

void write_one()
{
  PORTD = 1 << 7;  
  nop(); // 1
  nop();
  nop();
  nop();
  nop(); // 5
  nop();
  nop();
  nop();
  nop();
  nop(); // 10
  nop();
  nop();
  nop();
  nop();
  nop(); // 15
  nop();
  nop();
  nop();
  nop();
  nop(); // 20
  nop(); // 1
  nop();
  nop();
  nop();
  nop(); // 5
  nop();
  nop();
  nop();
  nop();
  nop(); // 10  
  nop();
  nop();
  nop();
  nop();
  nop(); // 15
  nop();
  nop();
  nop();
  nop();
  nop(); // 20  
  PORTD = 0; 
  nop(); // 1
  nop();
  nop();  

}

void write_zero()
{
  PORTD = 1 << 7;  
  nop(); // 1
  nop();
  nop();
  nop();
  nop(); // 5
  nop();
  nop();
  nop();
  nop();
  nop(); // 10
  nop();
  nop();
  nop();
  nop();
  nop(); // 15
  nop();
  nop();
  nop();
  PORTD = 0;  
  nop();
  nop(); // 20
  nop(); // 1
  nop();
  nop();
  nop();
  nop(); // 5
  nop();
  nop();
  nop();
  nop();
  nop(); // 10
  nop();
  nop();
  nop();
  nop();
  nop(); // 15
  nop();
  nop();
  nop();
  nop();
  nop(); // 20
  nop(); // 1
  nop();
  nop();  
}

void frame_0()
{
  write_zero();write_zero();write_zero();write_zero();
  write_zero();write_zero();write_zero();write_zero();
  write_zero();write_zero();write_zero();write_zero();
  write_zero();write_zero();write_zero();write_zero();
}

void frame_100()
{
  write_zero();write_zero();write_zero();write_one();
  write_zero();write_zero();write_one();write_zero(); 
  write_one();write_one();write_zero();write_zero();
  write_one();write_one();write_one();write_one();
}

void setup() {
  // put your setup code here, to run once:
  pinMode(7, OUTPUT);
  previousMillis = millis();
  frame_0();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (millis() < 5000)
  {
    frame_0();  
  } else {
    frame_100();    
  }
  //delayMicroseconds(1935);
  delay(25);
}
