void setup() {
  pinMode(3, OUTPUT); //trig of sonar 1
  pinMode (2, INPUT); //echo of sonar 1
  Serial.begin(9600);
  void reading();
  long microsecondsToCentimeters(long);
}
long duration, cm;
int oldangle=0;

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

void reading()
{
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  // attach pin 3 to Trig

  digitalWrite(3, LOW);
  delayMicroseconds(2);
  digitalWrite(3, HIGH);
  delayMicroseconds(5);
  digitalWrite(3, LOW);
  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(2, HIGH);
  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  Serial.println(cm);
  delay(100);
}

void loop()
{
  reading();
}


