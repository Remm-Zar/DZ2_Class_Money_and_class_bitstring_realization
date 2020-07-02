#pragma once
#include "Array.h"
#include <initializer_list>
#include <iostream>
using namespace std;
class BitString:public Array
{
    // В ФАЙЛЕ <cmath> ЕСТЬ ФУНКЦИЯ pow
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
        for (int i = 63; i >-1; --i)
        {
            y += m_arr[i] * power(redix, count);
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
   // ССЫЛКА КОНСТАНТНАЯ
   // СВОИХ ДАННЫХ В КЛАССЕ BitString НЕТ, ПОЭТОМУ НАДО НАПИСАТЬ
   // КОНСТРУКТОР КОПИРОВАНИЯ ДЛЯ Array И ПЕРЕАДРЕСОВАТЬ ЕМУ КОНСТРУИРОВАНИЕ
   BitString(BitString& b)
   {
       for (int i = 63; i > -1; --i)
       {
           m_arr[i] = b.m_arr[i];
       }
   }
   BitString(const initializer_list<unsigned char>& list) :Array(list)
   {}
   ~BitString()override
   {}
    void SetString(long x)
    {
        if (x < 0) m_arr[0] = 1;
        else m_arr[0] = 0;
        int i = 64;
        while (x > 0)
        {
            --i;
            m_arr[i] = x % 2;
            x /= 2;
        }   
        m_len = 64;
    }
    void print()const override
    {
        cout <<"\nIt's BitString object: "<< ToDecConvertor(2);
    }
    BitString& By_elem_plus(const Array& a, const Array& b)override
    {
        bool Q = 0;
        for (int i = 63; i > -1; --i)
        {
            m_arr[i] = (a[i] + b[i] + Q) % 2;
            Q = (a[i] + b[i]+Q) / 2;
        }
        return *this;
    }
    BitString XOR(BitString& b)
    {
        BitString temp;
        for (int i = 63; i > -1; --i)
        {
            temp.m_arr[i] = (m_arr[i] + b.m_arr[i]) % 2;
        }
        return temp;
    }
    BitString OR(BitString& b)
    {
        BitString temp;
        for (int i = 63; i > -1; --i)
        {
            // НАДО ИСПОЛЬЗОВАТЬ БИТОВЫЕ ОПЕРАЦИИ - |, &
            temp.m_arr[i] = b.m_arr[i] || m_arr[i];
        }
        return temp;
    }
    BitString AND(BitString& b)
    {
        BitString temp;
        for (int i = 63; i > -1; --i)
        {
            temp.m_arr[i] = b.m_arr[i] && m_arr[i];
        }      
        return temp;
    }
    BitString NOT()
    {
        BitString temp(*this);
        for (int i = 63; i > -1; --i)
        {
            // ОТРИЦАНИЕ НА СИМВОЛАХ НЕ РАБОТАЕТ
            temp.m_arr[i] = !temp.m_arr[i];
        }        
        return temp;
    }
    friend ostream& operator<<(ostream& out,const BitString &b)
    {
        for (int i = 0; i < 64; ++i)
        {
            out << static_cast<int>(b.m_arr[i]);
        }       
        return out;
    }
    void operator<<(int shift)
    {       
        int i;
        shift<=0?i=-1:i= 63 - shift;       
        while ( i >= 0)
        {
            m_arr[i + shift] = m_arr[i];
            m_arr[i] = 0;    
            --i;
        }
    }
    void operator>>(int shift)
    {
        int i;
        shift <= 0 ? i = 64 : i = 0;   
        while (i < 64-shift)
        {   
            m_arr[i] = m_arr[i + shift];
            m_arr[i + shift] = 0;           
            ++i;                       
        }
    }
};

