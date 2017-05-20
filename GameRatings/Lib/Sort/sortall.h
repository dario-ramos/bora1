#ifndef _SORTALL_H
#define _SORTALL_H


#include <vector>
#include "comparer.h"

// ******************
// prototypes for sort functions and search functions
// author: Owen Astrachan
//
// see also: comparer.h, sortall.cpp
//
// for "plain" sorts, the type being sorted
// must be comparable with < and for Merge and Quick also with <=
// for sorts with the Comparer template parameter the type
// for Comparer (see comparer.h) must have a member function
// named compare that takes two const Type arguments: lhs, rhs,
// and that returns -1, 0, or +1 if lhs <, ==, > rhs, respectively
//
// search functions take a Comparer object also
//
// *******************

template <class Type>
void InsertSort(std::vector<Type> & a, int size);

template <class Type, class Comparer>
void InsertSort(std::vector<Type> & a, int size, const Comparer & comp);

template <class Type>
void SelectSort(std::vector<Type> & a, int size);

template <class Type, class Comparer>
void SelectSort(std::vector<Type> & a, int size, const Comparer & comp);

template <class Type>
void BubbleSort(std::vector<Type> & a, int size);

template <class Type>
void MergeSort(std::vector<Type> & a,int n);

template <class Type, class Comparer>
void MergeSort(std::vector<Type> & a, int n, const Comparer & comp);

template <class Type>
void QuickSort(std::vector<Type> & a, int size);

template <class Type, class Compare>
void QuickSort(std::vector<Type> & a, int size,const Compare& comp);

template <class Type>
void HeapSort(std::vector<Type>& a, int size);

template <class Type>
void Swap(std::vector<Type> & v, int j, int k);
// post: v[k] and v[j] swapped


// searching functions

template <class Type>
int bsearch(const std::vector<Type>& list, const Type& key);

template <class Type, class Comparer>
int bsearch(const std::vector<Type>& list, const Type& key, const Comparer& c);


template <class Type, class Comparer>
int search(const std::vector<Type>& list, const Type& key, const Comparer& c);

template <class Type>
int search(const std::vector<Type>& list, const Type& key);

#include "sortall.cpp"  

#endif
