#include <iostream>
#include <stdio.h>
using namespace std;

#define N 3
double calcMean(int w1,int w2);
void display(int u);




void display(int u)
{
    printf("******\n");
    printf("%3d\n", u);
    printf("******\n");
    double y = calcMean(2,3);
}

double calcMean(int w1,int w2)
{
    double y;
    y = w1 + w2;
    y = y * 0.5;
    return y;
}


int main()
{
    int weight1 = 10;
    int weight2 = 7;
    double meanWeight;
    meanWeight = calcMean(weight1, weight2);
    printf("Mean = %f\n", meanWeight);

    display(weight1);
    display(weight2);

    return 0;
}