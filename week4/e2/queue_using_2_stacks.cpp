// CPP program to implement Queue using
// two stacks with costly deQueue()
#include <stack>
#include "queue_using_2_stacks.h"
#include <iostream>
using namespace std;

Queue::Queue()
{
	// Constructor (don't change this)
}

void Queue::enqueue(int x)
{
    // How would you use the two stacks s1 and s2 to implement enqueue?
    // YOUR CODE GOES HERE
    s1.emplace(x);
}

int Queue::dequeue()
{
    // How would you use the two stacks s1 and s2 to implement dequeue?
    // HINT 1: Use one stack to hold the incoming items
    // HINT 2: Use the other stack to hold the outgoing items
    // HINT 3: You may need to move items between the two stacks
    // YOUR CODE GOES HERE
    if(s1.empty() && s2.empty())
        return -1;
    size_t size = s1.size();
    if(s2.empty())
        for (size_t i = 0; i < size; ++i)
        {
            s2.emplace(s1.top());
            s1.pop();
        }
    int val = s2.top();
    s2.pop();
    
    return val;
}