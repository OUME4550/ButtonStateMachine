/* Button StateMachine Example
 *  by: Jay Wilhelm (jwilhelm@ohio.edu)
 *  Purpose: Demonstrates a button up/down state machine
 *  where actions can be triggered at the press/release states
 */
//button states
#define ButtonState_Up      1
#define ButtonState_Pressed 2 
#define ButtonState_Down    3
#define ButtonState_Released 4
//map button high/low to up/down
#define ButtonRead_Up 1
#define ButtonRead_Down 2

#define ledPin    13
#define buttonPin 2
#define led2Pin   1

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  Serial.begin(115200);
  Serial.println("Welcome to the button press example");
}

int UpdateButtonState(int iButtonState, int iNewButtonRead)
{
  if(iButtonState == ButtonState_Up && iNewButtonRead == ButtonRead_Down)
    return ButtonState_Pressed;
  else if(iButtonState == ButtonState_Pressed)
    return ButtonState_Down;
  else if(iButtonState == ButtonState_Down && iNewButtonRead == ButtonRead_Up)
    return ButtonState_Released;
  else if(iButtonState == ButtonState_Released)
    return ButtonState_Up;
  return iButtonState;
}

int checkButton(int iButtonPin)
{
  int newButtonRead = digitalRead(iButtonPin);
  delay(10);
  int debounceButtonRead = digitalRead(iButtonPin);
  if(newButtonRead != debounceButtonRead)
    return -1;//button is not stable

  if(newButtonRead == LOW) //Button is active low, ie using pullup
    return ButtonRead_Down;
  return ButtonRead_Up;
}

void loop() {
  //init value of state machine
  static int button1State = ButtonState_Up;
  //keep track of the times a press occurs
  static unsigned int pressCount = 0;
  /*Serial.print("Current State: ");//debug prints
  Serial.print(button1State);
  Serial.print(" Button Read: ");
  Serial.println(checkButton(buttonPin));*/
  button1State = UpdateButtonState(button1State,
                        checkButton(buttonPin));  
  /*Serial.print("New State: ");//debug prints
  Serial.println(button1State);*/

  //check the states
  if (button1State == ButtonState_Pressed) {
    digitalWrite(ledPin, HIGH);
    pressCount++;
    Serial.print("Press count: ");
    Serial.println(pressCount);
  } 
  else if(button1State == ButtonState_Released) {
    digitalWrite(ledPin, LOW);
    Serial.println("Button Released ");
  }

  //PART 2, LED ON for 2.5s if button pressed + clear on release if < 2.5s
  static unsigned long lastPressTime = 0;
  if (button1State == ButtonState_Pressed)
  {
    lastPressTime = millis();
    digitalWrite(led2Pin, HIGH);
    Serial.println("#2 on");
  }
  else if (millis() - lastPressTime >= 2500 
          || button1State != ButtonState_Down)
  {
    digitalWrite(led2Pin, LOW);
  }
}


