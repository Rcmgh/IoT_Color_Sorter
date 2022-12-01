#include <Servo.h>

#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6

Servo topServo;
Servo bottomServo;

int frequency = 0;
int color=0;
int d,o,b,g,y=0;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  topServo.attach(7);
  bottomServo.attach(8);

  Serial.begin(9600);
}

void loop() {

  topServo.write(115);
  delay(500);
  
  for(int i = 115; i > 80; i--) {
    topServo.write(i);
    delay(5);
  }
  delay(500);
  
  color = readColor();
  delay(10);  

  switch (color) {
    case 1:
    bottomServo.write(60);
    o++;
    //Serial.print("orange:");
   // Serial.print(o);
    break;

    case 2:
    bottomServo.write(90);
    y++;//Serial.print("yellow:");
    //Serial.print(y);
    break;  

    case 3:
    bottomServo.write(120);
    b++;
    //Serial.print("blue:");
    //Serial.print(g);
    break;

    case 4:
    bottomServo.write(0);
    d++;
    //Serial.print("others:");
    //Serial.print(d);
    break;
    
    case 0:
    break;
  }
  delay(300);  //300
  
  for(int i = 80; i > 29; i--) {
    topServo.write(i);
    delay(2);   //2
  } 
  delay(200);   //200
  
  for(int i = 29; i < 115; i++) {
    topServo.write(i);
    delay(2);    //2
  }
  //color=0;
}

// Custom Function - readColor()
int readColor() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  //frequency = map(frequency, 25,72,255,0);
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(50);

  // Setting Green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(50);

  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  delay(50);

  if( R<88 & R>80 & G<92 & G>84){   //& B<65 & B>55
    //color = 1;
     Serial.print("Yellow"); 
     return 1;// orange
  }
 
   if( B<70 & B>60){   //& B<62 & B>56
    //color = 2; 
    Serial.print("Orange"); 
    return 2;//yellow
  }
   if(R<105 & R>94 & G<94 & G>85 & B<62 & B>55){
   //color = 3;
    Serial.print("Blue Color");
    return 3;// blue
  }
   else{
    //color - 4 ;
     Serial.print("other Color");// others
  return 4;
  }
    
}
