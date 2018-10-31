#include <Mouse.h>
#include <Keyboard.h>

const int LED1 = 13;                // The LED indicates whether the mouse is on and activated
const int x_axis = 0;               // x-axis of the joystick on A0
const int y_axis = 1;               // y-axis of the joystick on A1
const int r2r = 2;                  // Buttons analog readout on A2

void setup()
{
  Serial.begin(9600);
  Mouse.begin();                    // Initialize Mouse 
  Keyboard.begin();                 // Initialize Keyboard 
    
  pinMode(x_axis, INPUT);
  pinMode(y_axis, INPUT);
  pinMode(r2r, INPUT);
  
  pinMode(LED1, OUTPUT);            // Arduino Onboard-Led
  digitalWrite(LED1, HIGH);         // Turn the LED on after booting
}




void loop()
{    
  int x_val = readJoystick(x_axis);                         // Read the thumbstick values
  int y_val = readJoystick(y_axis);
  if (x_val != 0)
  {
    Mouse.press(MOUSE_MIDDLE);
    while ((x_val != 0) || (y_val != 0))
    {
      Mouse.move(x_val, y_val, 0);                          // Move the mouse using the values 
      delay(10);   
      x_val = readJoystick(x_axis);                         // Read the thumbstick values
      y_val = readJoystick(y_axis);
    }
    Mouse.release(MOUSE_MIDDLE);
  }

  int r2r_value = analogRead(r2r);                          // Read the Button-R2R-Network value
  //Serial.println(r2r_value);
  switch(r2r_value)
  {
    case 1:
              // send command #1  Oben
              break;
    case 2:
              // send command #2  ESC
              break;
    case 3:
              // send command #3  CTRL
              break;
    case 4:
              // send command #4  Links
              break;
    case 5:
              // send command #5
              break;
    case 6:
              // send command #6
              break;
    case 7:
              // send command #7  Unten
              break;
    case 8:
              // send command #8  3D
              break;
    case 9:
              // send command #9  2D
              break;
    case 10:
              // send command #10 Rechts
              break;
    case 11:
              // send command #11 Home
              break;
    default:
              // do nothing, no button pressed
              break;
  }

                               // This delay adjusts the speed of the mouse; play with the value
  //Serial.println(" ");
}




int readJoystick(int axis)                                  // This function reads each axis of the thumbstick and adjusts them to usable values
{
  float value = map(analogRead(axis), 0, 1023, -20, 20);    // Read axis and map to -10 to 10
  if (value <= 1 && value >= -1)
  {                                                         // This conditional adjusts responsiveness, so if the thumbstick 
    return 0;                                               // only moves a little, it will return a value of zero, 1 is a good value
  }
  else 
  {
    return value;                                           // Return current value for mouse-move
  }
}
