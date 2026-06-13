#include <iostream>
#include <stack>
#include <queue>
using namespace std;

// Helper function to transfer elements to an auxiliary stack
void reverseStackUsingAux(stack<int>& st, queue<int>& aux) {
    if (st.empty()) return;

    // Pop the top element and store it in the auxiliary stack
    int top = st.top();
    st.pop();
    aux.push(top);

    // Recursive call to process remaining elements
    reverseStackUsingAux(st, aux);

    // Push back to original stack in reversed order
    if (!aux.empty()) {
        st.push(aux.front());
        aux.pop();
    }
}

// Function to print the stack
void printStack(stack<int> st) {
    if (st.empty()) return;
    int top = st.top();
    st.pop();
    cout << top << " ";
    printStack(st);
    st.push(top); // Restore the stack
}

// Driver function
int main() {
    stack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    st.push(5);

    cout << "Original Stack: ";
    printStack(st);
    cout << endl;

    queue<int> aux; // Auxiliary stack
    reverseStackUsingAux(st, aux);

    cout << "Reversed Stack: ";
    printStack(st);
    cout << endl;

    return 0;
}
