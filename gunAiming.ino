#include <Servo.h>
#include <math.h>
#include <U8glib.h>
#include <NewPing.h>

// OLED
#define CS 7
#define DC 9
#define RES 10
#define MOSI 11
#define CLK 12

// HC-SR04 pins (ultrasonic sensor)
#define TRIGGER_PIN A1
#define ECHO_PIN A2

// Objects
U8GLIB_SH1106_128X64 u8g(CLK, MOSI, CS, DC, RES);
NewPing sonar(TRIGGER_PIN, ECHO_PIN);

unsigned long lastDisplayChange = 0; // Variable to store the last time the display changed
bool showTank = true; // Flag to control which display to show

// declaring servos for control
Servo steering;
Servo gun_elevator;
Servo gun_rotator;
Servo gun_trigger;


// pin for MOSFET to control the DC motor
const int mosfetPin = 2;

//-----------------------------------------------------------------------------> CODE BUZZER TO A0
const int buzzerPin = A0;
//initial orientations of the servo motors
int steering_pos = 180;
int gun_elevation = 90;
int gun_rotation = 0;
int trigger = 90;

//accn due to gravity and initial projectile velocity values
double g = 9.81;
double speed = 7.62;

//keep track of no. of rubber bands loaded on the gun
int mag_capacity = 2;

//set normal firing range to 1m in normal mode
int firing_range = 100;





void setup() {
  Serial.begin(9600); // Initialize serial communication

  // Initialize the OLED display
  u8g.setFont(u8g_font_unifont);
  u8g.setColorIndex(1); // Set color to white

  //remember to map the servos and main wheel transistors to pins here
  steering.attach(4);
  gun_rotator.attach(5);
  gun_elevator.attach(6);
  gun_trigger.attach(8);


  //buzzer pin
  pinMode(buzzerPin, OUTPUT);
}





void readSensorValue() {
  // Display tank ASCII art on the OLED display
  u8g.drawStr(0, 2, "        ___");
  u8g.drawStr(0, 12, "       /   \\");
  u8g.drawStr(0, 22, "=======\\   /");
  u8g.drawStr(0, 32, "  ------   ---"); // Placeholder for distance value
  u8g.drawStr(0, 45, " / NeoPyramid \\");
  u8g.drawStr(0, 54, " \\            /");
  u8g.drawStr(0, 93, " \          /");
  u8g.drawStr(0, 65, "  \\(  )--(  )/ ");
  
}

void playTone(int frequency, int duration) {
analogWrite(buzzerPin, 128);  // 50% duty cycle (range: 0 to 255)
delay(duration);
analogWrite(buzzerPin, 0);    // Turn off the buzzer
}

void displayHello(int distance) {
  // Display distance measurement on the OLED display

  if (distance <= firing_range) {
    playTone(5000, 500);
  u8g.drawStr(0, 12, "Target Detected!   ");
  u8g.drawStr(0, 42, "  Distance to");
  u8g.setPrintPos(0, 60); // Set the print position
  u8g.print("  Target: ");
  u8g.print(distance);
  u8g.print(" cm");
}

  else {
    u8g.drawStr(0, 12, "Area Secure");
  }
}
// function to turn the DC motor with wheel on
void moveWheel() {
  digitalWrite(mosfetPin, HIGH);   //--------------------------------------------> remember to use the correctly mapped pin

}

//function to turn the DC motor with wheel off
void stopWheel() {
  digitalWrite(mosfetPin, LOW);    //--------------------------------------------> remember to use the correctly mapped pin
}

// function to rotate the gun on its own axis
void rotateGun(int rotation_speed) {
  for (gun_rotation = 0; gun_rotation <= 345; gun_rotation += 1) {
      gun_rotator.write(gun_rotation);
      delay(rotation_speed);
      }
  delay(2*rotation_speed);
  for (gun_rotation = 345; gun_rotation >= 0; gun_rotation -= 1) {
        gun_rotator.write(gun_rotation);
        delay(rotation_speed);
      }
}

// function to change the angle of elevation of the gun
void elevateGun() {
  for (gun_elevation = 90; gun_elevation >= 60; gun_elevation -= 1) {
    gun_elevator.write(gun_elevation);
    delay(20);
  }
  for (gun_elevation = 60; gun_elevation <= 160; gun_elevation += 1) {
    gun_elevator.write(gun_elevation);
    delay(20);
  }
  for (gun_elevation = 160; gun_elevation >= 90; gun_elevation -= 1) {
    gun_elevator.write(gun_elevation);
    delay(20);
  }
}

