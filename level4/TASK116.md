[UP](Digital_Outputs_2.md)

---

# Digital Outputs - `PortOut`

The digital outputs of the microcontroller are organised into "ports". In the example above, all the pins were from `PORTB` and `PORTC`. There are a number of ports on this device, each with up to 16 pins (PORTA, PORTB, etc...)

Under the hood, `BusOut` is just a collection of `DigitalOut` types. When you assign a value, each bit is set in turn. Strictly speaking, they do not all change at once. We say the outputs are _skewed_ as they all change at slightly different times. It's very fast, so you don't notice. You would need to see an electronic instrument to observe the skew. However, it is there and for some applications this could become a problem. This is the cost of flexibility.

All pins from the same port share some circuitry and it is possible to  turn them ON and OFF at precisely the same time. For this, we can use `PortOut`.

| TASK-116 | | Details |
| --- | --- | --- |
| 1. | |Make Task-116 the active program |
| 2. | |Build the code and run to see what it does |
| 3. | |Use the debugger to step line by line to see which lines lights which LED |

Let's now look at the code in Task-118:

```C++
PortOut lights(PortC, 0b0000000001001100);

int main()
{
    //All OFF
    lights = 0;

    while (true)
    {
        lights = 0b0000000000000100;
        wait_us(1000000);
        lights = 0b0000000000001000;
        wait_us(1000000);
        lights = 0b0000000001000000;
        wait_us(1000000);                
    }
}
```

As it probably apparent, this code is less easy to read and interpret. First we create the instance of `PortOut`

```C++
PortOut lights(PortC, 0b0000000001001100);
```

* The first parameter is the port. 
* The second parameter is the "mask" - where there is a binary `1`, this signifies this pin to be an output

Therefore, as we have a `1` bit positions 2, 3 and 6, we are setting `PC_2`, `PC_3` and `PC_6` as outputs (as we did in the previous section).

To set the pins, we must also write a `1` in the correct binary position. So, to set just `PC_2` to a `1`, we must write a `1` in bit-position 2 as follows:

```C++
lights = 0b0000000000000100;
```

Note again the `0b` prefix on these numeric literal values is only valid for C++ and not C. If you use an older C compiler, you could write:

```C++
lights = 4;
```

Now complete the task

| TASK-116 | | Details |
| --- | --- | --- |
| 4. | | Modify the code to perform the following sequence |
|  | a | RED+YELLOW |
|  | b | YELLOW+GREEN |
|  | c | RED + GREEN |
| | | |


`PortOut` is not something we will use that often. It is only needed when we want switch outputs very fast and with no timing skew. For now, just be aware that both `PortOut` and `BusOut` exist.

## There is more to know... but not now
There are more ways to configure digital outputs, but these will be covered later in the course.

If you are curious, you might want to read about the following

* `DigitalInOut`
* `BusInOut`
* `PortInOut`

These type allow more advanced configurations, such as "OpenDrain", "Pull-up and Pull-down resistors" and "Bidirectional" communication.

---

[Next - Iteration: while-loops](TASK120.md)

