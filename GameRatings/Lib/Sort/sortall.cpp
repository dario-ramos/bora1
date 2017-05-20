// see sortall.h

// ***************************
//
// some of the sort functions here are implemented twice to
// better illustrate how the Comparer template parameter is used.
// In "production" versions, there would only be one sort, which would
// use the Comparer template parameter and which would be called by
// a one line version of a sort function without the Comparer
// parameter --- see the SelectionSort function for how this is done
// both InsertionSort and MergeSort use duplicated code
//
// ***************************


const int CUTOFF = 30;               // used in quick/merge sorts 

template <class Type>
void Swap(std::vector<Type> & v, int j, int k)
// precondition:  v[j] references value A, v[k] references value B 
// postcondition: v[k] references value B, v[k] references value A 
{
    Type temp = v[j];
    v[j] = v[k];
    v[k] = temp;
}


template <class Type, class Comparer>
void Insert(std::vector<Type> & a ,int left,int right, const Comparer & comp)
// precondition: left <= right
// postcondition: a[left] <= ... <= a[right]
//     
// standard insertion sort between left/right
// for use in small quick/merge cases as well
{
    int k,loc;
    
    for(k=left+1;k<=right;k++) 
    {
        // shift elements to make room for a[k]
        
        Type hold = a[k];   // insert this element
        loc = k;            // location for insertion
        while (left < loc && comp.compare(hold,a[loc-1]) < 0)
        {
            a[loc] = a[loc-1];
            loc--;
        }
        a[loc] = hold;
    }
}

template <class Type, class Comparer>
void InsertSort(std::vector<Type> & a, int size, const Comparer & comp)
// precondition: size = # of elements of a
// postcondition: a is sorted
//
// uses insertion sort     
{
    Insert(a,0,size-1,comp);
}

template <class Type>
void Insert(std::vector<Type> & a ,int left,int right)
// precondition: left <= right
// postcondition: a[left] <= ... <= a[right]
//     
// standard insertion sort between left/right
// for use in small quick/merge cases as well
{
    int k,loc;
    
    for(k=left+1;k<=right;k++) 
    {
        // shift elements to make room for a[k]
        
        Type hold = a[k];   // insert this element
        loc = k;            // location for insertion
        while (left < loc  && hold < a[loc-1])
        {
            a[loc] = a[loc-1];
            loc--;
        }
        a[loc] = hold;
    }
}

template <class Type>
void InsertSort(std::vector<Type> & a, int size)
// precondition: size = # of elements of a
// postcondition: a is sorted
//
// uses insertion sort     
{
    Insert(a,0,size-1);
}

template <class Type,class Comparer>
void SelectSort(std::vector<Type> & a, int size, const Comparer & comp)
// precondition: size = # of elements of a
// postcondition: a is sorted
//     
// standard selection sort
{
    int j,k,min;
    
    for(j=0; j< size-1;j++)
    {
        min = j;
        for(k=j+1; k<size; k++)
        {
            if (comp.compare(a[k],a[min]) < 0)
            {
                min = k;
            }
        }
        Swap(a,min,j);
    }
}

template <class Type>
void SelectSort(std::vector<Type> & a, int size)
// precondition: size = # of elements of a
// postcondition: a is sorted
//     
// standard selection sort
{
    int j,k,min;
    
    for(j=0; j< size-1;j++)
    {
        min = j;
        for(k=j+1; k<size; k++)
        {
            if (a[k] < a[min])
            {
                min = k;
            }
        }
        Swap(a,min,j);
    }    
}


template <class Type>
void BubbleSort(std::vector<Type> & a, int n)
// precondition: n = # of elements in a
// postcondition: a is sorted
//                note: this is a dog of a sort     
{
    int j,k;
    for(j=n-1; j > 0; j--)
    {
		// find largest element in 0..k, move to a[j]
		for(k=0; k < j; k++)
    	{
	    	if (a[k+1] < a[k])
            {
				Swap(a,k,k+1);
	   		}
		}	
    }
}

template <class Type>
void ShellSort(std::vector<Type> & a, int n)
// precondition: n = # elements in a
// postcondition: a is sorted
//     
// shell sort using Hibbard increments, see Weiss "Algorithms, Data Structures and
// Problem Solving with C++"     
{
    int h,j,k,loc,increment;

    for(h=1; h <= n/2; h *= 2 )
    {
        // found power of 2 closest to n/2
    }
        
    h--;            // went past n/2 in loop guard

	while (h > 0)
    {
        // insertion sort using jumps of 'size' h, see InsertSort above
        
        for(k=h; k < n; k++) 
        {
            Type hold = a[k];
            loc = k;
            while (h <= loc && hold < a[loc-h])
            {
                a[loc] = a[loc-h];
                loc -= h;
            }
            a[loc] = hold;
        }
        
        h /= 2;
    }
}

