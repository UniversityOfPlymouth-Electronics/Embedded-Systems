[UP](Digital_Outputs_2.md)

---

# Variables and Terminal Output
Variables are one of the most important concepts in most programming languages. The vast majority of programming languages used today have the concept of a variable.

A variable is a entity that stores some information, such that it can be modified and read when required. They are typically stored at an _address_ in the computer memory, and are often referred to by a meaningful name of your choice. You do not usually need be concerned with the actual physical address.

| TASK | Details |
| --- | --- |
| 1 | Set `TASK-110-Variables` as the active project |
| 2 | Build the project |
| 3 | Click the menu View->Serial Monitor |
| 4 | Now debug the code, stepping over each line. Observe the output and try to understand what each line does. Some of the output might be a little surprising |
| | 

The code is shown below:

```C++
//This is a 128-bit constant - specified in hex
const long long NN = 0x12345678ABCD0001LL;

int main()
{
    printf("\nTASK-110\n");

    // Integer
    int count = 0;
    printf("count = %d\n", count);

    // Add one to count
    count = count + 1;
    printf("New value of count = %d\n", count);

    // Char
    char character;
    character = 'A';
    printf("The character %c has the ASCII code %d\n", character, character);

    // Short
    short shortCount = 32767;
    printf("The value of shortCount is %hd\n", shortCount);
    shortCount = shortCount + 1;
    printf("add 1 and shortCount is %hd\n", shortCount);

    // Long long
    printf("A very large number %lld\n", NN);
    printf("A very large number in hex %llX\n", NN);

    // float 
    float pi_float = 3.14159265358979323846;
    printf("The value of pi is approximately %f\n", pi_float);

    // double
    double pi_double = 3.14159265358979323846l;
    printf("The value of pi is approximately %lf\n", pi_double);

    // Data type sizes (in bytes)
    printf("Size of a char is %d bytes\n", sizeof(char));
    printf("Size of a short is %d bytes\n", sizeof(short));
    printf("Size of a int is %d bytes\n", sizeof(int));
    printf("Size of a long is %d bytes\n", sizeof(long));
    printf("Size of a long long is %d bytes\n", sizeof(long long));
    printf("Size of a float is %d bytes\n", sizeof(float));
    printf("Size of a double is %d bytes\n", sizeof(double));

    // Stop
    while (true);   
}
```

The `printf` function (from the standard C language library) is very versatile. It's name is short for "print formatted". Let's look at this code in steps and try to (i) better understand and (ii) resolve any issues.

## Constant Strings
The following line simply writes a string to the terminal:

```C++
printf("\nTASK-110\n");
```

Note the `\n` characters. This tells the terminal to start a new line.

