# Building capacitors for LPF, using NanoVNA to test them

### Comparison to known capacitance

Known capacitor of 10,000 pF has -14j ohms of reactance @ 1 MHz which would give 11,400 pF, pretty good.

## Building capacitors

Trash bag material is polyethylene with K=2.25, [capacitor calculator](https://www.omnicalculator.com/physics/capacitance)

[Trash bag thickness](https://www.plasticmill.com/blogs/plasticmill/understanding-trash-bag-thickness), light max volts is 200 so should be fine even with this.

Plan is to use 2 strips of alimunim foil with a strip of trash bag material all rolled up.

Calibration for trash bag, 10,000 pF range: 41 pF/cm^2

| Area (cm^2) | Plate width | Plate height | Material | Reactance | Capacitance (pF) | Actual Reactance | Actual Capacitance (pF) |
| - | - | - | - | - | - | - | - |
| 200 (doubled) (CALIBRATION) | 5 | 20 | Trash bag | -19.4j @ 1MHz | 8,200 pF | - | - |
| 16.6 (doubled) | 2.07 | 4 | Trash bag | - | 680 pF | 77 (unsqueezed) | 207 pF (unsqueezed) |
| 23.7 (doubled) | 2.96 | 4 | Trash bag | - | 970 pF | - | - |

Squeezing with a clamp across the wood blocks can get the capacitance to the correct value so What I will do from now on is to mae them with slightly lower capacitance (like 80%) and then have a screw to tune each one.

## More correct capacitor construction

Calibration for trash bag, 100 pF range: 12.5 pF/cm^2 <- WORNG

970 pF / 8 cm * 3.9 cm = 31 pF / cm^2 (double area)

| Area (cm^2) | Plate width | Plate height | Material | Unsqueezed Capacitance (80%) (pF) | Capacitance (pF) | Reactance |
| - | - | - | - | - | - | - |
| 43.6 (doubled) | 3.6 | 6 | Trash bag | 544 pF | 680 pF |
| 62.2 (doubled) | 3.9 | 8 | Trash bag | 776 pF | 970 pF |