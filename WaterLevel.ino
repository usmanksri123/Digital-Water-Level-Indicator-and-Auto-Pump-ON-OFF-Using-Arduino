
//Note that the numbering of arduino pins are different from microcontroller pinout



int pin1 = 2;//Highest level
int pin2 = 3;
int pin3 = 4;
int pin4 = 5;
int relay= 6;

int echo = 7; // Attach Echo of ultrasonic sensor to pin 7
int trig = 8; // Attach Trig of ultrasonic sensor to pin 8


int distances[5];



int tankSizeInch=46; //Tank Size in Inches, can be change able
int tankSizeSlot=tankSizeInch/4;

void setup() {
pinMode (pin1, OUTPUT);// Set pins to output for controlling I/O
pinMode (pin2, OUTPUT);
pinMode (pin3, OUTPUT);
pinMode (pin4, OUTPUT);
pinMode (relay, OUTPUT);

digitalWrite(relay,HIGH);
Serial.begin(9600); // send and receive at 9600 baud

//delay(20000);

blinkLed();

}

void loop()
{ 



  initilizeDistances();
  int currentLevel;
  currentLevel=getPopularElement(distances);
  Serial.print("Current Tank Level is :");  
  Serial.println(currentLevel);
  levelIndication(currentLevel);
  delay(1000);

}




void levelIndication(int in)
{
  
  
if (in >=1 && in <= tankSizeSlot)//   Tank is full
{

Serial.println("Full"); 

digitalWrite(pin2, HIGH);
digitalWrite(pin3, HIGH);
digitalWrite(pin4, HIGH);
digitalWrite(pin1, HIGH);
delay(1000);
 if(in<6)
 {
  pumpOFF(); // this will off the pump when tank is full
 }
}

else if (in >=tankSizeSlot&& in<=tankSizeSlot*2) //Tank is Almost Full
{
  
Serial.println("Medium"); 

digitalWrite(pin1, LOW);
digitalWrite(pin3, HIGH);
digitalWrite(pin4, HIGH);  
digitalWrite(pin2, HIGH);
int check=(tankSizeSlot)+(tankSizeSlot*2);; 
if(in>check/2)
pumpON(); 
delay(1000);

}
else if (in >=tankSizeSlot*2&&in<=tankSizeSlot*3) {

Serial.println("Low"); 
digitalWrite(pin1, LOW);
digitalWrite(pin2, LOW);
digitalWrite(pin4, HIGH);
digitalWrite(pin3, HIGH);
pumpON();

delay(1000);

}
//else if (in >=tankSizeSlot*3&&in<=tankSizeSlot*4) // empty
else if (in >=tankSizeSlot*3) // empty

{
  
Serial.println("Empty"); 
digitalWrite(pin1, LOW);
digitalWrite(pin2, LOW);
digitalWrite(pin3, LOW);
digitalWrite(pin4,HIGH );
pumpON();

delay(1000);
}
  }






void initilizeDistances()
{
  long duration, in;       //'in' is inches 
  for(int i=0;i<5;i++)
{

  // The PING is triggered by a HIGH pulse of 2 or more microseconds.
// Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
pinMode(trig, OUTPUT);
digitalWrite(trig, LOW);
delayMicroseconds(2);
digitalWrite(trig, HIGH);
delayMicroseconds(50);
digitalWrite(trig, LOW);

// The same pin is used to read the signal from the PING: a HIGH
// pulse whose duration is the time (in microseconds) from the sending
// of the ping to the reception of its echo off of an object.
  pinMode(echo, INPUT);
  duration = pulseIn(echo, HIGH);

  // Convert the time into a distance
  in = microsecondsToInches(duration);
  Serial.println(in); 
  
  distances[i]=in;
  delay(1500);
  
  }
  }


 int getPopularElement(int a[])
{
  int count = 1;
  int tempCount;
  int popular = a[0];
  int temp = 0;
  for (int i = 0; i < 5; i++)
  {
    temp = a[i];
    tempCount = 0;
    for (int j = 1; j < 5; j++)
    {
      if (temp == a[j])
        tempCount++;
    }
    if (tempCount > count)
    {
      popular = temp;
      count = tempCount;
    }
  }


  
  return popular;
}


long microsecondsToInches(long microseconds)
{
// According to Parallax's datasheet for the PING, there are
// 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
// second). This gives the distance travelled by the ping, outbound
// and return, so we divide by 2 to get the distance of the obstacle.
// See: http://www.parallax.com/dl/docs/prod/acc/28015-PI...
return microseconds / 74 / 2;
}

void pumpON()
{
    
    digitalWrite(relay,LOW);
    Serial.println("Pump is On"); 
    //delay(240000);// 60*1000= 1 minute; this delay is for 4 minutes
    
    //delay(60000);// waits for one minute


  }

  void pumpOFF()
  {
    digitalWrite(relay,HIGH);
      Serial.println("Pump is Off"); 

    
    }

    void blinkLed()
  {

   
    digitalWrite(pin1,HIGH);
    digitalWrite(pin2,HIGH);
    digitalWrite(pin3,HIGH);
    digitalWrite(pin4,HIGH);
    delay(2000);
    digitalWrite(pin1,LOW);
    digitalWrite(pin2,LOW);
    digitalWrite(pin3,LOW);
    digitalWrite(pin4,LOW);
   
    
  }
