#pragma once
#include "Array.h"
#include <initializer_list>
#include <iostream>
using namespace std;
class BitString:public Array
{
    // ИСПОЛЬЗУЙ МАССИВ ИЗ Array, НЕ НАДО СТРОКУ ДЕЛИТЬ НА ДВЕ ЧАСТИ
    unsigned long m_old[32] = { 0 };
    unsigned long m_young[32] = { 0 };
    
    long long power(long long num, long long pow)const
    {
        if (pow > 0)
        {
            return num * power(num, pow - 1);
        }
        else
        {
            return 1;
        }
    }
    long long ToDecConvertor(const int &redix)const
    {
        int count = 0;
        long long y = 0;
        for (int i = 31; i >-1; --i)
        {
            y += m_young[i] * power(redix, count);
            ++count;
        }
        for (int i = 31; i > -1; --i)
        {
            y += m_old[i] * power(redix, count);
            ++count;
        }
        return y;
    }
public:
   BitString(){}
   BitString(long x)
    {  
       SetString(x);
    }
   BitString(BitString& b)
   {
       for (int i = 31; i > -1; --i)
       {
           m_young[i] = b.m_young[i];
       }
       for (int i = 31; i > -1; --i)
       {
           m_old[i] = b.m_old[i]; 
       }
   }
   BitString(const initializer_list<unsigned char>& list) :Array(list)
   {}
   ~BitString()override
   {}
    void SetString(long x)
    {
        int i = 32, total = 0;
        bool OLD = false;
        while (x > 0)
        {
            --i;
            if (i == -1)
            {
                OLD = true;
                i = 31;
            }
            if (OLD)
            {
                m_old[i] = x % 2;
            }
            else
            {
                m_young[i] = x % 2;
            }
            x /= 2;
            ++total;
        }
        --i;
        if (x < 0) m_old[0] = 1;
        else m_old[0] = 0;
    }
    void print()const override
    {
        cout <<"\nIt's BitString object: "<< ToDecConvertor(2);
    }
    BitString& By_elem_plus(const Array& a, const Array& b)override
    {
        bool Q = 0;
        for (int i = 31; i > -1; --i)
        {
            m_young[i] = (dynamic_cast<BitString&>(const_cast<Array&>(a)).m_young[i] + dynamic_cast<BitString&>(const_cast<Array&>(b)).m_young[i]) % 2+Q;
            Q = (dynamic_cast<BitString&>(const_cast<Array&>(a)).m_young[i] + dynamic_cast<BitString&>(const_cast<Array&>(b)).m_young[i]) / 2;
        }
        for (int i = 31; i > -1; --i)
        {
            m_old[i] = (dynamic_cast<BitString&>(const_cast<Array&>(a)).m_old[i] + dynamic_cast<BitString&>(const_cast<Array&>(b)).m_old[i]) % 2 + Q;
            Q = (dynamic_cast<BitString&>(const_cast<Array&>(a)).m_old[i] + dynamic_cast<BitString&>(const_cast<Array&>(b)).m_old[i]) / 2;
        }
        return *this;
    }
    BitString XOR(BitString& b)
    {
        BitString temp;
        for (int i = 31; i > -1; --i)
        {
            temp.m_young[i] = (m_young[i] + b.m_young[i]) % 2;
        }
        for (int i = 31; i > -1; --i)
        {
            temp.m_old[i] = (m_old[i] + b.m_old[i]) % 2;
        }
        return temp;
    }
    BitString OR(BitString& b)
    {
        BitString temp;
        for (int i = 31; i > -1; --i)
        {
            temp.m_young[i] = b.m_young[i] || m_young[i];
        }
        for (int i = 31; i > -1; --i)
        {
            temp.m_old[i] = b.m_old[i] || m_old[i];
        }
        return temp;
    }
    BitString AND(BitString& b)
    {
        BitString temp;
        for (int i = 31; i > -1; --i)
        {
            temp.m_young[i] = b.m_young[i] && m_young[i];
        }
        for (int i = 31; i > -1; --i)
        {
            temp.m_old[i] = b.m_old[i] && m_old[i];
        }
        return temp;
    }
    BitString NOT()
    {
        BitString temp(*this);
        for (int i = 31; i > -1; --i)
        {
            temp.m_young[i] = !temp.m_young[i];
        }
        for (int i = 31; i > -1; --i)
        {
            temp.m_old[i] = !temp.m_old[i];
        }
        return temp;
    }
    friend ostream& operator<<(ostream& out,const BitString &b)
    {
        for (int i = 0; i < 32; ++i)
        {
            out << b.m_old[i];
        }
        for (int i = 0; i < 32; ++i)
        {
            out << b.m_young[i];
        }
        return out;
    }
    void operator<<(int shift)
    {
        bool OLD = false, trans = false;
        int prev_shift_index = 31, i;
        shift<=0?i=-1:i= 31 - shift;       
        while ( i >= 0)
        {          
            if (!prev_shift_index)
            {
                trans = false;
                OLD = true;
                prev_shift_index = -1;
            }
            if (!(OLD) && !(trans))
            { 
                m_young[i + shift] = m_young[i];
                m_young[i] = 0;
                --prev_shift_index;

            }
            if (trans)
            {
               m_young[prev_shift_index] =m_old[i];  
               m_old[i] = 0;
                --prev_shift_index;
            }
            if (OLD)
            { 
               m_old[i + shift] = m_old[i];
               m_old[i] = 0;
            }                     
            --i; 
            if ((i == -1)&&(!OLD))
            {
                trans = true;
                i = 31;
            }

        }
    }
    void operator>>(int shift)
    {
        bool YOUNG=false, trans;
        int prev_shift_index = 0, i;
        shift <= 0 ? i = 32 : i = 0;   
        shift >= 32 ? trans = true,i=shift-32 : trans = false;       
        while (i < 32)
        {
            if (prev_shift_index==32)
            {
                trans = false;
                YOUNG = true;
                prev_shift_index = -1;
            }
            if (!(YOUNG) && !(trans))
            {
                m_old[i] = m_old[i + shift];
                m_old[i + shift] = 0;
                ++prev_shift_index;
            }
            if (trans)
            {
                m_old[prev_shift_index] = m_young[i];
                m_young[i] = 0;
                ++prev_shift_index;
            }
            if (YOUNG)
            {
                m_young[i- shift] = m_young[i];
                m_young[i] = 0;
            }
            ++i;
            if ((i+shift == 32) && (!YOUNG))
            {
                trans = true;
                i = 0;
            }            
        }
    }
};

