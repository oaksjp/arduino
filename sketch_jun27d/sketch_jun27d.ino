#include <NS_Rainbow.h>

#define PIN 6
#define N_CELL 2

// test
NS_Rainbow ns_stick = NS_Rainbow(N_CELL,PIN);

const int R_LED = 9;
const int G_LED = 10;
const int B_LED = 11;
const int BUTTON = 2;
const int SENSOR = 0;

int sensor_val = 0;
byte sensor_led_val = 0;
byte sensor_led_val_old = 0;

char buf[1];
int pointer = 0;
byte serial_val = 0;

int button_val = LOW;
int button_val_old = LOW;
int state = 0;

void setup() {
  delay(100);
  ns_stick.begin();
  ns_stick.setBrightness(32);

  pinMode(R_LED, OUTPUT);
  pinMode(G_LED, OUTPUT);
  pinMode(B_LED, OUTPUT);
  pinMode(BUTTON, INPUT);

  Serial.begin(9600);
  Serial.println("SYSTEM START:");
}

void loop() {
  digitalWrite(G_LED, HIGH);

  if (Serial.available() > 0) {
    while (pointer < 2) {
      buf[pointer] = Serial.read();
      pointer++;
    }
    pointer = 0;
    serial_val = hex2dec(buf[1]) + hex2dec(buf[0]) * 16;
    Serial.print("serial:");
    Serial.println(serial_val);
    analogWrite(R_LED, serial_val);
    delay(100);
  }

  sensor_val = analogRead(SENSOR);
  //sensor_led_val = 255 - (sensor_val / 4);
  sensor_led_val = (sensor_val / 64 * 16);

  button_val = digitalRead(BUTTON);
  if ((button_val == HIGH) && (button_val_old == LOW)) {
    state = 1 - state;
  }
  //ns_stick.setColor(0, 255, 255, 255);
  ns_stick.setColor(1, sensor_led_val, sensor_led_val, sensor_led_val);
  ns_stick.show();

  button_val_old = button_val;

  if (sensor_led_val != sensor_led_val_old) {
    Serial.print("sensor:");
    Serial.println(sensor_led_val);
  }
  sensor_led_val_old = sensor_led_val;


  if (state == 1) {
    //Serial.print("sensor:");
    //Serial.println(sensor_val);

    //analogWrite(R_LED, serial_val);
    analogWrite(R_LED, serial_val);
    analogWrite(B_LED, sensor_led_val);
    ns_stick.setColor(0, sensor_led_val, sensor_led_val, sensor_led_val);
    ns_stick.setColor(1, sensor_led_val, sensor_led_val, sensor_led_val);
    //ns_stick.setColor(0, sensor_led_val, sensor_led_val, sensor_led_val);
/*
    ns_stick.setColor(1, 255, 255, 255);
    ns_stick.setColor(2, 255, 255, 255);
    ns_stick.setColor(3, 255, 255, 255);
    ns_stick.setColor(4, 255, 255, 255);
    ns_stick.setColor(5, 255, 255, 255);
    ns_stick.setColor(6, 255, 255, 255);
    ns_stick.setColor(7, 255, 255, 255);
*/
    ns_stick.show();
  } else {
    //analogWrite(R_LED, 0);
    analogWrite(R_LED, 0);
    analogWrite(B_LED, 0);
/*
    ns_stick.setColor(0, 0, 0, 0);
    ns_stick.setColor(1, 0, 0, 0);
    ns_stick.setColor(2, 0, 0, 0);
    ns_stick.setColor(3, 0, 0, 0);
    ns_stick.setColor(4, 0, 0, 0);
    ns_stick.setColor(5, 0, 0, 0);
    ns_stick.setColor(6, 0, 0, 0);
    ns_stick.setColor(7, 0, 0, 0);
    ns_stick.show();
*/
  }
  delay(10);
}

int hex2dec(byte c) {
  if (c >= '0' && c <= '9') {
    return c - '0';
  } else if (c >= 'A' && c <= 'F') {
    return c - 'A' + 10;
  }
  return 0;
}
