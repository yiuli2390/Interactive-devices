#include <SoftwareSerial.h>

SoftwareSerial mySerial(6, 7); // RX, TX

static const int BEAT_LOOP = 32;
static const int TIME_STEP = 300;
static const int PUMP_HIGH = 250;
static const int BASS_SWITCH = 11;
static const int MIDD_SWITCH = 8;
static const int CYMB_SWITCH = A0;
static const byte BASS_PUMP = (byte)4;
static const byte MIDD_PUMP = (byte)5;
static const byte HIGH_PUMP = (byte)6;
static const byte CYMB_PUMP = (byte)7;

void setup()
{
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  pinMode(MIDD_SWITCH, INPUT);
  pinMode(BASS_SWITCH, INPUT_PULLUP);
  
  static byte pump[8];
  for(byte ii = 0; ii < 8; ++ii)
  {
    pump[ii] = 0; 
  }
  drive(pump);
}

void loop()
{
  static int beat = 0;
  boolean bass_on = !digitalRead(BASS_SWITCH);
  boolean midd_on = digitalRead(MIDD_SWITCH);
  boolean cymb_on = (analogRead(CYMB_SWITCH) > 1000);

  play(bass_on, midd_on, cymb_on, beat);
  
  beat += 1;
  if(beat >= BEAT_LOOP) beat = 0;
  delay(TIME_STEP);
}

void play(boolean bass_on, boolean midd_on, boolean cymb_on, int beat)
{
  static const byte BASS_STATE[] = {0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0,
                                    1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0,
                                    1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0,
                                    1, 0, 2, 0, 1, 0, 2, 0, 1, 0, 2, 0, 1, 0, 2, 0, 1, 0, 2, 0, 1, 0, 2, 0, 1, 0, 2, 0, 1, 0, 2, 0};
  static const byte MIDD_STATE[] = {2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0,
                                    2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
                                    2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0,
                                    2, 0, 1, 0, 2, 0, 1, 0, 2, 0, 1, 0, 2, 0, 1, 0, 2, 0, 1, 0, 2, 0, 1, 0, 2, 0, 1, 0, 2, 0, 1, 0};
  static const byte HIGH_STATE[] = {0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2,
                                    0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2,
                                    0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2,
                                    1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2};
  static const byte CYMB_STATE[] = {2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 2, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0,
                                    2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
                                    2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 1, 0, 2, 0, 1, 0,
                                    2, 0, 1, 0, 2, 0, 1, 0, 2, 0, 1, 0, 2, 1, 2, 1, 2, 0, 1, 0, 2, 0, 1, 0, 2, 0, 1, 2, 1, 0, 0, 0};
  static byte PUMP_STATE[] = {(byte)0, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0};

  int high_beat = beat + (bass_on ? 32 : 0) + (midd_on ? 32 : 0) + (cymb_on ? 32 : 0);
  int bass_beat = (bass_on ? high_beat : beat);
  int midd_beat = (midd_on ? high_beat : beat);
  int cymb_beat = (cymb_on ? high_beat : beat);

  if(BASS_STATE[bass_beat] != 0)
  {
    PUMP_STATE[BASS_PUMP] = (BASS_STATE[bass_beat] == 1 ? PUMP_HIGH : 0);
  }
  if(MIDD_STATE[midd_beat] != 0)
  {
    PUMP_STATE[MIDD_PUMP] = (MIDD_STATE[midd_beat] == 1 ? PUMP_HIGH : 0);
  }
  if(HIGH_STATE[high_beat] != 0)
  {
    PUMP_STATE[HIGH_PUMP] = (HIGH_STATE[high_beat] == 1 ? PUMP_HIGH : 0);
  }
  if(CYMB_STATE[cymb_beat] != 0)
  {
    PUMP_STATE[CYMB_PUMP] = (CYMB_STATE[cymb_beat] == 1 ? PUMP_HIGH : 0);
  }

  drive(PUMP_STATE);
}

void drive(const byte pump[8])
{
  for(byte ii = 0; ii < 8; ++ii)
  {
    if(pump[ii] != 0xFF)
    {
      mySerial.write(0xFF);
      mySerial.write(ii);
      mySerial.write(pump[ii]);
    }
  }
}


