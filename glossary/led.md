[Glossary](/glossary/README.md)

---

# Light Emitting Diode (LED)

An electronic device that emits light when a current passes through it. As with any diode, electrical current can only pass in one direction (from the “anode” to the “cathode”). The schematic symbol for an LED is shown below (there are some variants. Sometimes the circle is missing). 

<img src="../img/LEDschematic.png" width="100px">

The anode typically has a longer lead as identified in the photo.

<img src="../img/LEDImage.png" width="100px">

Consider the LED circuit below. 

<img src="../img/LED_and_Resistor.png" width="300px">

The current `I` needs to be sufficient such that the LED light is sufficiently bright. We say this is now biased. There will be a voltage drop across the diode `V`<sub>`LED`</sub>. Note that this would not significantly rise if `I` was to rise (maybe by reducing `R`). 

The current needed for full brightness and the voltage drop `V`<sub>`LED`</sub> will vary with each device. You need to consider these parameters carefully before selecting an LED and the resistor `R`.

Note that if you try and pass current through an LED in the opposite direction (reverse biased), almost zero current will flow. In the circuit above, swapping the LED direction would mean that `V`<sub>`LED`</sub> &approx; `V`<sub>`out`</sub> and no light would emit.