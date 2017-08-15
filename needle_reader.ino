/* 
  Pin Configuration
*/
#define RED_NEEDLE_IN A0
#define WHITE_NEEDLE_OUT 9
#define RED_LIGHT 2
#define ORANGE_LIGHT 3
#define SWITCH_IN A1
//#define SWITCH_IN 4

// Demo vars
int needleSetting = 0;
long needleTime;
long lightTime;

bool redState = false;
bool orangeState = true;

void setup() {
  Serial.begin(9600);
  needleTime = millis();
  lightTime = millis();

  pinMode(RED_LIGHT, OUTPUT);
  pinMode(ORANGE_LIGHT, OUTPUT);
  pinMode(SWITCH_IN, OUTPUT);
}

void loop() {
  // Report red needle value and switch state
  Serial.print(readRedNeedle());
  Serial.print(", ");
  Serial.println(getSwitchState());
  //Serial.println(analogRead(SWITCH_IN));

  // Randomly set position of white needle
  setWhiteNeedle(needleSetting);

  if (millis() - needleTime >= 1000) {
    needleSetting = random(0, 30);
    needleTime = millis();
  }

  if (millis() - lightTime >= 500) {
    redState = !redState;
    orangeState = !orangeState;

    setRed(redState);
    setOrange(orangeState);
  
    lightTime = millis();
  }
}

float readRedNeedle() {
  return voltToDial(analogRead(RED_NEEDLE_IN));
}

// Converts voltage from analogRead to dial setting (for red needle)
float voltToDial(int volt) {
  volt = constrain(volt, 25, 700);

  // return (volt - minimum value) * (maximum value / range)
  return (volt - 25) * (31 / 630.0);
}

void setWhiteNeedle(float dialSetting) {
  // Map: 0 - 30 dial setting == 0 - 155 output
  
  analogWrite(WHITE_NEEDLE_OUT, dialSetting * (155 / 30.0));
}

bool getSwitchState() {
  return analogRead(SWITCH_IN) > 650;
}

void setOrange(bool setting) {
  if (setting) {
    digitalWrite(ORANGE_LIGHT, HIGH);
  } else digitalWrite(ORANGE_LIGHT, LOW);
}

void setRed(bool setting) {
  if (setting) {
    digitalWrite(RED_LIGHT, HIGH);
  } else digitalWrite(RED_LIGHT, LOW);
}