template <class Type>
void Merge(std::vector<Type> & a, std::vector<Type> & b, int left,int mid,int right)
// precondition: a sorted from a[left] ... a[mid] and from
//               a[mid+1] to a[right]
//               extra storage passed in as vector b
// postcondition: a sorted from a[left] ... a[right]     
{
    int lk=left;                          // a's left index 
    int rk = mid+1;                       // a's right index 
    int bk = left;                        // b's index

    while (lk <= mid && rk <= right)      // both parts non-empty?
    {
        if (a[lk] <= a[rk])
        {
            b[bk] = a[lk];
            lk++;
        }
        else
        {
            b[bk] = a[rk];
            rk++;
        }
        bk++;
    }
        // finish any leftovers in a (only one of loops below executes)
    
    while (lk <= mid)
    {
        b[bk] = a[lk];
        bk++;
        lk++;
    }
    while(rk <= right)
    {
        b[bk] = a[rk];
        bk++;
        rk++;
    }
    
        // copy b back to a
    
    for(lk=left; lk <= right; lk++)
    {
    	a[lk] = b[lk];
    }
}

template <class Type, class Comparer>
void Merge(std::vector<Type> & a, std::vector<Type> & b, int left,int mid,int right,
           const Comparer & comp)
// precondition: a sorted from a[left] ... a[mid] and from
//               a[mid+1] to a[right]
//               extra storage passed in as vector b
// postcondition: a sorted from a[left] ... a[right]     
{
    int lk=left;                          // a's left index 
    int rk = mid+1;                       // a's right index 
    int bk = left;                        // b's index

    while (lk <= mid && rk <= right)      // both parts non-empty?
    {
        if (comp.compare(a[lk],a[rk]) <= 0)
        {
            b[bk] = a[lk];
            lk++;
        }
        else
        {
            b[bk] = a[rk];
            rk++;
        }
        bk++;
    }
        // finish any leftovers in a (only one of loops below executes)
    
    while (lk <= mid)
    {
        b[bk] = a[lk];
        bk++;
        lk++;
    }
    while(rk <= right)
    {
        b[bk] = a[rk];
        bk++;
        rk++;
    }
    
        // copy b back to a
    
    for(lk=left; lk <= right; lk++)
    {
    	a[lk] = b[lk];
    }
}


template <class Type, class Comparer>
void DoMerge(std::vector<Type> & a, std::vector<Type> & temp, int left,int right,
             const Comparer & comp)
// postcondition: a[left] <= ... <= a[right],
//                temp.length() == a.length(), temp is temp array for merging    
{
    int mid = (left+right)/2;
    
    if (right - left > CUTOFF)
    {
        DoMerge(a, temp, left,mid,comp);
        DoMerge(a, temp, mid+1,right,comp);
        Merge(a, temp, left,mid,right,comp);
    }
    else
    {
        Insert(a,left,right,comp);
    }
}

template <class Type>
void MergeSort(std::vector<Type> & a,int n)
{
    MergeSort(a, n, Comparer<Type>());
}


template <class Type, class Comparer>
void MergeSort(std::vector<Type> & a, int n, const Comparer & comp)
{
	vector<Type> temp(a.length());
	DoMerge(a,temp,0,n-1,comp);
}


template <class Type, class Comparer>
int Median(std::vector<Type> & a,int first,int last, const Comparer& comp)
// postcondition: returns index of median element of
//            a[first],a[last],a[mid], mid = (first+last)/2
{
    int mid=(first+last)/2;

    if (comp.compare(a[first],a[mid]) < 0)
    {
        if (comp.compare(a[mid],a[last]) < 0)        return mid;
        else if (comp.compare(a[first],a[last]) < 0) return last;
        else                                         return first;
    }
    else
    {
        if (comp.compare(a[first],a[last]) < 0)      return first;
        else if (comp.compare(a[last],a[mid]) < 0)   return mid;
        else                                         return last;
    }
}

