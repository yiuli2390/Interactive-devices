#include <SoftwareSerial.h>

typedef struct {
    byte pumps[20];
    byte powers[20];
    int  delays[20];
    int  currentIndex;
    int  maxIndex;
    int  initialDelay;
} Sequence;

      
SoftwareSerial mySerial(6, 7); // RX, TX

// state[i] is (inverse of) the setting of pins[i], which controls pumps[i]
      boolean  state[]       = {  0,  0,  0};
const int      lightPin      = 8;
const int      screenPin     = 11;
const int      fanPin        = A0;
const byte     continPumps[] = {  5,  6,  7};
const byte     notiPumps[]   = {  4};
      int      lastTime;
      int      targetTime;
      Sequence beats;

void setup() {
    pinMode( lightPin, INPUT);
    pinMode(screenPin, INPUT_PULLUP);

    //beats.pumps        = (byte*) calloc(sizeof(byte), 20);
    //beats.powers       = (byte*) calloc(sizeof(byte), 20);
    //beats.delays       = (int*)  calloc(sizeof(int),  20);
    beats.currentIndex = 0;
    beats.maxIndex     = 0;
    beats.initialDelay = -1; 

    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    mySerial.begin(9600);
    Serial.println("I SAID HEEEEEEYYYEEEEEEEYYYEEEEEEYEYEY!");

    delay(500);
    for (byte i = 0; i < 8; i++)
    {
        mySerial.write(0xFF);
        mySerial.write(i);
        mySerial.write((byte) 0);
    }
    delay(1000);
}

void loop() { // run over and over
    if (updateState())
    {
        driveState();
        updateSequence();
    }
    progressSequence();

    delay(10);    // Neccessary 10ms delay because using the switches sometimes causes "flickering"
}

void updateSequence()
{
    /*beats.pumps[0] = 2; beats.pumps[1] = 2;
    beats.pumps[2] = 3; beats.pumps[3] = 3;
    beats.pumps[4] = 2; beats.pumps[5] = 2;
    beats.pumps[6] = 3; beats.pumps[7] = 3;

    beats.powers[0] = 100; beats.powers[1] = 0;
    beats.powers[2] = 100; beats.powers[3] = 0;
    beats.powers[4] = 200; beats.powers[5] = 0;
    beats.powers[6] = 200; beats.powers[7] = 0;
    
    beats.delays[0] = 0; beats.delays[1] = 500;
    beats.delays[2] = 0; beats.delays[3] = 500;
    beats.delays[4] = 0; beats.delays[5] = 500;
    beats.delays[6] = 0; beats.delays[7] = 500;*/

    for (int i = 0; i < 4; i++)
        beats.pumps[i] = notiPumps[0];

    beats.powers[0] = 250; beats.powers[1] = 0;
    beats.powers[2] = 250; beats.powers[3] = 0;
    
    beats.delays[0] = 0;    beats.delays[1] = 1000;
    beats.delays[2] = 1000; beats.delays[3] = 1000;

    beats.initialDelay = 0;
    beats.currentIndex = 0;
    beats.maxIndex = 3;
}

void progressSequence()
{
    int currentTime = millis();
    if (beats.initialDelay == -1 || beats.currentIndex > beats.maxIndex)
        return;
    
    if (currentTime - lastTime >= beats.delays[beats.currentIndex])
    {
        Serial.println("Gonne execute that sequence");
        executeSequenceStep();
        lastTime = currentTime;
    }
}

void executeSequenceStep()
{
    int i = beats.currentIndex;
    mySerial.write((byte) 0xFF);
    mySerial.write(beats.pumps[i]);
    mySerial.write(beats.powers[i]);
    beats.currentIndex += 1;
}

void driveState()
{
    for (int i = 0; i < 3; i++)
    {
        if (state[i])
            on(continPumps[i]);
        else
            off(continPumps[i]);
    }
}

boolean updateState()
{
    boolean isOn;
    boolean stateChanged = false;

    isOn = digitalRead(lightPin);
    if (isOn != state[0])
        stateChanged = true;
    state[0] = isOn;
    
    isOn = !digitalRead(screenPin);
    if (isOn != state[1])
        stateChanged = true;
    state[1] = isOn;
    
    
    isOn = (analogRead(fanPin) > 1000);
    if (isOn != state[2])
        stateChanged = true;
    state[2] = isOn;
    
    return stateChanged;
}

void on(byte pump){
    mySerial.write((byte)0xFF);
    mySerial.write((byte)pump);
    mySerial.write((byte)200);
    Serial.print("Turning on ");
    Serial.println(pump);
}

void off(byte pump){
    mySerial.write((byte)0xFF);
    mySerial.write((byte)pump);
    mySerial.write((byte)1);
    Serial.print("Turning off ");
    Serial.println(pump);
}

void printIntArray(int* arr, int size)
{
    String message = "[ ";
    for (int i = 0; i < size - 1; i++)
    {
        message.concat(arr[i]);
        message.concat(", ");
    }
    message.concat(arr[size - 1]);
    message.concat("]");
    Serial.println(message);
}

void printBoolArray(boolean* arr, int size)
{
    String message = "[ ";
    for (int i = 0; i < size - 1; i++)
    {
        message.concat(arr[i]);
        message.concat(", ");
    }
    message.concat(arr[size - 1]);
    message.concat("]");
    Serial.println(message);    
}


