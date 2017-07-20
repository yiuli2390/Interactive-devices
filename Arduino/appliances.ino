
// set pin numbers:
const int lightInPin = 8;     
const int ledPin =  13;    
const int screenPin = 11;    
int fanPin = A0;    // select the input pin for the potentiometer

// variables will change:
int lightpower = 0;
boolean lightPowerOn = false;
int fanpower = 0;
boolean fanPowerOn = false;

int screenpower = 0;
boolean screenPowerOn = 0;

 void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the switch pin as an input:
  pinMode(lightInPin, INPUT);
  Serial.begin(9600);
}

void loop() { 
  // read the state of the input 
   lightpower = digitalRead(lightInPin);
  // Serial.print(lightpower);
   fanpower = analogRead(fanPin);
   screenpower = digitalRead(screenPin);


  // check for light
  if (lightpower == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    lightPowerOn = true;
  } else {
    lightPowerOn = false;
  }
  Serial.print("Light == ");
  Serial.println(lightPowerOn);
  

  // check for fan
  if (fanpower > 1000)
  {
    digitalWrite(ledPin,HIGH);
    //delay(1000);
    fanPowerOn = true;
  }else
  { 
    fanPowerOn = false;
   //delay(1000);
  }
  Serial.print("Fan == ");
  Serial.println(fanPowerOn);    
//Serial.println(fanpower);
  digitalWrite(ledPin,LOW);


  //check for screen
  if (screenpower == HIGH){
      screenPowerOn = true;
      //delay(1000);
    }else{
      screenPowerOn = false;
      //delay(1000);  
    }
   Serial.print("Screen = ");
   Serial.println(screenPowerOn);

  delay(1000);
}

