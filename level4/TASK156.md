[Up - Digital inputs](Digital_Inputs_1.md)

--- 

# Arrays
In this task, we experiment with arrays and use them to reduce the effects of signal noise.

Looking at the code in Task-156, once again, we use `AnalogIn`

```C++
AnalogIn ldr(AN_LDR_PIN);
```

An array is statically allocated to hold 100 16-bit samples: 

```C++
unsigned short samples[100];
```

In the main loop, we see an array being used to collect 100 samples _approximately_ every 1/100th of a second.

```C++
for (unsigned int m=0; m<100; m++) {
    unsigned short ldrVal   = ldr.read_u16();
    samples[m] = ldrVal;
    wait_us(10000);          // 10ms
}
```


| TASK156 | Arrays |
| --- | --- |
| 1. | Make Task156 the active program |
| 2. | Write some code at the top of the main function (just before the while loop) to write out all the samples in the array `samples`. Run the code to inspect the content. Reset the board (black push button) and repeat |
| -  | What do you notice about the data in the array each time? |
| 3. | Read all the comments in the code and tackle each sub-task: |
| a  | Write some code to calculate the mean value in the array |
| b  | Display the mean to 1 decimal place. How much does it vary under constant light conditions? |
| c  | Again, using hysteresis if you can, turn on the green LED when the LDR is covered with a sheet of (non conductive!) paper |

## Challenge (advanced) - moving average
In the example above, we perform what is often terms "block based processing".

* We acquire 100 samples
* We perform some mathematical operation
* Repeat

This means for every 100 input samples, we get 1 output.

An alternative is known as a **moving average**. It works as follows:

* You initialise an array with zeros (average will be zero)
* You read a sample
* You **update** the running sum
    * Add the newest sample to the sum
    * Subtract the oldest from the sum
* Update the array by overwriting the oldest sample in the array with the newest
* From the sum, you get the average (sum / 100.0)

This way, you get a new average with each new raw sample. We call this a **moving average**.

TASK: Write some code to measure a sample approximately every 1/100th of a second and print out the moving average.

---

[NEXT - Task 158 - C Strings](TASK158.md)
