/* Button StateMachine Example
 *  by: Jay Wilhelm (jwilhelm@ohio.edu)
 *  Purpose: Demonstrates a button up/down state machine
 *  where actions can be triggered at the press/release states
 */


#define ledPin    13
#define buttonPin 2

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
  if(newButtonRead != secondButtonRead)//make sure there is no bouncing
    return;
  else
  {
    //update the state machine
    if(button1State == 1 && newButtonRead == LOW)
      button1State = 2;
    else if(button1State == 2)
      button1State = 3;
    else if(button1State == 3 && newButtonRead == HIGH)
      button1State = 4;
    else if(button1State == 4)
      button1State = 1;
  
    //do something with the state data
    if (button1State == 2) {
      digitalWrite(ledPin, HIGH);
      pressCount++;
      Serial.print("Press count: ");
      Serial.println(pressCount);
    } 
    else if(button1State == 4) {
      digitalWrite(ledPin, LOW);
      Serial.println("Button Released ");
    }
  }
}