> Characters preceded by the back-slash `\` indicate a **control character**. So `\n` is a special code for new-line, which is different from the human-readable character `n`. If you actually want to write a back-slash, write `\\` instead.

This is useful, but the real power of `printf` comes when you include placeholders, making strings **dynamic**.

| TASK | Details |
| --- | --- |
| 1 | Add another newline at the end of the string |
| 2 | Run the code and check the output is what you expect |
| |


## Printing variables
Consider the following two lines:

```C++
int count = 0;
printf("count = %d\n", count);
```

The first line creates a variable in the computer memory. 
* It's **type** is an integer `int`
* It's **value** is initialised to 0
* We refer to its value using the identifier `count`
* We don't yet know (or need) it's address in memory

Note how the value of count is substituted into the string.

Consider the next two lines:

```C++
count = count + 1;
printf("New value of count = %d\n", count);
```

The first line modified the variable count.

* The expression on the right-hand-side `count + 1` is evaluated first
* The result of the right-hand-side is copied over the left.

> **Question**: Note the output from this. What value is displayed?

| TASK | Details |
| --- | --- |
| 1 | Can you initialise `count` to a larger value, such as 10 |
| 2 | Modify the code to add 2 to the count |
| 2 | Run the code and check the output is what you expect |
| |

## ASCII characters and `char`
All characters displayed in the terminal are just numbers. These are converted into small images by the terminal to make them human readable. Each character has a code, known as it's [ASCII code](https://en.wikipedia.org/wiki/ASCII).

> There are many terminal types that evolved over the history of computing. We will not focus on this as it is documented well elsewhere. 

Now consider the code:

```C++
char character;
character = 'A';
printf("The character %c has the ASCII code %d\n", character, character);
```

* The first line creates a variable of type `char`. This is a single byte (8-bit) value which is large enough to hold a single character
* The second line set the value of this variable to the character literal `A`. The single quotes tells the compiler this is a character, and it is converted into the ASCII code for the letter `A`
* The third line has two placeholders, but this time we use `%d` (decimal) and `%c` (character)

> **Question**: Note the output. What is the ASCII code for the letter `A`?

We see how `printf` and it's placeholders can be used to control the display and formatting of variable data.

| TASK | Details |
| --- | --- |
| 1 | Change the second line to read `character = 65;` |
| 2 | Rerun the code - has anything changed?
| 3 | Add some more code to find out the ASCII codes for the following characters: A, Z, a, z, 0 and 9 |
| |


## Integers
Integers are whole numbers. The integer types are

* char
* short
* int
* long
* long long

Each of these have a specific size (in bytes) and hence range of possible values. As variables become larger, so they consume more memory and can take longer to process.

We already saw an `int` type being used in a previous example. On this platform, the `int` is a 4-byte (32 bit) value.

Consider the following code which uses a `short` type. On this platform, this consumes half the memory of an `int`

```C++
short shortCount = 32766;
printf("The value of shortCount is %hd\n", shortCount);
shortCount = shortCount + 1;
printf("add 1 and shortCount is %hd\n", shortCount);
```

* Note how the placeholder is `%hd` where `h` means _half_.

| TASK | Details |
| --- | --- |
| 1 | Change the third line to read `shortCount = shortCount + 2;` |
| 2 | Build and run the code, noting the output |
| 3 | Can you explain what has happened? |
| 4 | Now change the data type from `short` to `unsigned short` |
| 5 | Build and run the code again. |
| | 

What we witnessed here was an overflow. This can become a fairly confusing topic so I won't say more than this for now:

> The data type you choose not only determines how much memory a variable consumes, but also it's range of possible values. 

| TASK | Details |
| --- | --- |
| 6 | Change the data type from `short` to `int` |
| 7 | Build and run. Is the result as you expect? |
| |

There are two additional types that are commonly used:

* `long`
* `long long`

Let's skip `long` (for reasons that will be explained) and look at `long long`

```C++
long long NN = 0x12345678ABCD0001LL;
printf("A very large number %lld\n", NN);
printf("A very large number in hex %llX\n", NN);
```

> Note that `NN` is initialised with a numerical literal, but in hexadecimal. If you use the prefix `0x`, the following digits are interpreted as base-16. 
>
> This keeps numbers shorter and makes it easier (for humans) to convert to binary. Each hex digit represents 4 bits
>
> The number also has the `LL` suffix. This ensures the value is not rounded to a regular integer by the compiler.

| TASK | Details |
| --- | --- |
| 1 | Change the place holders from `lld` to `d` |
| 2 | Wait and you will see "squiggly lines" appear in the editor. Hover your mouse over this and read the warning |
| |

The placeholders also indicate the size of the data to expect. The warnings are there to help prevent you from making a logical error. 

> Take a note of the wikipedia article on the printf format string - [https://en.wikipedia.org/wiki/Printf_format_string](https://en.wikipedia.org/wiki/Printf_format_string)

If you browse the article, you will see there is more detail than we want to look at right now! Much of this will be learned through example and practise.

## unsigned types
For every integer type (which are signed by default), there is an unsigned variant.

| type | unsigned alternative |
| --- | --- |
| `char` | `unsigned char` |
| `short` | `unsigned short` |
| `int` | `unsigned int` |
| `long` | `unsigned long` |
| `long long` | `unsigned long long` |

When you add the `unsigned` prefix, **the variable size does not change**. It is the range that needs careful consideration.

Consider the example in the code that uses an `unsigned short`. On this platform, a `short` uses 2 bytes (16 bits).

```C++
unsigned short p = 1; //16 bit
printf("unsigned int p = %u\n", p);
p = p - 2;
printf("Subtract 2. Now unsigned int p = %u\n", p);
```

This code demonstrates an **underflow**. As the quantity is considered unsigned, the value cannot go below zero. Therefore, it underflow back to the maximum value.

* The range of an N-bit unsigned integer is 0 ... 2<sup>N</sup>-1, where `N` is the number of bits.

* The range of an N-bit signed integer is -2<sup>N-1</sup> ... 2<sup>N-1</sup>-1, where `N` is the number of bits.

These both have the same number of possible values, just spread over different values.

| TASK | Details |
| --- | --- |
| 1 | Note the output from this section of code |
| 2 | Change the data type to signed by deleting the keyword `unsigned` |
| 3 | Change the placeholder in the `printf` format string from `%u` to `%d` |
| 4 | Re build and run the code. Note the change in output |
| |

The choice of signed and unsigned integers have many different implications, and some of these will become more apparent as we progress through the course.

## Floating Point Variables
So far, all the variable types have been whole numbers. In fact, this is all the computer can ultimately understand. But what if you want to use fractional numbers, such as 1.23, 0.5 etc..

The C and C++ programming languages support fractional arithmetic through the `float`, `double` data types (and variants on them).

> The standard fractional number type is a `float`. The type `double` is so named as it is _double precision_.

Some examples of this are shown below. However, there is a logical error in this code:

```C++
// float 
float pi_float = 3.1415926536;
printf("The value of pi is approximately %f\n", pi_float);

