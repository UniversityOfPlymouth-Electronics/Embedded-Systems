#include <iostream>
#include <functional>
//#include <string>
//#include <type_traits>

using namespace std;

bool sort(int *data, unsigned N, function<bool(int,int)> sortRule) 
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


int main()
{   
    auto sortCriteria = [](int a, int b) {
        return (a > b) ? true : false;
    };

    int x[] = {4, 2, 3, 1, 7};
    uint16_t N = (sizeof(x)/sizeof(int));
    
    bool updated = false;
    do {
        updated = sort(x, N, sortCriteria);
    } while (updated == true);
    
    for (unsigned n=0; n<N; n++) {
        cout << x[n] << endl;    
    }
    
    return 0;
}