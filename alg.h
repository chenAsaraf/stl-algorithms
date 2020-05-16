// Implementation of algorithms similar to stl algorithms 
#include <algorithm>

/**
 * Add_n
 * Parameters:
 *           first, last	-	the range of elements in the container
 *           n              -   positive integer 
 * Return value: 
 *           Iterator to the element past the last element to sum.        
 * 
 * The algorithm sum up the first n elements and saves the
 * amount in the first place at the container,
 * sum up the next n members and saves it in the second place,
 * and so on.
 * If the container is empty - return value is last.
 * If the number of elements does not divided without a remainder in n,
 * the last sum will be the summing of (1, n-1) last elements.
 * 
 * example:
 * int ia[] = {1,2,3,4,5,6,7,8,9}; 
 * int * p = Add_n(begin(ia), end(ia), 3); 
 * result:
 * {6 5,24,4,5,6,7,8,9} , *p = 4
**/
template <class InputIt> 
InputIt Add_n(InputIt first, InputIt last, int n) {
    if (first == last) return last;
    InputIt temp = first;

    InputIt out_itr = first;
    auto sum = *first;
    /**
     *  why auto and not decltype?
     *  decltype will make 'sum' be exactly what  * operator returns- &T.
     *  auto will make 'sum' be the type T
    **/
    ++first;
    int counter = n-1;
    while(first!=last){
        if(counter > 0){
            sum = sum + *first;
            ++first;
            --counter;
            
        }
        else if (counter == 0) {
            *out_itr = sum;
            ++out_itr;
            sum = *first;
            ++first;
            counter = n-1;
        }
    }
    *out_itr = sum;
    ++out_itr;
    return out_itr;
}


/**
 * Transpose
 * Parameters:
 *           begin, end	-	the range of elements in the container
 * Return value: 
 *           Iterator to the last element or to the element past the last
 * 
 * The algorithm switches between two adjacent elements
 * If the number of elements is not even, the last one will not be replaced.
 * If the number of elements is even or the container is empty - return value is end.
 * If the number of elements is not even - return value is end - 1.
 * 
 * example:
 * int ia[] = {1,2,3,4,5,6,7,8,9}; 
 * int * p = Transpose(begin(ia), end(ia)); 
 * result:
 * {2,1,4,3,6,5,8,7,9} , *p = 9
**/
template <class InputIt> 
InputIt Transpose(InputIt begin, InputIt end){
if (begin == end)
    return end;

InputIt odd = begin;
InputIt even = begin + 1;

while (even != end){
    std::iter_swap(odd, even);
    odd = even + 1;
    if (odd == end) return odd;
    even = odd + 1;
}
return even-1;
}

/**
 * Transform
 * Parameters:
 *           begin, end	-	the range of elements in the container
 *           other      -   the beginning of the second range of elements to transform
 *           f          -   binary operation function object that will be applied.
 * Return value: 
 *           Output iterator to the element past the last element transformed.
 * 
 * The algorithm runs f on the first two elements in the first container and
 * saves the result in the first element of the other container, 
 * Then runs f on the next two elements in the first container and 
 * saves the result in the second element of the other container,
 * and so on.
 * If the number of elements is even - return value iterator to the
 * element past the last element transformed.
 * If the container is empty or number of element is not even - 
 * The algorithm will not run the function at all,
 * and the returned value will be an iterator for the start of the other container
 * 
 * example:
 * int ia[] = {1,2,3,10,8,6}; 
 * vector<int> vec(100);
 * int * p = Transform(begin(ia), end(ia), vec.begin(), 
 *            [](const int x, const int y){return x + y;}); 
 * int * p = Transpose(begin(ia), end(ia)); 
 * result:
 * {3,13,14, , ,    ... }
**/
template <class InputIt, class OutputIt, class BinaryOp>
OutputIt Transform(InputIt begin, InputIt end, OutputIt other, BinaryOp f){
    // If the first container is empty or have uneven elements - return
    if ((begin == end) or (std::distance(begin,end)%2 == 1)) 
        return other;
    
    InputIt odd = begin;
    InputIt even = begin + 1;
    while (true){
        *other = f(*odd, *even);
        ++other;
        odd = even + 1;
        if (odd == end) return other;
        even = odd + 1;
        }
    return other;
}