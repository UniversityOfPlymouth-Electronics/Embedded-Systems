// Move constructor and assignment
//
// See https://learn.microsoft.com/en-gb/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170

#include <iostream>
#include <memory>
using namespace std;

template<class T, int N>
class Record
{
    private:
    // I've used a unique_ptr to simplify memory management
    T* samples;    // When this goes out of scope, the resource is released
    uint32_t index;             // Location of latest sample
    
    public:
    Record() {
        cout << "Record() called" << endl;      //
        samples = new T[N];                     // Allocate memory (non-reference counted)
        index = 0;                              //
    }
    ~Record() {
        delete [] samples;                      // Deallocate
    }
    // Declare COPY CONSTRUCTOR - ensure the parameterless constructor is also called
    Record( const Record& other) : Record() {
        cout << "Copying via constructor..." << endl;
        *this = other;
    }     
    // Declare MOVE CONSTRUCTOR - using the RVALUE Reference (RVALUE References cannot be accessed elsewhere)
    Record( const Record&& other) : samples(nullptr), index(0) {
        samples = other.samples;    //Set pointer to the existing resource - we are taking ownership of this memory
        index   = other.index;      //Copy the index
        //Invalidate the RHS (best practise) as it will not be used anywhere else / again
        other.samples = nullptr;
        other.index = 0;
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
    // Move assignment
    

    // For initialisation with a scalar
    void operator=(T u) {
        for (uint32_t n=0; n<N; samples[n] = u, n++);
    }

    ~Record() {
        cout << "~Record() called" << endl;
    }

    // Add a sample
    void operator << (T sample)
    {
        samples[index] = sample;
        index = (index == 0) ? N-1 : index-1;
    }

    // Write contents of the internal buffer to the terminal
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