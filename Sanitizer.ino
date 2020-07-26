  //PROGRAM TO TRIGGER THE OPENING OF A SANITIZER SYSTEM

//SERVO CONNECTION

Servo myservo;
int servopin = 8;
int servoposopen = 0;   //SERVO POSITION  IN OPEN STATE
int servoposclose = 90; //SERVO POSITION  IN OPEN STATE

//ULTRASONIC CONNECTION
int trigpin = 10;     //TRIGGER PIN
int echopin = 11;     //ECHO PIN
float pingtravelfull; //PING TRAVEL TIME IN FULL DISTANCE --- TO GO TO TARGET AND COMEBACK
float pingtravelhalf; // PING TRAVEL TIME IN HALF DISTANCE --- TO GO TO TARGET ONLY
float dist;

//LED CONNECTION
int rled = 6; //GREEN LED
int gled = 7; //RED LED

//BUZZER CONNECTION
int buzzpin = 5; //BUZZER PIN
int dt = 200;    //DELAY TIME 1

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  myservo.attach(servopin);

  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);

  pinMode(rled, OUTPUT);
  pinMode(gled, OUTPUT);

  pinMode(buzzpin, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:

  //TRIGGERING THE ULTRASONIC SENSOR
  digitalWrite(trigpin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(20);
  digitalWrite(trigpin, LOW);
  delayMicroseconds(5);

  //READING THE ULTRASONIC SENSOR
  pingtravelfull = pulseIn(echopin, HIGH);
  pingtravelhalf = pingtravelfull / 2;
  dist = 0.03428 * pingtravelhalf; //THE VALUE USED (0.003428) IS FROM CONVERTING THE SPEED OF SOUND FROM KM/HR TO CM/MICROSECONDS

  Serial.print(pingtravelfull);
  Serial.print("       ");
  Serial.print(pingtravelhalf);
  Serial.print("       ");
  Serial.println(dist);
  delay(100);

  //CONDITION FOR OPENING
  if (dist >= 0.0 && dist <= 30.0)
  {
    digitalWrite(gled, HIGH);
    digitalWrite(rled, LOW);

    Serial.print("=> GREEN LED ON");
    Serial.print("   ");
    Serial.println("OPEN");

    digitalWrite(buzzpin, HIGH);
    delay(dt);
    digitalWrite(buzzpin, LOW);
    myservo.write(servoposopen);
  }

  //CONDITION FOR CLOSING
  if (dist > 30.0)
  {
    digitalWrite(gled, LOW);
    digitalWrite(rled, HIGH);
    Serial.print("=> RED LED ON");
    Serial.print("   ");
    Serial.println("CLOSE");

    myservo.write(servoposclose);
  }
}
//Code Written by CLEMENT PETER----"OPEN SOURCE IS LOVE"
