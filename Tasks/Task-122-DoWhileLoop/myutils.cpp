#include "stdio.h"

void flushInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}
