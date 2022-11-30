#include <stdio.h>
#include <math.h>

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


    // Now writing to a file
    // See https://cplusplus.com/reference/cstdio/fopen/ for different modes
    FILE* op = fopen("trig_data.csv", "w"); //Write mode - try changing to append
    if (!op) {
        printf("Could not open the file\n");
        return -1;
    }

    //Ok, file is open - let's now write it
    for (unsigned int n=0; n<N; n++) {
        double angleInRadians = 2.0*pi*n/N;
        double c = cos(angleInRadians);
        double s = sin(angleInRadians);
        fprintf(op, "%10.6f,%10.6f\n", c, s);    //Field width = 10 characters, 6dp
    } 

    //Remember to CLOSE the file
    fclose(op);

    

    return 0;
}