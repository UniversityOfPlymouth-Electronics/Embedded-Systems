[Up - Digital inputs](Digital_Inputs_1.md)

--- 

# C Strings
Strings are arrays of characters that typically form sentences or other human readable information. In the C programming language, the string is backed by an array of type `char` (8-bit characters).

> * The C-string is an array of characters
> * The all-important end-of-string character is 0 (which we can write as "\0") 
> * It is not uncommon for the array is to be larger than the string length

Strings are used for so many different purposes in computing, and that includes embedded systems. Examples include:

* Data from an electronics module (e.g. GPRS, Accelerometer or GPS)
* World Wide Web (WWWW) traffic
* Data encoded for transmission between different computers on a serial port
* Display output or keyboard input

More examples do exist. You might wonder why this is. Consider the hex value 0x12345678. This 32-bit number is 4 bytes long. 

Memory is organised into bytes (8-bit values), so in which order are the bytes to be stored in memory?

The answer? 

> **It depends on the CPU** and it is known as "endianness"

Now consider what might happen if we send such a 32-bit number from one machine to another (via a network, serial interface or storage device). 

> If you don't know the byte order of the recipient machine, there is a real risk the data will be corrupted.

Manufacturers of electronic modules do not know what CPU type will be interfaced to their module, so one popular solution is to "marshall" the data into a string format (for the sender) and at the receiving end, convert back to an integer (known as unmarshalling).

This is much safer as the recipient can convert strings into numbers using it's own (known) byte alignment. However, it comes with an overhead cost. Consider an example: 

* The HEX value 1234ABCD, which as a decimal is 4 bytes.
* Written as a human-readable string would be "1234ABCD" which is 9 ASCII characters (including the zero on the end).

So the string representation is 9 bytes instead of 4 in binary format. There is also the computational cost of converting from binary number to string and back again. However, it is so much safer and simpler that it commonly used.


## 1 - Printing a string
Let's now look at some common ways to work with strings in C, and later, C++. Let's start with creating and printing a string to the serial terminal:

| TASK158 | C Strings |
| --- | --- |
| 1. | Make Task158 the active program |
| 2. | Build and run the code in debug mode. |
| -  | Make sure you have the serial monitor visible |
| 3. | Step over the following lines |

```C++
//1. Printing a string
char str1[] = "Welcome to ELEC143";

//Displaying a string with printf
printf("%s\n", str1);

//Viewing a string as an array of characters
for (unsigned int n=0; n<sizeof(str1); n++) {
    printf("Character: %c\tASCII: %u\n", str1[n], str1[n]);
}
```

Now how a string is an array of characters:

```C++
char str1[] = "Welcome to ELEC143";
```

We can print a string using `printf` and the `%s` placeholder:

```C++
printf("%s\n", str1);
```

Or we can treat it as an array of characters:

```C++
for (unsigned int n=0; n<sizeof(str1); n++) {
    printf("Character: %c\tASCII: %u\n", str1[n], str1[n]);
}
```

Note how `%c` is used to display as a character whereas `%d` shows you the actual decimal value.

> **Question**: What is the last value in the string any why?

### 2. The null character
To stress the importance of the decimal zero (`"\0"`), consider the next few lines

| TASK158 | C Strings |
| --- | --- |
| 4. | Step over the following lines |
| -  | Can you explain the output? |

```C++
char str2[] = "Welcome\0 to ELEC143";
printf("%s\n", str2);
for (unsigned int n=0; n<strlen(str2); n++) {
    printf("Character: %c\tASCII: %u\n", str2[n], str2[n]);
}
```

Firstly, the `printf` statement stopped after the word "Welcome"

```C++
printf("%s\n", str2);
```

This is because the `printf` function encountered a decimal zero, which signifies the **end of string**. You can add a decimal zero using the control character `"\0"` as shown above.

Also, note the use of the `strlen` function in the for-loop. In this case, it counted 7 characters.

> **Note** how `strlen` does not count the zero on the end!!

| TASK158 | C Strings |
| --- | --- |
| 5. | Step over the following lines |
| -  | Can you predict the output of the last two lines? |

```C++
char str3[16];
strcpy(str3, "Hello");
printf("%s\n", str3);
printf("Size: %d\n", sizeof(str3));
printf("String length: %d\n", strlen(str3));
```

