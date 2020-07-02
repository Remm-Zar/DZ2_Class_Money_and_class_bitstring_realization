#include "Money.h"
#include "BitString.h"
#include <iostream>
using namespace std; 
void V(Array &a,Array &b,Array &c)
{
    a.By_elem_plus(b, c);
    a.print();
}
int main()
{ 
    Money *Der1,a, b(56,99), c(2345,67);
    Array *base,f(6),d{ 44,56,43,77,85,7 }, e{ 7,86,43,12,34,2 };
    BitString *Der2,h,i(21989),j(65474);
    //полиморфизм 
    base = &f;
    V(*base, d, e); 
    base = &a;
    V(*base,b,c);  
    base = &h;
    V(*base, i, j);
    //вызов методов через указатели
    base = new Array{ 1,2,3,4,5 };
    Der1 = new Money{ 1234,56 };
    Der2 = new BitString( 23455334 );
    cout << "\nBase print: ";
    base->print();
    //Money ptr
    Der1->GetKopeyki();
    Der1->GetRubles();
    cout << "\nMoney print: ";
    Der1->print();
    //
    cout << "\nBitString print: ";
    Der2->print();
    cout << "\nBitString>>4";
    *Der2 << 5;
    Der2->print();
    cout << "\nBitString<<7";
    *Der2 >>7;
    Der2->print();
    cout << "\nBinary output:";
    cout<<"\nAND: "<<Der2->AND(i);
    cout << "\nOR: " << Der2->OR(j);
    cout << "\nNOT: " << Der2->NOT();
    cout << "\nXOR: " << Der2->XOR(i);
    delete base;
    delete Der1;
    delete Der2;
    return 0;
}

