#include <IRremote.h>
int input_pin = 10; //set D10 as input signal pin
IRrecv irrecv(input_pin);
decode_results signals;
int output3 = 13;
int speedcheck = 100;
int condinueBlink = 0;
int vibrationPin = 11;
int buzzerPin = 12;
float referancevaltage = 5.0;
int vibration = 10000;
int tolerence = 5; 



void setup()
{
    Serial.begin(9600);
    irrecv.enableIRIn(); // enable input from IR receiver
    pinMode(output3, OUTPUT);
    pinMode(vibrationPin, INPUT);
    pinMode(buzzerPin, OUTPUT);
}


void loop() {
if (irrecv.decode(&signals)) {
        if(signals.value==16754775){
          digitalWrite(output3, HIGH);
          }

        if(signals.value==16769055){
          digitalWrite(output3, LOW);
          condinueBlink = 0;
          }

        if(signals.value==16750695){
          digitalWrite(output3, HIGH);
          speedcheck = speedcheck + 100;
          fastBlink(speedcheck);
          condinueBlink = 1;
        }

// EQ
        if(signals.value==16748655){
          speedcheck = 0;
          }
          
        Serial.println(signals.value);
        irrecv.resume(); // get the next signal
    }

    if(condinueBlink==1){
       fastBlink(speedcheck);
    }

    vibrationLevel();
}



void vibrationLevel(){

  int battery = analogRead(vibrationPin);
  int lowt = battery - tolerence;
  int hight = battery + tolerence;
//Serial.println("vvvv"); 
//Serial.println(battery);
//Serial.println(lowt);
//Serial.println(hight);

  if((vibration<lowt) || (vibration>hight)){
    Serial.println(vibration);
    digitalWrite(buzzerPin, HIGH);
    delay(10);
    digitalWrite(buzzerPin, LOW);
    vibration = battery;
  }

  delay(200);

  
  //vibration = battery;
}

int fastBlink(int blinkspeed)
{
  digitalWrite(output3, HIGH);
  delay(10);
  digitalWrite(output3, LOW);
  delay(blinkspeed);
}