Here we see the string copy function `strcpy` being used to copy one string to another.

```C++
strcpy(str3, "Hello");
```

The first parameter is the *destination*, and the second is the *source*.

> **Note** that strcpy is potentially very dangerous. What would happen if the source string was longer than the destination?
>
> Hint - bad things!

Note also the difference between `sizeof` and `strlen`.

* `sizeof` returns the number of bytes in the array
* `strlen` counts (from the beginning) the number of characters until it finds a zero.


Another example of `strcpy` is shown in the following lines, only the source string is `const`

```C++
const char str4[] = "The moon is made of cheese";
char str5[64];
strcpy(str5, str4);
printf("%s\n", str5);
printf("Size: %d\n", sizeof(str5));
printf("String length: %d\n", strlen(str5));   
//strcpy(str4, str5);   //Uncomment this
```

> The keyword `const` tells the compiler to now allow any code that tries to modify the variable after it has been initialised. It becomes read-only
>
> In fact, adding `const` on the front makes it a different *type*

If you uncomment the last line shown above, you will find that the code does not compile. This is because `strcpy` takes a first parameter of type `char[]` and not `const char[]` (which is different)

This is known as **type safety** and is one of the safety features of the C and C++ languages.

## 4 - Marshalling data
Earlier it was mentioned that data can be converted to a string in order to send it to another device. One way to do with is with `sprintf`.

> We have already met `printf`, which is used to construct strings and send them to the serial terminal. `sprintf` does much the same, only the destination is another string.

| TASK158 | C Strings |
| --- | --- |
| 6. | Step over the following lines |
| -  | Can you predict the output of the last two lines? |

```C++
//4. Marshalling binary data with sprintf
char str6[8];
for (unsigned int n=0; n<3; n++) {
    unsigned int x = rand();
    x = x % 65536; //16 bit (2 bytes)
    sprintf(str6, "I guess %X", x);
    printf("%s\n", str6);
}
```
The following two lines produce a random integer in the range 0 ... 65535

```C++
unsigned int x = rand();
x = x % 65536; //16 bit (2 bytes)
```

The following line is the focus here:

```C++
sprintf(str6, "I guess %X", x);
```

This has an additional first parameter, a string.

> Note that the name of a string, without any square brackets `[]` represents the **address** of the first element

So instead of sending the output to a serial interface (and hence our terminal in Mbed Studio), it is written to a C string `str6`

For confirmation, this is then displayed, but equally, it might be written to a network interface etc..

```C++
printf("%s\n", str6);
```

## 5 - Unmarshalling
The opposite to marshalling data into strings is unmarshalling, which involves converting strings back to native binary data types.

| TASK158 | C Strings |
| --- | --- |
| 7. | Step over the following lines |
| -  | Can you explain the output? |

```C++
char strList[][8] = {   "1024", 
                        "32768",
                        "1234",
                        "65535"
                        };

unsigned int val;
for (unsigned int n=0; n<4; n++) {
    sscanf(strList[n], "%u", &val);
    printf("Found integer: %u\n", val);
}
```

This shown an example of a 2D array (a topic covered later), which is an array of arrays.

```C++
char strList[][8] = {   "1024", 
                        "32768",
                        "1234",
                        "65535"
                        };
```

To convert a string to a number (assuming it is written as a valid number) is known as string parsing. One method is to use the `sscanf` function. This is very similar to the `scanf` function we met earlier (for reading the serial terminal), only the input source is a string.

```C++
sscanf(strList[n], "%u", &val);
```

The first parameter is the source string. Next we have the format string "%u" which indicates what to search for. In this case, we are looking for an `unsigned integer`. Finally, we pass the address of where to write the result.

> Note the use of the `&` to obtain the address of a variable

## 6 - Comparing String with `strcmp` 
A common mistake is try and compare two strings using `==`. This will NOT work as it will compare their addresses (are are likely to always be different).

When we wish to compare two strings as having the same characters, we must use one of the string compare functions. The simplest is `strcmp` 

## 5 - Unmarshalling
The opposite to marshalling data into strings is unmarshalling, which involves converting strings back to native binary data types.

| TASK158 | C Strings |
| --- | --- |
| 8. | Allow the code to continue |
| -  | Type in either red, blue or green and observe the outputs |