double pi_double = 3.1415926536l;
printf("The value of pi is approximately %lf\n", pi_double);
```

Note the two place holders used, `%f` and `%lf`. However, the output for both is exactly the same. This is because `printf` is performing a numerical rounding operation.

| TASK | Details |
| --- | --- |
| 1 | Change the place holders to display to 10 decimal places. Change `%f` to `%.10f` and `%lf` to `%.10lf`|
| 2 | Are both values displayed perfectly? |
| 3 | Increase the number of places to 20 |
|   | `double pi_double = 3.14159265358979323846l;` |
| 4 | Does `double` have the necessary precision?
| |

Note the `l` suffix on the `double` literal.

> **Performance** - Although computers work with binary data, fractional arithmetic is still possible due to "floating point arithmetic". Floating point arithmetic operations require specialist logic and can be computationally expensive. The microcontroller we are using was partly chosen as it supports floating point in hardware. Other devices may not support this and resort to (relatively) slow software libraries to implement the logic. If you need to perform fractional arithmetic, it is always good to choose a device that supports it. 

## sizeof
As we have seen, variables need a **type**, which specifies both the amount of memory a variable consumes and it's valid range. 

> Unfortunately, the size of the built in data type are not standardised.

You can check the size (in bytes) of any data type or variable using the `sizeof` function as shown below:

```C++
printf("Size of a char is %d bytes\n", sizeof(char));
printf("Size of a short is %d bytes\n", sizeof(short));
printf("Size of a int is %d bytes\n", sizeof(int));
printf("Size of a long is %d bytes\n", sizeof(long));
printf("Size of a long long is %d bytes\n", sizeof(long long));
printf("Size of a float is %d bytes\n", sizeof(float));
printf("Size of a double is %d bytes\n", sizeof(double));
```

On this platform, you might be surprised that despite its name, the `long` data type is the same size as `int`, so there is little benefit from using it.

## Platform independent types and typedef
If you use the native data types in C or C++, you can of course check the sizes of all data types. But what happens if you wish to reuse your code on another platform (such as a PC, Raspberry Pi or Arduino)?

This problem is easily addressed by using custom names for types using `typedef`. For example, we could write the following:

```C++
typedef char int8;
typedef short int16;
typedef int int32;
```

Now you can use `int8` in place of `char`, `int16` in place of `short` and `int32` in place of `int`. **These are just new names for existing types**.

> Note how _the new names reflect the size_. On another platform, you would keep these names but you would need to find existing types of the right size to match.

The general syntax is:

 ```C++ 
 typedef <Existing type> <New type name>
 ```

The good news is that most platforms do this for you so you can always know the size of your data types.

| type | size | signed |
| --- | --- | --- |
| int8_t | 1 | Yes |
| int16_t | 2 | Yes |
| int32_t | 4 | Yes |
| int64_t | 8 | Yes |
| uint8_t | 1 | No |
| uint16_t | 2 | No |
| uint32_t | 4 | No |
| uint64_t | 8 | No |
| |

> For educational purposes, we will use both the native data times and these safer types. You will see both code styles used. However, these safer types should become your default.  

| TASK | Details |
| --- | --- |
| 1 | Modify the code and use `sizeof` to verify the size of the  |
| 2 | Change the data type to signed by deleting the keyword `unsigned` |

---

[NEXT - Variables and Terminal Input](TASK112.md)