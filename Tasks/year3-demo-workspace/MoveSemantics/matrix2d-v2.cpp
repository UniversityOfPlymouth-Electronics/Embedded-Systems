#include <iostream>
#include <memory>

// Original Source: The bearded guru Steve
// with some mods by N Outram
//
// Compile with "-fno-elide-constructors" to demonstrate the move

// This is a great resource - presents the recipe (otherwise, this can got easily wrong!!!)
// https://learn.microsoft.com/en-us/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170

// matrix M rows by N columns
template <uint32_t M, uint32_t N, class T>
class matrix2D  {
	private:
	// vector of values
	T* m_data;
	static uint16_t copyCount;

	public:
	// default constructor
	matrix2D<M,N,T> () {
		// set the vector size
		m_data = new T[M*N];
		// Initialise with zeros
		for (int i=0; i<M*N; ++i) {
			m_data[i] = 0;
		}
	}

	// DESTRUCTOR
	~matrix2D<M,N,T>() {
		delete [] m_data;
	}

	// COPY CONSTRUCTOR (chains constructors to ensure the memory is allocated first)
	matrix2D<M,N,T> (const matrix2D<M,N,T>& other) : matrix2D<M,N,T>()  {
		//Copy the data over
		for (uint32_t i=0; i<M*N; ++i) {
			m_data[i] = other.m_data[i];
		}
		copyCount++;	
	}	

	// COPY operator=
	matrix2D<M,N,T>& operator=(const matrix2D<M,N,T>& other) {
		//If you equate to self, do nothing!
		if (other.m_data == m_data) return *this;

		//Copy the data over
		for (uint32_t i=0; i<M*N; ++i) {
			m_data[i] = other.m_data[i];
		}
		copyCount++;

		//Return reference (not a pointer type)
		return *this;
	}


	// MOVE CONSTRUCTOR (no need to allocate in this case)
	matrix2D<M,N,T> (matrix2D<M,N,T>&& other) : m_data(nullptr)  {
		// Simply transfer ownership
		m_data = other.m_data;
		// Set other m_data to null to avoid it being deallocated
		other.m_data = nullptr;
	} //At this point, the rvalue `other` is likely to go out of scope (soon)
	
	// MOVE operator=
	matrix2D<M,N,T>& operator=(matrix2D<M,N,T>&& other ) {
		// If moving to self, just return
		if (m_data == other.m_data) return *this;

		// Free up the memory in this object (if allocated)
		delete [] m_data;

		// Take ownership of other data (move)
		m_data = other.m_data;

		// Set m_data in the other vector to nullptr 
		// Critical - otherwise m_data would be deallocated when the rvalue goes out of scope!
		other.m_data = nullptr;

		//Return a reference (not a pointer type)
		return *this;
	}
	
	// Adds the contents of this matrix with another and MOVE-RETURNS THE RESULT
	matrix2D<M,N,T> operator+(const matrix2D<M,N,T>& other) const {
		//Create temporary object to hold the result
		matrix2D<M,N,T> result;
		
		for (uint32_t i=0; i<M*N; ++i) {
			result.m_data[i] = m_data[i] + other.m_data[i];
		}
		
		// Return as rvalue (move) 
		return result;

	} // result will now go out of scope

	// Return a value from the matrix
	T get(int row, int column) const {
		return m_data[row*N+column];
	}
	
	// Set a value in the matrix
	void set(uint32_t row, uint32_t column, T value) {
		m_data[row*N+column] = value;
	}
		
	// Print the contents of the data vector
	void dump(const std::string& name) {
		std::cout << name << "  ----------------\n";
		for (uint32_t r=0; r<M; ++r) {
			for (uint32_t c=0; c<N; ++c) {
				std::cout << get(r,c) << "\t";
			}
			std::cout << std::endl;
		}
		std::cout << "---------------------------\n";
	}
	static uint32_t getCopyCount() {
		return copyCount;
	}
};

//Static memory for keeping count
template <uint32_t M, uint32_t N, class T>
uint16_t matrix2D<M,N,T>::copyCount {0};

using namespace std;

int main() {
	std::cout << "Copy Semantics\n";
	
	// create two matrices
	matrix2D<3,4,double> mat1, mat2;

	// set a value in the two matrices
	mat1.set(2,3, 3.0);
	mat2.set(2,3, 7.0);

	// Display
	mat1.dump("mat1");
	mat2.dump("mat2");

	// Create another with the copy constructor
	cout << "Copy Constructor. mat3 is a copy of mat1" << endl;
	matrix2D<3,4,double> mat3(mat1);

	// Check
	mat3.dump("mat3 : should be the same as mat1");

	// add them together
	cout << "Now some move semantics" << endl;
	matrix2D<3,4,double> mat4 = mat1 + mat2;	//In one line
	mat4.dump("mat4 = mat1 + mat2");
	
	// add them together in the other order
	mat4 = mat2 + mat1;		// Note mat4 already exists
	mat4.dump("mat4 = mat2 + mat1");

	//Print out copy count
	cout << "Copies = " << matrix2D<3,4,double>::getCopyCount() << endl;
}
