#include "stdio.h"
#include "myusefullibrary.h"
// Attendance code: BF BV US

int main()
{
    int N;
    N = displayBanner("ELEC143");
    printf("The Attendance code is: BF BV US\n");
    printf("displayBanner has been called %d times\n",N);
    N = displayBanner("MATH190");
    printf("displayBanner has been called %d times\n",N);
    return 0;
}

