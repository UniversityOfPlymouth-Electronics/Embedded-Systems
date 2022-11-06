#include "mbed.h"

typedef struct {
  double real;
  double imag;
} ComplexNumber_C;

ComplexNumber_C complexAdd(const ComplexNumber_C a, const ComplexNumber_C b) {
    ComplexNumber_C y = a;
    y.real += b.real;
    y.imag += b.imag;
    return y;
}

void complexDisplay(const char *strName, const ComplexNumber_C u) {
    printf("%s = %f + j%f\n", strName, u.real, u.imag);
}

// TASK - write and test complexConjugate, complexNegate, complexSubtract, complexMagnitude, complexMultiply and complexDivide

ComplexNumber_C complexConjugate(const ComplexNumber_C a){//conjugate finder keep real, - imag
    ComplexNumber_C conjnum;                              
    ConjNum.real = a.real;
    ConjNum.imag = a.imag;
    return ConjNum;    
}

ComplexNumber_C complexNegate(const ComplexNumber_C a){// no clue what a negate is

}

ComplexNumber_C complexSubtract(const ComplexNumber_C a, const ComplexNumber_C b){
    ComplexNumber_C ComSum = a;
    ComSum.real -= b.real;
    Comsum.imag -= b.imag;
    return ComSum;
}


int main() {
    printf("\n\nTASK312\n");

    //Create instance of a complex number
    ComplexNumber_C p = {2.0, 3.0};         //2+3j
    ComplexNumber_C q = {1.0, 1.0};         //1+j
    complexDisplay("p", p);
    complexDisplay("q", q);
 
    ComplexNumber_C sum = complexAdd(p, q);
    complexDisplay("p+q", sum);

    
    while (true) {
    }
}
