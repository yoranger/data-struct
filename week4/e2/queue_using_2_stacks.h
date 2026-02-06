#ifndef QUEUE_USING_2_STACKS_H
#define QUEUE_USING_2_STACKS_H

#include <stack>

struct Queue {
    Queue();
    void enqueue(int x);
    int dequeue();
    private:
    std::stack<int> s1, s2; // declaration of two stacks
};

#endif // QUEUE_USING_2_STACKS_H