#include <stdio.h>
#include <iostream>
#include <array>
using namespace std;


int main()
{
    int keyPress;
    scanf("%d", &keyPress);
    printf("You typed %d\n", keyPress);

    switch (keyPress)
    {
        case 0:
        cout << "Main Menu" << endl;
        break;

        case 1:
        cout << "Sales" << endl;
        break;

        case 2:
        cout << "Repairs" << endl;
        break;

        default:
        cout << "Huh? I do not understand" << endl;
        break;
    }

    if (keyPress == 0) {
        cout << "Main Menu" << endl;
    } else if (keyPress == 1) {
        cout << "Sales" << endl;
    } else if (keyPress == 2) {
        cout << "Repairs" << endl;
    } else {
        cout << "Huh? I do not understand" << endl;
    }

    return 0;
}