// function to adjust angle of elevation depending on distance from target
void aimGun(double range) {
  int new_angle = int (0.5*asin(9.81*range/(speed*speed)));
  if (new_angle > gun_elevation) {
    for (int i = gun_elevation; i <= new_angle; i += 1) {
      gun_elevator.write(i);
      delay(8);
    }
  }
  else {
    for (int i = gun_elevation; i >= new_angle; i -= 1) {
      gun_elevator.write(i);
      delay(8);
    }
  }
  gun_elevation = new_angle;
}

void engageGun() {
  if (mag_capacity == 2) {
    gun_trigger.write(35);
    delay(300);
    gun_trigger.write(90);
    mag_capacity -= 1;
  }
  if (mag_capacity == 1) {
    gun_trigger.write(145);
    delay(300);
    gun_trigger.write(90);
    mag_capacity -= 1;
  }
}

void turnLeft() {
  if (steering_pos > 90) {
    for (int i = 0; i < 90; i+= 1) {
      steering_pos -= 1;
      steering.write(steering_pos);
      delay(15);
    }
  }

  else {
    for (int i = 0; i < 270; i += 1) {
      steering_pos += 1;
      steering.write(steering_pos);
      delay(10);
    }
  }
}

void turnRight() {
    if (steering_pos < 270) {
    for (int i = 0; i < 90; i+= 1) {
      steering_pos += 1;
      steering.write(steering_pos);
      delay(15);
    }
  }
  else {
    for (int i = 0; i < 270; i += 1) {
      steering_pos -= 1;
      steering.write(steering_pos);
      delay(10);
    }
  }
}

void turnAround() {
  if (steering_pos <= 180) {
    for (int i = 0; i <180; i += 1) {
      steering_pos += 1;
      steering.write(steering_pos);
      delay(10);
    }
  }
  else {
    for (int i = 0; i <180; i += 1) {
      steering_pos -= 1;
      steering.write(steering_pos);
      delay(10);
  }
}
}
double toDegrees (double radians) {
  return radians * 180/M_PI;
}




void loop() {

//=======================================================================================================================
  unsigned long currentTime = millis(); // Get the current time

  delay(3000);
  // Check if it's time to change the display
  if (showTank && currentTime - lastDisplayChange >= 2000) {
    // Change to displaying the other text
    showTank = false;
    lastDisplayChange = currentTime;
  } else if (!showTank && currentTime - lastDisplayChange >= 8500) {
    // Change to displaying the tank again
    showTank = true;
    lastDisplayChange = currentTime;
  }

  // Measure distance using HC-SR04
  int distance = sonar.ping_cm();

  // Update OLED display
  u8g.firstPage();
  do {
    if (showTank) {
      readSensorValue();
    } else {
      displayHello(distance);
      
    }
  } while (u8g.nextPage());

  // Delay before next iteration
  delay(100); // Adjust delay if needed to control the switching speed


//=======================================================================================================================
  // delay(1000);
  if (Serial.available() > 0) {
    char incomingChar = Serial.read(); // Read the incoming character

// Going Forward (KEY: W)
    if(incomingChar == 'W'|| incomingChar == 'w') {
    
      moveWheel();
      delay(15);
      rotateGun(20);
      elevateGun();
      delay(200);
    }
// Turning Left (KEY: A)
    if (incomingChar == 'A' || incomingChar == 'a') {
      stopWheel();
      delay(15);
      turnLeft();
      moveWheel();
      rotateGun(20);
      elevateGun();
      delay(200);
    }

// Stopping/Reversing (KEY: S)
    if (incomingChar == 'S' || incomingChar == 's') {
      rotateGun(20);
      elevateGun();
      if (mosfetPin == LOW) {
        turnAround();
      }
      else {
        stopWheel();
      }
      delay(200);
    }
// Turning Left (KEY: D)
    if(incomingChar == 'D' || incomingChar == 'd') {
      stopWheel();
      delay(15);
      rotateGun(20);
      elevateGun();
      turnRight();
      moveWheel();
      delay(200);
    }

// Alert Mode toggle (KEY: X)
    if (incomingChar == 'X' || incomingChar == 'x') {
      if (firing_range == 100) {
        rotateGun(10);
        firing_range = 150;
        //print 'ALERT MODE ON' on OLED screen

      }

      else {
        rotateGun(20);
        firing_range = 100;
        //print 'ALERT MODE OFF' on OLED screen
      }
      elevateGun();
      if (mosfetPin == HIGH) {
        digitalWrite(mosfetPin, HIGH);
      }

      else {
        digitalWrite(mosfetPin, LOW);
      }
      delay(200);
    }

// Engage Feature (KEY: E)
    if (incomingChar =='E' || incomingChar == 'e') {
      if (distance < firing_range) {
      if (mag_capacity > 0) {
      stopWheel();
      aimGun(distance);
      engageGun();
    }
      
    delay(200);
    } 
    }
    delay(1000);
  }
}
