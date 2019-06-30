#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#define THRESHOLD 10
#define TOLERANCE 30
/* Assign a unique ID to this sensor at the same time */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
float heading;float headingsum=0;
float headingDegrees;
float declinationangle;
void displaySensorDetails(void)
{
  sensor_t sensor;
  mag.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

long duration, cm;


long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

int reading()
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
  return cm;
}

void proximity_buzzer()
{
  digitalWrite(9,HIGH);
 delay(30);
 digitalWrite(9,LOW);
 delay(30);
}

void setup(void) 
{
  Serial.begin(9600);
  Serial.println("HMC5883 Magnetometer Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!mag.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while(1);
  }
  /* Display some basic information on this sensor */
  displaySensorDetails();
  
  
  pinMode(3, OUTPUT); //trig of sonar 1
  pinMode (2, INPUT); //echo of sonar 1
  Serial.begin(9600);
  void reading();
  long microsecondsToCentimeters(long);
  pinMode(9,OUTPUT); //output of the buzzzer
  digitalWrite(9,LOW);
}

void loop(void) 
{
  sensors_event_t event; 
  mag.getEvent(&event);
  for(int i=0;i<5;i++)
  {
    heading = atan2(event.magnetic.y, event.magnetic.x);
    if(heading < 0)
    heading += 2*PI;
    if(heading > 2*PI)
    heading -= 2*PI;
     headingDegrees = heading * 180/M_PI;
     headingsum+=headingDegrees;
  }
  float refangle=headingsum/5;
  Serial.print("refernce angle:  ");Serial.println(refangle);
  delay(1000);
 while(1)
{
  /* Get a new sensor event */ 
  sensors_event_t event; 
  mag.getEvent(&event);
 
  /* Display the results (magnetic vector values are in micro-Tesla (uT)) */
  /*Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  ");Serial.println("uT");*/

  // Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
  // Calculate heading when the magnetometer is level, then correct for signs of axis.
   heading = atan2(event.magnetic.y, event.magnetic.x);
  
  // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
  // Find yours here: http://www.magnetic-declination.com/
  // Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
  // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.

 // heading += declinationAngle;
  
  // Correct for when signs are reversed.
  if(heading < 0)
    heading += 2*PI;

  // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;
   
  // Convert radians to degrees for readability.
   headingDegrees = heading * 180/M_PI; 
Serial.print("finalangle:  ");
Serial.println(headingDegrees);
if(headingDegrees>TOLERANCE && headingDegrees<360-TOLERANCE)
{
 digitalWrite(9,HIGH); 
}
else if(360-headingDegrees>TOLERANCE && headingDegrees>360-TOLERANCE)
{
 digitalWrite(9,HIGH); 
}
else digitalWrite(9,LOW);
int dist;
  dist=reading();
  if(dist<THRESHOLD)
  {
    proximity_buzzer();
  }
  else digitalWrite(9,LOW);
}
}
