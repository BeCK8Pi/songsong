#define buzzer 22
#define button 18

hw_timer_t *myTimer = NULL;
hw_timer_t *songTimer = NULL;

#define time 1000000

#define C time/1047
#define D time/1175
#define E time/1319
#define F time/1397
#define G time/1568
#define A time/1760
#define B time/1976

int song[25] = {G,G,A,G,C,B,G,G,A,G,D,C,G,G,G,E,C,B,A,F,F,E,C,D,C};
int crr = 0;
int DELAY[5] = {1500000,1000000,800000,500000,100000};
int crrDelay = 0;


void IRAM_ATTR onTimer() {
  digitalWrite(buzzer, !digitalRead(buzzer));
}

void IRAM_ATTR nextNote() {
  crr = (crr+1)%25;
  //Serial.println(crr);
}
void IRAM_ATTR changeSpeed() {
  crrDelay = (crrDelay+1)%5;
  timerAlarm(songTimer, DELAY[crrDelay], true, 0);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(button, INPUT);
  myTimer = timerBegin(1500000);
  timerAttachInterrupt(myTimer, &onTimer);
  songTimer = timerBegin(1000000);
  timerAttachInterrupt(songTimer, &nextNote);
  timerAlarm(songTimer, DELAY[0], true, 0);
  attachInterrupt(button, changeSpeed, RISING);
  //timerAlarm(myTimer, C, true, 0);
}

void loop() {
  // put your main code here, to run repeatedly: 
  timerAlarm(myTimer, song[crr], true, 0);
  //Serial.println(song[crr]);
}
