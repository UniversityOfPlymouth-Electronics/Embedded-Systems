#include "stdio.h"
#include "string.h"

void displayMatrix(const unsigned int R, const unsigned int C, const double M[][C])
{
    for (unsigned int n=0; n<(10*C); n++) {
        printf("-");
    }
    printf("\n");
    for (unsigned r=0; r<R; r++) {
        for (unsigned c = 0; c<C; c++) {
            printf("%10.3f", M[r][c]);
        }
        printf("\n");
    }    
}

int main()
{

    double A[3][2] = {
        {1.0, 2.0},
        {3.0, 4.0},
        {5.0, 6.0}
    };
    
    double B[3][2] = {
        {10.0, 20.0},
        {30.0, 40.0},
        {50.0, 60.0}
    };

    double u[] = {
        2.0,
        10.0,
        1.0
    };

    // Y = A+B
    double Y[3][2];
    for (unsigned r=0; r<3; r++) {
        for (unsigned c = 0; c<2; c++) {
            Y[r][c] = A[r][c] + B[r][c];
        }
    }

    displayMatrix(3,2,A);
    displayMatrix(3,2,B);


    return 0;
}