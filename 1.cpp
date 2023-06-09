#include <iostream>
#include <string>

using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int value) {
        data = value;
        next = NULL;
    }
};

class Stack {
public:
    Node* top;
public:
    Stack() {
        top = NULL;
    }
    void push(int value) {
        Node* newNode = new Node(value);
        if (top == NULL) {
            top = newNode;
        }
        else {
            newNode->next = top;
            top = newNode;
        }
    }
    int pop() {
        if (top == NULL) {
            cout << "Stack is empty!" << endl;
            return -1;
        }
        else {
            int value = top->data;
            Node* temp = top;
            top = top->next;
            delete temp;
            return value;
        }
    }
    bool isEmpty() {
        return top == NULL;
    }
};

class Queue {
private:
    Node* front;
    Node* rear;
public:
    Queue() {
        front = NULL;
        rear = NULL;
    }
    void enqueue(int value) {
        Node* newNode = new Node(value);
        if (rear == NULL) {
            front = newNode;
            rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
    }
    int dequeue() {
        if (front == NULL) {
            cout << "Queue is empty!" << endl;
            return -1;
        }
        else {
            int value = front->data;
            Node* temp = front;
            front = front->next;
            if (front == NULL) {
                rear = NULL;
            }
            delete temp;
            return value;
        }
    }
    bool isEmpty() {
        return front == NULL;
    }
};

class Calculator {
private:
    Stack stack;
    Queue queue;
public:
    void infixToPostfix(string expression) {
        for (int i = 0; i < expression.length(); i++) {
            char c = expression[i];
            if (isdigit(c)) {
                int num = c - '0';
                queue.enqueue(num);
            }
            else if (c == '+' ||  c == '-' ||  c == '*' || c == '/') {
                while (!stack.isEmpty() && precedence(stack.top->data) >= precedence(c)) {
                    queue.enqueue(stack.pop());
                }
                stack.push(c);
            }
            else if (c == '(') {
                stack.push(c);
            }
            else if (c == ')') {
                while (!stack.isEmpty() && stack.top->data != '(') {
                    queue.enqueue(stack.pop());
                }
                if (!stack.isEmpty() && stack.top->data == '(') {
                    stack.pop();
                }
                else {
                    cout << "Invalid expression!" << endl;
                    return;
                }
            }
            else {
                cout << "Invalid expression!" << endl;
                return;
            }
        }
        while (!stack.isEmpty()) {
            if (stack.top->data == '(' || stack.top->data == ')') {
                cout << "Invalid expression!" << endl;
                return;
            }
            queue.enqueue(stack.pop());
        }
    }
    void evaluate() {
        while (!queue.isEmpty()) {
            int value = queue.dequeue();
            if (value >= 0 && value <= 9) {
                stack.push(value);
            }
            else if (value == '+' ||  value == '-' ||  value == '*' || value == '/') {
                if (stack.isEmpty()) {
                    cout << "Invalid expression!" << endl;
                    return;
                }
                int num2 = stack.pop();
                if (stack.isEmpty()) {
                    cout << "Invalid expression!" << endl;
                    return;
                }
                int num1 = stack.pop();
                switch (value) {
                    case '+':
                        stack.push(num1 + num2);
                        break;
                    case '-':
                        stack.push(num1 - num2);
                        break;
case
'*':
stack.push(num1 * num2);
                        break;
                    case '/':
                        if (num2 == 0) {
                            cout << "Invalid expression!" << endl;
                            return;
                        }
                        stack.push(num1 / num2);
                        break;
                }
            }
        }
        if (!stack.isEmpty()) {
            int result = stack.pop();
            if (stack.isEmpty()) {
                cout << "Result: " << result << endl;
            }
            else {
                cout << "Invalid expression!" << endl;
            }
        }
        else {
            cout << "Invalid expression!" << endl;
        }
    }
    int precedence(char op) {
        if (op == '+' || op == '-') {
            return 1;
        }
        else if (op == '*' || op == '/') {
            return 2;
        }
        else {
            return 0;
        }
    }
};

int main() {
    Calculator calc;
    string expression;
    cout << "Enter infix expression: ";
    getline(cin, expression);
    calc.infixToPostfix(expression);
    calc.evaluate();
    return 0;
};