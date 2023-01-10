#include <iostream>
#include <vector>

// matrix M rows by N columns
template <int M, int N, class T>
class matrix2D  {
	public:
	// default constructor
	matrix2D<M,N,T> () {
		// set the vector size
		m_data.resize(M*N);
		// fill it with zeros
		std::fill(m_data.begin(), m_data.end(), 0);
	}
	
	// move constructor
	matrix2D<M,N,T> (matrix2D&& other)  {
		// move the other data
		m_data = std::move(other.m_data);
		// set the other vector length to zero so the object can't be used
		other.m_data.resize(0);
	}
	
	// destructor - use the default action
	~matrix2D<M,N,T>() = default;
	
	// return a value from the matrix
	T get(int row, int column) const {
		return m_data[row*N+column];
	}
	
	// set a value in the matrix
	void set(int row, int column, T value) {
		m_data[row*N+column] = value;
	}
	
	// move operator=
	matrix2D<M,N,T>& operator=(matrix2D<M,N,T>&& other ) {
		// move the data over
		m_data = std::move(other.m_data);
		// set the size of the other vector to zero so the object can't be reused.
		other.m_data.resize(0);
		return *this;
	}
	
	// copy operator=
	matrix2D<M,N,T>& operator=(const matrix2D<M,N,T>& other) {
		m_data = other.m_data;
		return *this;
	}
	
	// print the contents of the data vector
	void dump(const std::string& name) {
		std::cout << name << "  ----------------\n";
		for (int r=0; r<M; ++r) {
			for (int c=0; c<N; ++c) {
				std::cout << get(r,c) << "\t";
			}
			std::cout << std::endl;
		}
		std::cout << "---------------------------\n";
	}

	// adds the contents of this matrix with another and move-returns the result
	matrix2D<M,N,T> operator+(const matrix2D<M,N,T>& other) const {
		matrix2D<M,N,T> result;
		
		for (int i=0; i<m_data.size(); ++i) {
			result.m_data[i] = m_data[i] + other.m_data[i];
		}
		
		return std::move(result);
	}
	
	private:
	// vector of values
	std::vector<T> m_data;
};

int main() {
	std::cout << "Hello, world!\n";
	
	// create two matrices
	matrix2D<3,4,double> mat1, mat2;

	// print out the default value of [2,3]
	std::cout << mat1.get(2,3) << std::endl;
	
	// set a value in the two matrices
	mat1.set(2,3, 3.0);
	mat2.set(2,3, 7.0);

	// add them together
	auto mat3 = mat1 + mat2;
	
	// print out the value of [2,3] in the three matrices
	std::cout << mat1.get(2,3) << std::endl;
	std::cout << mat2.get(2,3) << std::endl;
	std::cout << mat3.get(2,3) << std::endl << "----------------\n";
	
	// add them together in the other order
	mat3 = mat2 + mat1;
	
	// print out the value of [2,3] in the three matrices
	std::cout << mat1.get(2,3) << std::endl;
	std::cout << mat2.get(2,3) << std::endl;
	std::cout << mat3.get(2,3) << std::endl << "----------------\n";
	
	// print out the contents of mat3
	mat3.dump("mat3");
}
