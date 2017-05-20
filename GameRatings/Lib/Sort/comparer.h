#ifndef _COMPARER_H
#define _COMPARER_H

// *********************
// for use in sorting, and in searches
// author: Owen Astrachan
// 7/20/98
//
// the struct Comparer, with templated implementation
// here, is an exemplar of the kind of struct/class needed
// for sorting and searching.  The template parameter must
// be the same kind as the objects being sorted/searched for
//
// the Comparer struct can be used for "standard" types, the
// only needed operator is <
//
// **********************

template <class Kind>
struct Comparer
{
    int compare(const Kind & lhs, const Kind & rhs) const;
};


template <class Kind>
int Comparer<Kind>::compare(const Kind & lhs, const Kind & rhs) const
// precondition:  operator < defined for class Kind, and Kind obeys
//                the trichotomy law: a < b OR a > b OR a == b
// postcondition: if lhs < rhs returns value < 0
//                if lhs > rhs returns value > 0
//                if lhs == rhs returns 0
{
    if (lhs < rhs) return -1;
    if (rhs < lhs) return  1;
    
    // else ==
    
    return 0;
}


#endif

