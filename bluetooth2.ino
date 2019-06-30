char val;         // variable to receive data from the serial port
int x;
void setup()
{
  pinMode(13, OUTPUT);  // pin 13  as OUTPUT
 
  Serial.begin(115200);       // start serial communication at 115200bps
 
}
 
void loop() {
  if( Serial.available() )       // if data is available to read
  {;}
    val = Serial.read();         // read it and store it in 'val'
    int x=val-'0';
  if( x == 0 )               // if '0' was received led 13 is switched off

  {
   digitalWrite(13, LOW);    // turn Off pin 13 off
delay(1000);                  // waits for a second   
Serial.println("13 off");
  }

if( x == 1 )               // if '1' was received led 13 on
 {
    digitalWrite(13, HIGH);  // turn ON pin 13 on
    delay(1000);                  // waits for a second
    Serial.println("13 on");
  }
}
