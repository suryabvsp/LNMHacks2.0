#include <QueueList.h>
QueueList <float> queue;
float printDistance;
const int trigPin = 2;
const int echoPin = 3;
const int IRpin = 8;
float duration;
float distance;
float minDist;
void setup() {
  pinMode(IRpin, INPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
  queue.setPrinter (Serial);
}
float calculateDistance() {
  unsigned long T1 = micros();
  digitalWrite(trigPin, LOW); // trigPin needs a fresh LOW pulse before sending a HIGH pulse that can be detected from echoPin
  delayMicroseconds(2);//DELAY #2:time for which low trig pulse is maintained before making it high
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);//DELAY #3:Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  //distance= duration*0.034/2;
  distance = (duration / 2) / 29.1; //in cm,  datasheet gives "duration/58" as the formula

  return distance;
}
void loop()
{
  distance = calculateDistance();

  if(distance >= 400) {
    ;
  }
  else{
    if (queue.count() < 5)
    {
      queue.push(distance);
    }
    else
    {
      minDist = 1000;
      for(int i=0;i<5;i++)  {
        if (queue.peek() < minDist)
          minDist = distance;
        queue.pop();
      }
      
      //printDistance = minDist;         //getMinimum
      Serial.print(minDist);
      Serial.print(",");
      int A = digitalRead(IRpin);
      Serial.println(A);
      delay(62);  // delay to avoid overloading the serial port buffer    }
  }

  
  }
}
