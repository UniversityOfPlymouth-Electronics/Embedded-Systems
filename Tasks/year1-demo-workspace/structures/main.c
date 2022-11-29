#include <stdio.h>

typedef struct {

    double currentMax;
    double voltageMax;
    int partNumber;

} Elec_t;

void display(const Elec_t* component)
{
    printf("Part %d: Imax=%f, Vmax=%f\n",  component->partNumber, component->currentMax, component->voltageMax);
}

Elec_t createWithZero()
{
    Elec_t y = {0.0, 0.0, 0};
    return y;
}

int main()
{
    Elec_t part1 = {.currentMax = 0.125, .voltageMax = 5.0, .partNumber = 12345};

    display(&part1);
    display(&part1);

    Elec_t part2 = createWithZero();
    display(&part2);

    return 0;
}