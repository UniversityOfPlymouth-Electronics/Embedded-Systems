#include <iostream>

template <class T, int N>
class DataContainer
{
    private:
    //Array of data - potentially large!
    T data[N];
    uint32_t index = 0;

    public:
    DataContainer() : index(0) {
        for (uint32_t n=0; n<N; n++) {
            data[n] = (T)0;
        }
    }

    void addSample(T nextSample) {
        data[index] = nextSample;
        index = (index+1)%N;    //Not the fastest method
    }

    double calcMean() const {
        double y = 0.0;
        for (uint32_t n=0; n<N; n++) {
            y = y + (double)data[n];
        }
        return (y/N);
    }
};

template <class T, int N>
bool compareMeans( const DataContainer<T,N>& dat1, const DataContainer<T,N>& dat2)
{
    double m1 = dat1.calcMean();
    double m2 = dat2.calcMean();

    double margin = 0.05*m1;                            //5% margin
    return ( (m2>=(m1-margin)) && (m2<=(m1+margin)) );  //True if they are within +-5%
}

int main()
{
    DataContainer<double,10> c1;
    DataContainer<double,10> c2;

    compareMeans(c1,c2);

    return 0;
}