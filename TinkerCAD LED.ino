const int  buttonPin = 2; 
const int ledPin1 = 4;
const int ledPin2 = 6;
const int ledPin3 = 13;       
int buttonPushCounter = 0;
int buttonState = 0;         
int lastButtonState = 0; 
long lCnt = 0;
unsigned long lStart;
int i = 0;


void setup() {
 pinMode(buttonPin, INPUT);
 pinMode(ledPin1, INPUT);
 pinMode(ledPin2, INPUT);
  pinMode(ledPin3, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode (ledPin2, OUTPUT);
 pinMode(ledPin3, OUTPUT);
 Serial.begin(9600);
}


void loop() {
   if( lCnt == 0)
{
 lStart = millis();
}
lCnt++;
while( (millis() - lStart) <= 15000)
{
  delay(50);
 buttonState = digitalRead(buttonPin);

 if (buttonState != lastButtonState) {
   if (buttonState == HIGH) {
     buttonPushCounter++;
     Serial.println("on");
     Serial.print("number of button pushes: ");
     Serial.println(buttonPushCounter);
   } else {
     Serial.println("off");
   }
   delay(50);
 }
 lastButtonState = buttonState;

 if (buttonPushCounter == 0) {
   digitalWrite(ledPin1, 0);
   digitalWrite(ledPin2, 0);
   digitalWrite(ledPin3, 0);
 }
 else if (buttonPushCounter == 1) {
for (int i = 0; i < 255; i++){ 
  analogWrite(ledPin3, i);
  analogWrite(ledPin2, i);
  analogWrite(ledPin1, i);
    delay(5); 
  }
  for (int i = 255; i > 0; i--){ 
    analogWrite(ledPin3, i);
    analogWrite(ledPin2, i);
    analogWrite(ledPin1, i);
    delay(5);
  }
 }
  else if (buttonPushCounter == 2) {
   digitalWrite(ledPin3, HIGH);
   digitalWrite(ledPin2, HIGH);
   digitalWrite(ledPin1, HIGH);

   delay(250);
  digitalWrite(ledPin3, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin1, LOW);
   delay(250);
 } 
 else if (buttonPushCounter == 3) {
for(int i=0;i<=7;i++)
 {
  if(i==2 || i==4 || i==6 || i==0)
  {
   digitalWrite(ledPin1,LOW);  
  }
         else
  {
   digitalWrite(ledPin1,HIGH);
  }
  if(i==2 || i==3 || i==6 || i==7)
  {
   digitalWrite(ledPin2,HIGH);  
  }
  else
  {
   digitalWrite(ledPin2,LOW);
  }
  if(i>3)
  {
   digitalWrite(ledPin3,HIGH);  
  }
  else
  {
   digitalWrite(ledPin3,LOW);
  }

  delay(1500);      
 }
   buttonPushCounter = 0;
 }
}
}
 
