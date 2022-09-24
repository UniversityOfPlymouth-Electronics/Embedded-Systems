// Copy constructor and assignment
//
// See https://learn.microsoft.com/cpp/cpp/copy-constructors-and-copy-assignment-operators-cpp?view=msvc-170

#include <iostream>
#include <memory>
using namespace std;

template<class T, int N>
class Record
{
    private:
    unique_ptr<T[]> samples;
    uint32_t index;
    
    public:
    Record() {
        cout << "Record() called" << endl;
        samples = unique_ptr<T[]>(new T[N]);
        index = 0;
    }
    // Declare copy constructor - ensure the parameterless constructor is also called
    Record( const Record& other) : Record() {
        cout << "Copying via constructor..." << endl;
        this->operator=(other);
    }            
    // Declare copy assignment.
    Record& operator=(const Record& rhs) {
        cout << "Copying..." << endl;
        for (uint32_t n=0; n<N; n++) {
            samples[n] = rhs.samples[n];
            index = rhs.index;
        }
        return *this;   //Dereference from pointer to value
    }   
    // For initialisation
    void operator=(T u) {
        for (uint32_t n=0; n<N; samples[n] = u, n++);
    }

    ~Record() {
        cout << "~Record() called" << endl;
    }

    void operator << (T sample)
    {
        samples[index] = sample;
        index = (index == 0) ? N-1 : index-1;
    }

    void display()
    {
        uint32_t idx = index;
        for (uint32_t n=0; n<N; n++) {
            cout << samples[idx] << endl;
            idx = (idx == 0) ? N-1 : idx-1;   
        }
    }

};

int main()
{
    cout << "Copy Constructors" << endl;

    Record<int, 4> A;
    Record<int, 4> B;
    A << 1;
    A << 2;
    A << 3;
    A << 4;
    A.display();

    //Use copy constructor to deep-copy A into C
    Record<int, 4> C(A);

    //Update A (independently of C)
    A << 5;

    //Check C has not changed
    C.display();
    
    //Now the operator
    B = A;
    B.display();

    //The initialisation operator
    Record<int,4> D;
    D = 0;
    D.display();
    

    return 0;
}