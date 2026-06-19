# Solar LifePO4 battery charger, boost converter

## Parts

* 3.3V regulator for INA219, ATtiny85
* Boost converter circuit (simple)
* INA 219 for current/voltage
* ATtiny85

## Specs

Switching frequency: 5 KHz
Maximum current (assume buildup from 0 through inductor over 1 period): 500 mA
Inductor: using `L = V*secs/A`, `V=2, secs = 2e-4, A  0.5`, `L = 0.8 mH`

## Maximum power point

Since the whole idea is to get the most power from whatever solar panel gets attached, we don't care about output V (unless the battery is full).

Inputs to the program will be average input voltage/current

The only output will be duty cycle to the timing logic which will somehow relate to current.