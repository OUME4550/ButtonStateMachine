/* Button StateMachine Example
 *  by: Jay Wilhelm (jwilhelm@ohio.edu)
 *  Purpose: Demonstrates a button up/down state machine
 *  where actions can be triggered at the press/release states
 */


#define ledPin      7
#define buttonPin   2
#define ON_DURATION 1500
#define DEBUG_MODE //comment out to remove debug statement
void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  Serial.begin(115200);
  Serial.println("Welcome to the button press example");
}

void loop() {
  //init value of state machine
  static int button1State = 1;
  //keep track of the times a press occurs
  static unsigned int pressCount = 0;
  int newButtonRead = digitalRead(buttonPin);
  delay(10);//debounce wait
  int secondButtonRead = digitalRead(buttonPin);
  if(newButtonRead != secondButtonRead) {//make sure there is no bouncing
    Serial.println("Debounce issue!");
    return;//jump out of loop, avoids rest of code in here
  }  
  #ifdef DEBUG_MODE
  Serial.print("Current State: ");
  Serial.println(button1State);
  #endif
  //update the state machine
  //STATE MACHINE LOGIC HERE
  if(button1State == 1 && newButtonRead == HIGH)
    button1State = 2;
  else if(button1State == 2)
    button1State = 3;
  else if(button1State == 3 && newButtonRead == LOW)
    button1State = 4;
  else if(button1State == 4)
    button1State = 1;
  #ifdef DEBUG_MODE
  Serial.print("New State: ");
  Serial.println(button1State);
  #endif
  //EVENT LOGIC HERE
  //do something with the state data
  static unsigned long press_time = 0;
  if (button1State == 2) { //pressed
    press_time = millis();
    Serial.print("Start Timer: ");
    Serial.println(press_time);
    pressCount++;
    Serial.print("Press count: ");
    Serial.println(pressCount);
  } 
  else if(button1State == 4) { //released
    //turn off the led when released???
    //digitalWrite(ledPin, LOW);
    //Serial.println("LED Off - release");
    Serial.println("Button Released ");
  }
  //ONLY turn off the LED if it is already on AND time has elapsed
  else if(press_time != 0 && press_time + ON_DURATION < millis()) {
    Serial.print("Timeout!");
    Serial.println(millis());
    press_time = 0;
  }
  #ifdef DEBUG_MODE
  delay(200);
  #endif
}
