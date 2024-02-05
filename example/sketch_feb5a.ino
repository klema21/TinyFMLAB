#include <Wire.h>
#include <BROADCASTRADIO.h>

int switchPin = 8;
int switchPinBack = 9;
double frequency;
double old_frequency;
int search_mode = 0;
int search_direction;
unsigned long last_pressed;

BroadcastRadio Radio;
byte arr[5]={0,0,0xB0,0x10,0x00};

void setup() {
  Wire.begin();
  
  Radio.init();
  Radio.set_frequency(105.4);
  Serial.begin(9600);

  pinMode(switchPin, INPUT);
  pinMode(switchPinBack, INPUT);
}
void loop() {
  unsigned char buf[5];
  int stereo;
  int signal_level;
  double current_freq;
  unsigned long current_millis = millis();

  if (Radio.read_status(buf) == 1) {
    current_freq =  floor (Radio.frequency_available (buf) / 100000 + .5) / 10;
    stereo = Radio.stereo(buf);
    signal_level = Radio.signal_level(buf);
  }

  if (search_mode == 1) {
      if (Radio.process_search (buf, search_direction) == 1) {
          search_mode = 0;
      }
  }

  if (digitalRead(switchPin) == HIGH) {
    last_pressed = current_millis;
    search_mode = 1;
    search_direction = BROADCASTRADIO_SEARCH_DIR_UP;
    Radio.search_up(buf);
    delay(300);
  }

  if (digitalRead(switchPinBack) == HIGH) {
    last_pressed = current_millis;
    search_mode = 1;
    search_direction = BROADCASTRADIO_SEARCH_DIR_DOWN;
    Radio.search_down(buf);
    delay(300);
  }

  delay(50);
  
  if (frequency < 87.4) frequency = 87.4;
  else if (frequency > 108.0) frequency = 108.0;
}