#include <iostream>
#include <random>
#include <ctime>
#include <utility>      

int number_of_recursive_calls = 0;
int* first_line_memory;
int* second_line_memory;

int min(int first,int second) {
    if (first < second) return first;
    return second;    
}   

int a2_helper(int*& a1, int*& a2,int n,int*& t1, int*& t2, int e1, int e2);

int a1_helper(int*& a1, int*& a2,int n,int*& t1, int*& t2, int e1, int e2) {
    number_of_recursive_calls++;
    if (n==0){
        return e1 + a1[0];
    }
    else {
        return min(a1_helper(a1,a2,n-1,t1,t2,e1,e2) + a1[n] , a2_helper(a1,a2,n-1,t1,t2,e1,e2) + t2[n-1] + a1[n]);
    }
}

int a2_helper(int*& a1, int*& a2,int n,int*& t1, int*& t2, int e1, int e2) {
    number_of_recursive_calls++;
    if (n==0) {
        return e2 + a2[0];
    }
    else {
        return min(a2_helper(a1,a2,n-1,t1,t2,e1,e2) + a2[n], a1_helper(a1,a2,n-1,t1,t2,e1,e2) + t1[n-1] + a2[n]);
    }
}

std::pair<int,int> Assembly_Rec (int*& a1, int*& a2, int n, int*& t1, int*& t2, int e1, int e2, int x1, int x2)
{
    std::pair<int,int> retVal;
    int minimum = min(a1_helper(a1,a2,n-1,t1,t2,e1,e2) + x1 , a2_helper(a1,a2,n-1,t1,t2,e1,e2) + x2);
    retVal.first = minimum;
    retVal.second = number_of_recursive_calls;
    number_of_recursive_calls = 0;
    return retVal;
}

int a2_helper_memo(int*& a1, int*& a2,int n,int*& t1, int*& t2, int e1, int e2);

int a1_helper_memo(int*& a1, int*& a2,int n,int*& t1, int*& t2, int e1, int e2){
    number_of_recursive_calls++;
    if (first_line_memory[n] != 0) {
        return first_line_memory[n];
    }
    else if (n==0)
    {
        first_line_memory[n] = e1+a1[0];
        return e1 + a1[0];
    }
    else {
        int value = min(a1_helper_memo(a1,a2,n-1,t1,t2,e1,e2) + a1[n] , a2_helper_memo(a1,a2,n-1,t1,t2,e1,e2) + t2[n-1] + a1[n]);
        first_line_memory[n] = value;
        return value;
    }
}

int a2_helper_memo(int*& a1, int*& a2,int n,int*& t1, int*& t2, int e1, int e2) {
    number_of_recursive_calls++;
    if (second_line_memory[n] != 0) {
        return second_line_memory[n];
    }
    else if (n==0){
        second_line_memory[n] = e2 + a2[0];
        return e2 + a2[0];
    }
    else {
        int value = min(a2_helper_memo(a1,a2,n-1,t1,t2,e1,e2) + a2[n] , a1_helper_memo(a1,a2,n-1,t1,t2,e1,e2) + t1[n-1] + a2[n]);
        second_line_memory[n] = value;
        return value;
    }   
}

std::pair<int,int> Assembly_Memo (int*& a1, int*& a2, int n, int*& t1, int*& t2, int e1, int e2, int x1, int x2)
{
    std::pair<int,int> retVal;
    first_line_memory = new int[n]{0};
    second_line_memory = new int[n]{0};
    int minimum = min(a1_helper_memo(a1,a2,n-1,t1,t2,e1,e2) + x1 , a2_helper_memo(a1,a2,n-1,t1,t2,e1,e2) + x2);
    retVal.first = minimum;
    retVal.second = number_of_recursive_calls;
    number_of_recursive_calls = 0;
    delete [] first_line_memory;
    delete [] second_line_memory;
    return retVal;
}


std::pair<int,int> Assembly_Tab (int*& a1, int*& a2, int n, int*& t1, int*& t2, int e1, int e2, int x1, int x2)
{
    
    std::pair<int,int> retVal;
    int iteration_count = 0;
    first_line_memory = new int[n]{0};
    second_line_memory = new int[n]{0};

    
    first_line_memory[0] = e1 + a1[0];
    second_line_memory[0] = e2 + a2[0];
    
    
    for (int j=1;j<n;j++) {
        iteration_count++;
        if (first_line_memory[j-1] + a1[j] <= second_line_memory[j-1] + t2[j-1] + a1[j])
            first_line_memory[j] = first_line_memory[j-1] + a1[j];
        else
            first_line_memory[j] = second_line_memory[j-1] + t2[j-1] + a1[j];
        if (second_line_memory[j-1] + a2[j] <= first_line_memory[j-1] + t1[j-1] + a2[j])
            second_line_memory[j] = second_line_memory[j-1] + a2[j];
        else
            second_line_memory[j] = first_line_memory[j-1] + t1[j-1] + a2[j];
    }
    
    
    retVal.first = min(first_line_memory[n-1] + x1,second_line_memory[n-1] + x2);

    retVal.second = iteration_count+1;
    
    
    delete [] first_line_memory;
    delete [] second_line_memory;
    
    return retVal;
    
}