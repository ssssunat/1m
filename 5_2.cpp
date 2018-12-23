/*Пара слов называется стековой анаграмой, если одно слово можно получить из другого,
проведя последовательность стековых операций с его буквами (взять очередную букву исходного слова и поместить ее в стек; 
взять букву из стека и добавить ее в конец выходного слова). 
Для заданной пары слов требуется определить, можно ли выполнить последовательность стековых операций, переводящую первое слово во второе. 
Все буквы в слове различные. Длина анаграммы ≤ 10000.*/
#include <bits/stdc++.h>

int initialSize = 256;

class Stack {
public:
    Stack() : bufferSize(initialSize), top(0) { buffer = new char[initialSize]; };

    ~Stack() { delete[] buffer; }

    void push(char element);

    char pop();

    bool empty();

private:
    char *buffer;
    int bufferSize;
    int top;

    void grow();

};

void Stack::push(char element) {
    if (top == bufferSize) {
        grow();
    }
    buffer[top++] = element;
}

char Stack::pop() {
    assert(top > 0);
    return buffer[top--];
}

bool Stack::empty() {
    return (top == 0);
}

bool type(char c) {
    return (c == ')' || c == ']' || c == '}');
}

void Stack::grow() {
    int newBufferSize = 2 * bufferSize;
    char *newBuffer = new char[newBufferSize];
    for (int i = 0; i < bufferSize; ++i) {
        newBuffer[i] = buffer[i];
    }
    top = bufferSize;
    delete[] buffer;
    buffer = newBuffer;
    bufferSize = newBufferSize;
}

int main() {
    char *string = new char[20000];
    char c = 0;
    int length = 0;

    while (std::cin >> c) {
        string[length++] = c;
    }

    length /= 2;

    int j = 0;
    Stack stack;

    for (int i = 0; i < length; ++i) {
        if (string[i] != string[length + j]) {
            if (stack.empty()) {
                stack.push(string[i]);
            } else {
                c = stack.pop();
                if (string[length + j] == c) {
                    j++;
                    i--;
                } else {
                    stack.push(c);
                    stack.push(string[i]);
                }
            }
        } else {
            j++;
        }
    }

    while (stack.empty()!=0) {
        if (string[length + j] != stack.pop()) {
            std::cout << "NO\n";
            return 0;
        } else {
            j++;
        }
    }

    std::cout << "YES\n";

    return 0;
}
