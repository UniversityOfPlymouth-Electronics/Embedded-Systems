#include <iostream>
using namespace std;

class Big {
    private:
    uint32_t bigArray[1024];
    public:
    Big() { /*Constructor here*/ }
    uint32_t getVal(uint32_t n) const {
        return bigArray[n];
    }
    //and the rest....
};

double calcMean(const Big& obj) {
    double sum=0.0;
    for (uint32_t n=0; n<1024; n++) { 
        sum+=(double)obj.getVal(n); 
    }
    return sum/1024.0;
}

int main()
{

    //Pointer example
    uint16_t dat1 = 10;
    uint16_t dat2 = 20;
    
    //pDat is the address of dat1
    uint16_t* pDat = &dat1;
    cout << *pDat << endl;  //Print the value at the address

    //Switch the pointer
    pDat = &dat2;
    cout << *pDat << endl;

    //Dereferencing
    uint16_t array[4] = {1,2,4,8};
    pDat = array;
    cout << *pDat << endl;
    cout << pDat[0] << endl;

    cout << *(pDat+3) << endl;
    cout << pDat[3] << endl;

    pDat++;
    cout << *pDat << endl;

    //References
    uint16_t& ref = dat1;   // ref is an alias of dat1
    cout << ref << endl;    // 10
    dat1 = 0;               // dat1 is now 0
    cout << ref << endl;    // 0
    ref = dat2;             // DOES NOT SWITCH ADDRESS.
    cout << ref << endl;    // 20
    dat2 = 1;               // No effect on dat1
    cout << ref << endl;    // 20

    Big someData;
    double y = calcMean(someData);  //Faster than it looks



    return 0;
}