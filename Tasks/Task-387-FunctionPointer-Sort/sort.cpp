#include <iostream>
using namespace std;

bool sort(int *data, unsigned N, bool(*sortRule)(int,int) ) 
{
    bool hasupdated = false;
    for (unsigned int n=0; n < (N-1); n++) {
        int u = data[n];
        int v = data[n+1];

        //Apply criteria for sort
        bool swap = sortRule(u,v);
        
        if (swap == true) {
            data[n]   = v; 
            data[n+1] = u;
            hasupdated = true;
        }
    }
    return hasupdated;
}

bool myFunc(int a, int b) {
    return (a > b) ? true : false;
} 
     
int main()
{
    bool (*fPointer)(int, int);
    fPointer = &myFunc; 
    
    int x[] = {4, 2, 3, 1, 7};
    uint16_t N = (sizeof(x)/sizeof(int));
    
    bool updated = false;
    do {
        updated = sort(x, N, fPointer);
    } while (updated == true);
    
    for (unsigned n=0; n<N; n++) {
        cout << x[n] << endl;    
    }
    
    return 0;
}