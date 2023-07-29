ardperf
========

PC/server (Disk/CPU/RAM usage) performance real-time monitor with
Arduino LCD screen.

Example:

![ExampleImage][ExampleImage]

Hardware
--------

### Components ###

- Arduino UNO
- LCD screen (16x2)
- Jumper wires

### Schematic ###

![SchematicImage][SchematicImage]

| LCD | Arduino |
|-----|---------|
| VSS | GND     |
| VDD | 5V      |
| V0  | 6       |
| RS  | 12      |
| RW  | GND     |
| E   | 11      |
| D4  | 5       |
| D5  | 4       |
| D6  | 3       |
| D7  | 2       |
| A   | 5V      |
| K   | GND     |

Software
--------

Monitoring is done through a serial connection between the host and the Arduino.

Application `ardperf` must be running on the host that sends statistics to the
corresponding serial interface (e.g. `/dev/ttyUSB0`).
Arduino UNO listens to the serial interface and if data is received,
it displays it on the LCD screen.

### Dependencies ###

- [Python 3.10](https://www.python.org/downloads/)
- [Arduino IDE](https://www.arduino.cc/en/software)

### Installation ###

1.  Upload sketch [`ardperf.ino`][SketchSource] to Arduino UNO
    using Arduino IDE.

2.  Install [`ardperf.py`][ApplicationSource] application:

    ```sh
    python3 -m pip install "git+https://github.com/endygamedev/ardperf.git"
    ```

### Usage ###

Example of running an application to send statistic to Arduino:

```sh
python3 -m ardperf \
    --device=/dev/ttyUSB0 \
    --verbose
```

Mandatory argument `--device` specifies the path to serial interface
of the host.

Optional `--verbose` argument specifies whether to output statistics to STDOUT.

License
-------

ardperf is made available under the terms of either the GPL-3.0 License.
See the [LICENSE][LicenseFile] files for license details.

[SketchSource]: ./ardperf.ino
[ApplicationSource]: ./ardperf.py
[ExampleImage]: ./doc/figures/example.jpg
[SchematicImage]: ./doc/figures/schematic.png
[LicenseFile]: ./LICENSE
