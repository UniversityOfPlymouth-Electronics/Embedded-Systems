#include "myusefullibrary.h"

int displayBanner(const char moduleCode[], int initialValue)
{
    static int count = initialValue;
    printf("\n");
    printf("***********\n");
    printf("* %s *\n", moduleCode);
    printf("***********\n");
    count++;
    return count;
}