// Copy constructor and assignment
//
// See https://learn.microsoft.com/cpp/cpp/copy-constructors-and-copy-assignment-operators-cpp?view=msvc-170
//
// N Outram and S Harris (the bearded Guru)
//
// Checked with valgrind - https://valgrind.org/docs/manual/quick-start.html
// valgrind --leak-check=yes ./main

#include <iostream>
#include <memory>
using namespace std;

template<class T, int N>
class Record
{
    private:
    T* samples;                 // When this goes out of scope, the resource is deleted
    uint32_t index;             // Location of latest sample
    
    public:
    Record() {
        cout << "Record() called" << endl;      //
        samples = new T[N];                     // Allocate memory 
        index = 0;                              //
    }
    
    ~Record() {
        delete [] samples;
    }

    // Declare COPY CONSTRUCTOR - ensure the parameterless constructor is also called
    Record( const Record& other) : Record() {
        cout << "Copying via constructor..." << endl;
        *this = other;
    }     

    // Declare copy assignment.
    Record& operator=(const Record& rhs) {
        cout << "Copying..." << endl;
        for (uint32_t n=0; n<N; n++) {
            samples[n] = rhs.samples[n];
        }
        index = rhs.index;
        copyCount++;
        return *this;   //Dereference from pointer to value
    }   

    // For initialisation with a scalar
    void operator=(const T& u) {
        for (uint32_t n=0; n<N; n++) {
            samples[n] = u;
        }
    }

    // ********************* MOVE SEMANTICS *********************
/*
    Record( Record&& other) : samples(nullptr) {
        cout << "Move constructor..." << endl;
        // Remember: other is an rvalue, so will not persist

        //Take ownership of rvalue data
        samples = other.samples;    // Adopt the array as own
        other.samples = nullptr;    // When other goes out of scope, data won't be deleted

        //Same state
        index = other.index;
    } 

    // Declare copy assignment.
    Record& operator=(Record&& rhs) {
        if (samples == rhs.samples) return *this;
        cout << "Moving..." << endl;
        if (samples) {
            delete [] samples;
            samples = rhs.samples;
            rhs.samples = nullptr;
            index = rhs.index;
        }        
        return *this;   //Dereference from pointer to value
    }
*/
    // ******************** ~MOVE SEMANTICS *********************

    // Insert a sample
    void operator << (T sample) {
        samples[index] = sample;
        index = (index == 0) ? N-1 : index-1;
    }

    // Read a sample via []
    T& operator[](uint32_t n) const {
        return samples[(index - n)%N];
    }
    // Read/write a sample via []
    T& operator[](uint32_t n) {
        return samples[(index - n)%N];
    }

    // Sum two together 
    Record operator+(const Record<T,N>& rhs) const {
        Record<T,N> sum;                //Allocate a record for the result
        for (uint32_t n=0; n<N; n++) {
            sum[n] = (*this)[n] + rhs[n];   //Add and store in sum
        }
        return sum;
    }

    // Write contents of the internal buffer to the terminal
    void display() {
        uint32_t idx = index;
        for (uint32_t n=0; n<N; n++) {
            cout << samples[idx] << endl;
            idx = (idx == 0) ? N-1 : idx-1;   
        }
    }

    //Used for demo purposes
    static uint16_t copyCount;

};

//Static memory for keeping count
template<class T, int N>
uint16_t Record<T,N>::copyCount {0};

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

    // Use copy constructor to deep-copy A into C
    Record<int, 4> C(A);

    // Update A (independently of C)
    A << 5;

    // Check C has not changed
    C.display();
    
    // Now the operator
    B = A;
    B.display();

    // The initialisation operator
    Record<int,4> D;
    D = 0;
    D.display();

    // The add can be done in 1 line or two. In two lines, it is less able to optimise
    Record<int,4> Y;
    Y = A + B;
    //Record<int,4> Y = A+B;    //Turn on optimisation and watch the copy disappear.

    Y.display();

    cout << Record<int,4>::copyCount << endl;

    return 0;
}