**Description:**

NeoPyramid is a project inspired by Leonardo Da Vinci's 1487 model of a tank, considered by some as a precursor to modern tanks. Our innovation centers around a moving pyramid-shaped object equipped with a rubber band shooter that activates upon detecting obstacles, akin to a target.

To construct the foundation, we utilized interconnected ball bearings held together by popsicles, providing stability and mobility. The central component comprises a tire powered by a DC motor, enabling forward and backward movement. This tire is coupled with a servo motor for lateral navigation. Another servo and DC motor are integrated to operate the rubber band shooter, triggered by the HC-SR04 sensor upon detecting a target. The sensor relays target detection and distance information via an OLED screen. The entire system is orchestrated by an Arduino Nano programmed in C++ using Arduino IDE.

**How We Built It:**

We began by designing the framework, incorporating ball bearings and popsicles to form the pyramid's base. Next, we installed the DC motor and servo mechanisms to facilitate movement and steering. The rubber band shooter assembly, comprising a servo, DC motor, and HC-SR04 sensor, was meticulously integrated. Wiring and connections were carefully established to synchronize all components. Finally, we programmed the Arduino Nano to orchestrate the operation of motors, sensors, and the OLED screen.

**What We Learned:**

Through NeoPyramid, we gained invaluable insights into mechanical design, sensor integration, and microcontroller programming. Managing multiple components and ensuring seamless coordination provided us with practical experience in system integration. Additionally, troubleshooting challenges during the construction process enhanced our problem-solving skills.

**Challenges Faced:**

One of the primary hurdles we encountered was configuring the WiFi module and establishing a stable wireless connection within the stringent 24-hour time frame. Managing the complexities of integrating various components within this limited time posed significant challenges. However, through perseverance and collaboration, we successfully navigated these obstacles to realize our project's vision.

**Tools/Equipment/Languages/Platforms Used:**

- Arduino Nano
- DC motors
- Servo motors
- HC-SR04 sensor
- OLED screen
- Ball bearings
- Popsicles
- C++ programming language
- Arduino IDE
