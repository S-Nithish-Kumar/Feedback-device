#include <Servo.h>
const int microphonePin1 = A3;
const int microphonePin2 = A7;
int ledPin1 = 3;
int ledPin2 = 7;
int pos = 0;
Servo myservo; 

void setup() {
  Serial.begin(9600);
  myservo.attach(9);
  pinMode(ledPin1, OUTPUT);
  pinMode(microphonePin1, INPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(microphonePin2, INPUT);
}

void servo_min() 
{
  for (pos = 0; pos <= 15; pos += 1) 
  {
    myservo.write(pos);              
    delay(1);                       
  }
  for (pos = 15; pos >= 0; pos -= 1) 
  { 
    myservo.write(pos);              
    delay(1);                       
  }
}

void servo_max() 
{
  for (pos = 0; pos <= 60; pos += 1) 
  {
    myservo.write(pos);              
    delay(1);                       
  }
  for (pos = 60; pos >= 0; pos -= 1) 
  { 
    myservo.write(pos);              
    delay(1);                       
  }
}

void led1_function()
{
  digitalWrite(ledPin1, HIGH);
  delay(100);
  digitalWrite(ledPin1, LOW);
}

void led2_function()
{
  digitalWrite(ledPin2, HIGH);
  delay(100);
  digitalWrite(ledPin2, LOW);
}

void loop() {
  int mn1 = 1024;
  int mx1 = 0;
  int mn2 = 1024;
  int mx2 = 0;

  for (int i = 0; i < 500; ++i) {
    int val1 = analogRead(microphonePin1);
    mn1 = min(mn1, val1);
    mx1 = max(mx1, val1);
    int val2 = analogRead(microphonePin2);
    mn2 = min(mn2, val2);
    mx2 = max(mx2, val2);
  }

  int delta1 = mx1 - mn1;
  int delta2 = mx2 - mn2;

  Serial.print("delta1:");
  Serial.println(delta1);
  Serial.print("delta2:");
  Serial.println(delta2);

  if ((delta1 > 15 && delta1 <=19) && (delta2 <= 14)) 
  {
    //led1_function();
    ///servo_inter(); 
  }
  if ((delta1 > 19) && (delta2 <= 14)) 
  {
    delay(100);
    servo_min(); 
  }
  else if ((delta1 > 13 && delta1 <=17) && (delta2 > 14))
  {
    delay(100);
    servo_max();
  }
  else if (delta1 > 20 && delta2 > 14)
  {
  }
  else if ((delta1 > 13 && delta1 <=15) && (delta2 <= 14))
  {
    delay(100);
    servo_max();
  }
  else {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
  }

}
