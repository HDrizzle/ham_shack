/* Maximum power point tracking boost converter for charging LifePO4 12.8V Battery
Pins:
1. Unused
2. Boost converter MOSFET
3. ADC #2, used for battery voltage reading through voltage divider
4. GND
5. SDA
6. Unused
7. SCL
8. +3.3V
More info in MD file*/

// Ratio between current power and previous best power (or other way) that triggers re-calibration sweep
#define POWER_ERROR 1.2

// Power sweep settings
#define SWEEP_START 0
#define SWEEP_STEP 5
#define SWEEP_STEPS 19
#define SWEEP_STEP_TIME_US 1000

// Boost converter settings
#define PERIOD_US 100// 10 KHz
#define MOSFET_PIN 2

// Include INA219 library
#include <Adafruit_INA219.h>
// Create a current sensor object
Adafruit_INA219 ina219;

// Duty cycle in ms
uint8_t duty_cycle;
// Best power from most recent calibration, if power goes too far from this then re-calibrate
float latest_power_mw;
// Array for storing corresponding power for duty cycle
float[sweep_steps] power_sweep;
// For measuring power over exactly 1 cycle of the boost converter
float power_1_cycle_avg;
bool mosfet_is_on;
unsigned long current_micros;

// Flags
bool flag_sweep_mode;


void setup() {
  // put your setup code here, to run once:
  ina219.begin();
  pinMode(MOSFET_PIN, OUTPUT);
  mosfet_is_on = false;
  digitalWrite(MOSFET_PIN, mosfet_is_on);
  duty_cycle = 50;
}

void loop() {
  current_micros = micros();
  // Determine if the mosfet should be on or not
  int boost_cycle_remainder = current_micros / PERIOD_US;
  mosfet_is_on = boost_cycle_remainder < duty_cycle;
  digitalWrite(MOSFET_PIN, mosfet_is_on);
  //
}