```C++
char inputStr[64];
while (true) {
    printf("What colour?\n");
    scanf("%s", inputStr);

    if (strcmp(inputStr, "red") == 0) {
        redLED = !redLED;
    }
    else if ( strcmp(inputStr, "green") == 0 ) {
        greenLED = !greenLED;
    }
    else if ( strcmp(inputStr, "blue" ) == 0) {
        blueLED = !blueLED;
    }
    else {
        printf("Please specify red, green or blue\n");
    }
}
```

Now how `strcmp` returns a difference between two strings. A difference of 0 indicates a match.

## DANGER
Strings follow the convention of searching for a zero to mark the end of an operation. Furthermore, performance is a priority in C and C++, so there is no checking to see if you have run off the end of an array, whether reading or writing.

`strcpy` is very dangerous. 
* If the destination is too small to hold a copy of the source, it will over-flow the array and likely corrupt other variables
* If the source is missing a zero, this can be extensive!

Consider `strncpy` instead, which has an additional parameter to limit the number of characters.

`strlen` is often misunderstood - it returns the length of a string but this does NOT include the zero on the end. Strings must be large enough to also hold the zero. 

`strcmp` returns a zero when two strings match, which is a boolean for `false`. Hence the following would not work:

```C++
//This is probably wrong!!!
if (strcmp(str1, str2)) 
{ 
    // do someting 
}
```

| TASK158 | C Strings |
| --- | --- |
| 9. | Look up the syntax of `strncpy` |
| 10. | Find all occurrences of `strcpy` in the code and replace with the safer `strncpy` |

# C++ Strings
Before we move onto another topic, let's take a quick look at C++ strings.

Although we are not yet learning to write C++, we are "consuming it" every time we use custom types such as:

* `DigitalOut`
* `DigitalIn`
* `Timer`
* `Ticker`
* etc..

Another C++ type is `string`. I don't want to go into great depth, but as you may encounter this, it is good to have seen it once.

| TASK159 | C++ Strings (OPTIONAL) |
| --- | --- |
| 1. | Make Task159 the active program |
| 2. | Build and run the code in debug mode. |
| -  | Make sure you have the serial monitor visible |
| 3. | Step through the code to try and understand what it does |

Let's pick some key points:

## `cout`
We see this a lot. This is a C++ object used to write data to a serial terminal. For example:

```C++
int x = 1234;
cout << "Hello ";
cout << "World:";
cout << x << endl;
```

Note the `<<` operator as a new meaning when used with `cout`. Also the `endl` is the end of line character (`\n` for C)

In the following code, we both convert a integer to a string and then join two strings together:

```C++
string str1 = "Hello World: " + to_string(x);
cout << str1 << endl;
```

Again, the operator `+` is redefined for `string` types. This is a feature of C++ that we will study in year 3.

We can also read from the serial terminal using `cin`:

```C++
cin >> x;
cout << "You typed: " << x << endl;
```

Converting C++ strings to C is achieved using `c_str()`

```C++
string elec143 = "Welcome to ELEC143"; 
const char *str = elec143.c_str();
```

And unlike C, you *can* compare C++ strings with `==`

```C++
cin >> strInput;
if (strInput == "red") {
    redLED = !redLED;
}
```

There is much more you can do with C++ strings, but this is just an introduction.

## Header Files
We've not talked much about header files, except to say that when you uses `#include <filename>`, you essentially paste the copy of the file (name <filename>) into your code.

So first, not the following two lines:

```C++
#include <iostream>
using namespace std;
```

The header file for all the C++ standard input / output is `iostream`. 

Without the second line, we would have to prefix every `cout`, `cin` and `endl` with the prefix `std::`

> This prefix is known as a `namespace` and is a prefix designed to avoid *name collisions*.
>
> If we know which prefix to use, we can have it automatically added with the `using` directive

## Challenge
There is a clever function in the C standard library called `strtok`. This is used to read parts of string separated by a _delimiter_, such as a comma or space.

> You can read about it here: https://linux.die.net/man/3/strtok_r

Task-159 has some starter code which takes a string, with instructions separated by commas.

* Build and step through Task-160 to see what it does

Using string functions described about, you should do the following:

Use each string to switch on a specific LED

When you find a _wait_ string, do the following:

* wait for 1s,
* then turn OFF all LEDs 

Use `strcmp` as part of your solution.


---

[Up - Digital inputs](Digital_Inputs_1.md)

