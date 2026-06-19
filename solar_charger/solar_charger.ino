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

// Include INA219 library
#include <Adafruit_INA219.h>
// Create a current sensor object
Adafruit_INA219 ina219;

// Ratio between current power and previous best power (or other way) that triggers re-calibration power sweep
#define POWER_ERROR_RATIO 1.2

// Power sweep settings, in microseconds
#define SWEEP_START 0
#define SWEEP_STEP 10
#define SWEEP_STEPS 19
#define SWEEP_STEP_TIME_US 2000

// Boost converter settings
#define PERIOD_US 200// 5 KHz
#define MOSFET_PIN 2
// For average power in case filtering doesn't work well, these must multiply to `PERIOD_US`
#define POWER_SAMPLE_INTERVAL_US 20
#define POWER_SAMPLES 10

// Duty cycle in ms
int duty_cycle;
// Best power from most recent calibration, if power goes too far from this then re-calibrate
float latest_sweep_best_power_mw;
// Array for storing corresponding power for duty cycle
float power_sweep_data[SWEEP_STEPS];
bool mosfet_is_on;
// For measuring power over exactly 1 cycle of the boost converter
float power_sample_sum;
float power_sample_avg;
int current_power_samples;

// Timing flags
unsigned long current_micros;
unsigned long last_power_sample_micros;
unsigned long sweep_last_step_micros;

// Flags
bool flag_sweep_mode;
int sweep_current_step;

void setup() {
  // put your setup code here, to run once:
  ina219.begin();
  pinMode(MOSFET_PIN, OUTPUT);
  mosfet_is_on = false;
  digitalWrite(MOSFET_PIN, mosfet_is_on);
  duty_cycle = 50;
  current_power_samples = 0;
}

void loop() {
  current_micros = micros();
  // Determine if the mosfet should be on or not
  int boost_cycle_remainder = current_micros / PERIOD_US;
  mosfet_is_on = boost_cycle_remainder < duty_cycle;
  digitalWrite(MOSFET_PIN, mosfet_is_on);
  // Check last power sample
  if((current_micros - last_power_sample_micros) > POWER_SAMPLE_INTERVAL_US) {
    last_power_sample_micros += POWER_SAMPLE_INTERVAL_US;
    power_sample_sum += ina219.getPower_mW();
    current_power_samples++;
    // If all samples have been taken for boost period, find average
    if(current_power_samples == POWER_SAMPLES) {
      current_power_samples = 0;
      power_sample_avg = power_sample_sum / ((float)POWER_SAMPLES);
    }
  }
  // Sweep or normal mode
  if(flag_sweep_mode) {
    // Time to increase the duty cycle and record previous duty cycle avg power
    if((current_micros - sweep_last_step_micros) > SWEEP_STEP_TIME_US) {
      sweep_last_step_micros += SWEEP_STEP_TIME_US;
      power_sweep_data[sweep_current_step] = power_sample_avg;
      sweep_current_step++;
      duty_cycle = SWEEP_START + (SWEEP_STEP * sweep_current_step);
      // If end of sweep
      if(sweep_current_step == SWEEP_STEPS) {
        // Set flag
        flag_sweep_mode = false;
        // Find highest value and corresponding index in `power_sweep_data`
        int best_i = 0;
        latest_sweep_best_power_mw = 0;
        for(int i = 0; i < SWEEP_STEPS; i++) {
          if(power_sweep_data[i] > latest_sweep_best_power_mw) {
            best_i = i;
            latest_sweep_best_power_mw = power_sweep_data[i];
          }
        }
        // Find duty cycle from `best_i`
        duty_cycle = SWEEP_START + (SWEEP_STEP * best_i);
      }
    }
  }
  // Monitor power
  else {
    // Tiny additions to prevent division by 0
    if((power_sample_avg + 0.1) / (latest_sweep_best_power_mw + 0.1) > POWER_ERROR_RATIO || (latest_sweep_best_power_mw + 0.1) / (power_sample_avg + 0.1) > POWER_ERROR_RATIO) {
      // Enter sweep mode, setup all the flags
      flag_sweep_mode = true;
      sweep_last_step_micros = current_micros;
      sweep_current_step = 0;
      duty_cycle = SWEEP_START;
    }
  }
}
