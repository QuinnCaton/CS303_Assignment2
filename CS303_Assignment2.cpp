#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "omp.h"
using namespace std;


int getDotProduct(vector<int>&, vector<int>&);
int getDotProductOMP(vector<int>&, vector<int>&);
void insertStackElement(stack<int>&, int, int);

int main()
{
    vector<int> v1 = { 1, 2, 3, 4, 5 };
    vector<int> v2 = { 6, 7, 8, 9, 10 };
    stack<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(5);

    cout << "Without Multithreading: " << getDotProduct(v1, v2) << endl;
    cout << "With Multithreading: " << getDotProductOMP(v1, v2) << endl;
    cout << endl;
    cout << endl;
    insertStackElement(s1, 2, 1);
    while (s1.size() != 0) {
        cout << s1.top() << endl;
        s1.pop();
    }
}

//Dot product using standard for loop, no multithreading
//pre: 2 int vectors passed
//post: int total of dot product of two vectors
int getDotProduct(vector<int>& v1, vector<int>& v2) {

    int total = 0;

    for (int i = 0; i < v1.size(); ++i) {
        total += (v1.at(i) * v2.at(i));
    }

    return total;
}

//Dot product with multithreading
//Pre: 2 int vectors pass through for loop using 3 threads
//Post: int total returned, print statements showing 
//      iteration and thread nums
int getDotProductOMP(vector<int>& v1, vector<int>& v2) {
    int total = 0;
    int MAX = v1.size();

    omp_set_num_threads(3);

    #pragma omp parallel for shared(MAX)
    for (int i = 0; i < MAX; ++i) {
        total += (v1.at(i) * v2.at(i));
        int threadNum = omp_get_thread_num();
        printf("Iteration %d, Thread no. %d\n", i, threadNum);
    }

    return total;
}

//pre: int stack, element to add, position from top of stack to insert
//post: stack elements pop&top to temp stack, then back after 
//      new element has been added
void insertStackElement(stack<int>& s1, int element, int pos) {
    stack<int> temp = {};

    for (int i = 0; i < pos; ++i) {
        int newVar = s1.top();
        temp.push(newVar);
        s1.pop();
    }
    
    s1.push(element);

    for (int j = 0; j < temp.size(); ++j) {
        int pushVar = temp.top();
        s1.push(pushVar);
        temp.pop();
    }
}