template <class Type,class Compare>
int Pivot(std::vector<Type> & a,int first,int last,const Compare& comp)
// postcondition: returns piv such that
//                first <= k <= piv, a[k] <= a[piv]
//                piv < k <= last, a[piv] < a[k]                
// standard Bently/ola pivot routine
{
    int k,p=first;
    
    Swap(a,first,Median(a,first,last,comp));  
    Type piv = a[first];
    
    for(k=first+1;k<=last;k++)
    {
        if (comp.compare(a[k],piv) <= 0)
        {
            p++;            
            Swap(a,k,p);
        }
    }
    Swap(a,p,first);
    return p;
}

template <class Type, class Compare>
void Quick(std::vector<Type> & a,int first,int last,const Compare& comp)
// postcondition: a[first] <= ... <= a[list]     
{
    int piv;
    
    if (last - first > CUTOFF)
    {
        piv = Pivot(a,first,last,comp);
        Quick(a,first,piv-1,comp);
        Quick(a,piv+1,last,comp);
    }
    else
    {
        Insert(a,first,last,comp);
    }
}

template <class Type, class Compare>
void QuickSort(std::vector<Type> & a, int size,const Compare& comp)
// precondition: size = # of elements of a
// postcondition: a is sorted     
{
    Quick(a,0,size - 1,comp);
}

template <class Type>
void QuickSort(std::vector<Type> & a, int size)
// precondition: size = # of elements of a
// postcondition: a is sorted     
{
    Quick(a,0,size - 1,Comparer<Type>());
}

template <class Type>
void Heapify(std::vector<Type> & a, int vroot, int size)
// precondition: subheaps of vroot are heaps: shape and property
// postcondition: heap rooted at vroot is a heap
{
    Type rootval = a[vroot];
    int child;
    int k = vroot;
    
    while (2*k+1 < size)
    {
        child = 2*k+1;                       
        
        // if there's a right child, and it's bigger, move the larger
        if (child+1 < size && a[child] < a[child+1])
        {
            child++;
        }
        if (a[child] < rootval) break;
        
        a[k] = a[child];
        k = child;
    }
    a[k] = rootval;
}

template <class Type>
void HeapSort(std::vector<Type>& a, int size)
{
    int k;
    
    for(k=(size-2)/2; k >= 0; k--)
    {
        Heapify(a,k,size);
    }
    for(k=size-1; k >= 1; k--)
    {
        Swap(a,0,k);
        Heapify(a,0,k);
    }
}

template <class Type>
int search(const std::vector<Type>& list, const Type& key)
// precondition: list.size() == # elements in list
// postcondition: returns index of key in list, -1 if key not found
{
    int k;
    for(k=0; k < list.size(); k++)
    {   if (list[k] == key)
        {   return k;
       }
    }
    return -1;   // reach here only when key not found
}

template <class Type, class Comparer>
int search(const std::vector<Type>& list, const Type& key, const Comparer& c)
// precondition: list.size() == # elements in list
// postcondition: returns index of key in list, -1 if key not found
//                uses c.compare for equality condition    
{
    int k;
    for(k=0; k < list.size(); k++)
    {   if (c.compare(list[k],key)==0)
        {   return k;
       }
    }
    return -1;   // reach here only when key not found
}

template <class Type>
int bsearch(const std::vector<Type>& list, const Type& key)
// precondition: list.size() == # elements in list, list sorted
// postcondition: returns index of key in list, -1 if key not found
{
    int low = 0;                   // leftmost possible entry
    int high = list.size()-1;      // rightmost possible entry
    int mid;                       // middle of current range
    while (low <= high)
    {   mid = (low + high)/2;
        if (list[mid] == key)       // found key, exit search
        {   return mid;
        }
        else if (list[mid] < key)   // key in upper half
        {   low = mid + 1;
        }
        else                        // key in lower half
        {   high = mid - 1;
        }
    }
    return -1;                      // not in list
}

template <class Type, class Comparer>
int bsearch(const std::vector<Type>& list, const Type& key, const Comparer& c)
// precondition: list.size() == # elements in list, list sorted
// postcondition: returns index of key in list, -1 if key not found
{
    int low = 0;                   // leftmost possible entry
    int high = list.size()-1;      // rightmost possible entry
    int mid;                       // middle of current range
    while (low <= high)
    {   mid = (low + high)/2;
        int compVal = c.compare(list[mid],key);
        if (compVal == 0)       // found key, exit search
        {   return mid;
        }
        else if (compVal < 0)   // key in upper half
        {   low = mid + 1;
        }
        else                        // key in lower half
        {   high = mid - 1;
        }
    }
    return -1;                      // not in list
}
