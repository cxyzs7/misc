//! \file array_size.h 
//! uses template type induction to discover the size of an array
//! FROM THINKING IN C++
#ifndef _ARRAY_SIZE_H
#define _ARRAY_SIZE_H

template<typename T, int size>
int sz(T (&)[size]) { return size; }

#endif