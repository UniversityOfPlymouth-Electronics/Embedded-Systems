[UP](Digital_Outputs_2.md)

---

# Variables and Terminal Input
We saw how data can written to a terminal, but what about reading?

For this, we have a few methods but we will focus on just two of them:

* `getchar`
* `scanf`

> The example code is in `Task-112-Terminalnput`

| TASK | Details |
| --- | --- |
| 1 | Set `Task-112-Terminalnput` as the active project |
| 2 | Click View->Serial Monitor |
| 3 | Build and run the code - follow the instructions in the serial monitor |
| |

An extract from the code is shown below:

```C++
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);


int main()
{
    printf("\nTASK-112\n");

    //getchar
    char c1, c2;
    printf("\n\nPress a key\n");
    c1 = getchar();
    printf("You entered character %c which has the ASCII code %d\n", c1, c1);

    printf("\n\nPress another key\n");
    c2 = getchar();
    printf("You entered character %c which has the ASCII code %d\n", c2, c2);

    //scanf
    printf("\n\nTo set the delay (in ms), type in an integer number and press return\n");
    int delay_ms;
    int parsed = scanf("%d", &delay_ms);
    
    printf("You entered %d correct integer values. The value was %dms\n", parsed, delay_ms);

    // Stop
    while (parsed > 0) {
        wait_us(delay_ms * 1000);
        led1 = 1;
        led2 = 1;
        led3 = 1;
        wait_us(delay_ms * 1000);
        led1 = 0;
        led2 = 0;
        led3 = 0;        
    } 

    printf("Invalid - please restart and try again\n");
    while(1);    
}
```

## Reading a single character with `getchar`
The first of the serial input functions is `getchar`. This simple function simply waits until it receives a single character (from the serial terminal).

> Every time we press a key in the serial monitor, the equivalent ASCII character is sent to the Nucleo board.

We do this twice in the code:

```C++
char c1, c2;
printf("\n\nPress a key\n");
c1 = getchar();
printf("You entered character %c which has the ASCII code %d\n", c1, c1);

printf("\n\nPress another key\n");
c2 = getchar();
printf("You entered character %c which has the ASCII code %d\n", c2, c2);
```

Note how the value returned from getchar() is a single byte.


| TASK | Details |
| --- | --- |
| 1 | Use this code to find out the ASCII characters for the following symbols: *, %, £ and the space key. |

## scanf
Like `printf`, the `scanf` function is another large and complex function. Let's look at an example:

```C++
//scanf
printf("\n\nTo set the delay (in ms), type in an integer number and press return\n");
int delay_ms;
int parsed = scanf("%d", &delay_ms);

printf("You entered %d correct integer values. The value was %dms\n", parsed, delay_ms);
```

| TASK | Details |
| --- | --- |
| 1 | Run this code. When prompted, enter 500 |
| 2 | Repeat, but enter 500a |
| 3 | Repeat, but try and enter a500 |

The format string `%d` is looking to read characters and convert them to a decimal integer. This stops as soon as it notices an invalid character.

The value returned and stored in the `parsed` variable contains the number of successful conversation. For this example, typing in a number will return a `1`.

> Note the & ampersand before `delay_ms`
>
> The expression `&delay_ms` is the address of the variable `delay_ms` and NOT the value.
>
> By providing `scanf` with the address, it is able to modify the variable contents on your behalf. We call this an _in-line modification_.

If we enter a correct value, this sets both the ON and OFF time of the LEDs (in ms). 

| TASK | Details |
| --- | --- |
| 1 | Modify this code to read both ON and OFF time from the user |
| 2 | Update the flashing code to use both delays accordingly |


# Quiz
Please attempt the following Quiz before proceeding.

[Link to Quiz on the DLE](https://dle.plymouth.ac.uk/mod/quiz/view.php?id=977697)

Thank you.

---

[Next - GPIO Outputs: `DigitalOut`](TASK114.md)



# 