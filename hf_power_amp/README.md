# HF Power amplifier

This amplifier will use push-pull MOSFETs with selectable low-pass filters to eliminate harmonics.

## References

* Filter network math, Chebyshev filter table: https://home.sandiego.edu/~ekim/e194rfs01/lec17ek.pdf
* 2-port network ABCD parameters: https://resources.altium.com/p/advantages-abcd-parameters-analyzing-your-pcb
* QRP Labs experimental 50W 40m amp: https://qrp-labs.com/qcx/qro.html
* Filter design tool: https://markimicrowave.com/technical-resources/tools/lc-filter-design-tool/

## Output filters

| Band(s) | Freq Range (MHz) | Lowest harmonic (MHz) | Order | Ideal L/C Values | Actual C Values |
| - | - | - | - | - | - |
| 10, 12 | 24.89 - 29.7 | 49.78 | 5 | 452.5 nH, 130.5 pF, 674 nH, 130.5 pF, 452.5 nH |
| 15, 17 | 18.068 - 21.45 | 36.136 | 5 | 646.4 nH, 186.4 pF, 962.8 nH, 186.4 pF, 646.4 nH |
| 20 | 14 - 14.35 | 28 | 4 | 728.5 nH, 343.1 pF, 857.8 nH, 291.4 pF |
| 30, 40 | 7 - 10.15 | 14 | 7 | 680 pF, 870 nH, 970 pF, 920 nH, 970 pF, 870 nH, 680 pF |
| 60 | 5.3 - 5.4 | 10.6 | 5 | 2.514 uH, 724.8 pF, 3.744 uH, 724.8 pF, 2.514 uH |
| 80 | 3.5 - 4 | 7 | 5 | 3.394 uH, 9.785 pF, 5.055 uH, 9.785 pF, 3.394 uH |
| 160 | 1.8 - 2 | 3.6 | 5 | 6.787 uH, 1.957 nF, 10.11 uH, 1.957 nF, 6.787 uH |

For capacitors: Use silver mica

## Math for using NanoVNA to find component values

Solving for inductance given reactance, freq:

`Z = wL = 2*pi*F*L`, `L = Z/2*pi*F`

Solving for capacitance given reactance, freq:

`Z = 1 / wC = 1 / 2*pi*F*C`, `C = 1 / 2*pi*F*Z`

For 1.16 uH at 10 MHz: 73 ohms

For 480 pF at 10 MHz: 33 ohms