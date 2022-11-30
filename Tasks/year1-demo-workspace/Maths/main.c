#undef __STRICT_ANSI__  //Needed to get the extra constants (sigh)
#include <stdio.h>
#include <math.h>       //Header with all the math library functions and constants

int main()
{
    double pi = M_PI;
    unsigned int N = 100;

    for (unsigned int n=0; n<N; n++) {
        double angleInRadians = 2.0*pi*n/N;
        double c = cos(angleInRadians);
        double s = sin(angleInRadians);
        printf("%10.6f,%10.6f\n", c, s);    //Field width = 10 characters, 6dp
    }

    //Write data to file
    FILE* op = fopen("trigdata.csv","a");
    if (!op) {
        puts("Error - cannot create file");
        return -1;
    }

    for (unsigned int n=0; n<N; n++) {
        double angleInRadians = 2.0*pi*n/N;
        double c = cos(angleInRadians);
        double s = sin(angleInRadians);
        fprintf(op, "%10.6f,%10.6f\n", c, s);    //Field width = 10 characters, 6dp
    }

    fclose(op);

    return 0;
}