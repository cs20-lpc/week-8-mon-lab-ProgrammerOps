// my_driver_analogy.cpp — Stack Testing Playground
// -----------------------------------------------------------
// Imagine we are running a pancake restaurant 
// Every stack here is a pile of pancakes (or toy cars, or cards).
// We test pushing (adding pancakes), popping (eating one),
// peeking (looking at the top pancake), and rotating the pile
// (moving the top pancake to the bottom or vice versa).
// -----------------------------------------------------------

#include <iostream>
#include <string>
#include "ArrayStack.hpp"   // our tray of pancakes (the real stack)
using namespace std;

// -----------------------------------------------------------
//  printStack()
// Think of this like showing the waiter what pancakes are on
// the tray from top to bottom.
// -----------------------------------------------------------
template <typename T>
void printStack(const string& label, const ArrayStack<T>& s) {
    cout << "\n=== " << label << " ===\n" << s;
}

// -----------------------------------------------------------
//  testRotate()
// This function plays with the tray: it spins the pancakes.
// RIGHT = move top pancake to bottom.
// LEFT  = move bottom pancake to top.
// -----------------------------------------------------------
template <typename T>
void testRotate(ArrayStack<T>& st) {
    cout << "\n[Rotate tests] Initial pancake stack:\n";
    cout << st;

    // Rotate RIGHT (top pancake goes under all others)
    st.rotate(Stack<T>::RIGHT);
    cout << "\nAfter RIGHT rotate (top→bottom):\n";
    cout << st;

    // Rotate LEFT (bottom pancake climbs to top)
    st.rotate(Stack<T>::LEFT);
    cout << "\nAfter LEFT rotate (top→bottom):\n";
    cout << st;
}

// -----------------------------------------------------------
//  pushRange()
// Adds several pancakes in a loop.  If we run out of space,
// the cook shouts "tray is full!" (throws an exception).
// -----------------------------------------------------------
template <typename T, typename F>
void pushRange(ArrayStack<T>& st, int count, F maker) {
    for (int i = 0; i < count; ++i) {
        try {
            // The "maker" decides what kind of pancake to make
            st.push(maker(i));
            cout << "pushed: " << st.peek()
                 << "   length=" << st.getLength() << '\n';
        }
        catch (string& e) {
            cout << " EXCEPTION (push): " << e << '\n';
        }
    }
}

// -----------------------------------------------------------
// 🏁 main() — Let's run our pancake experiments!
// -----------------------------------------------------------
int main() {
    try {
        // ===================================================
        //  TEST 1 — Integer Stack
        // ===================================================
        ArrayStack<int> a(5);  // Tray can hold 5 pancakes (numbers)
        cout << "Created ArrayStack<int> a(5)\n";
        cout << "isEmpty? " << (a.isEmpty() ? "yes" : "no") << '\n';
        cout << "isFull?  " << (a.isFull()  ? "yes" : "no") << '\n';

        // Add pancakes numbered 1..5
        pushRange<int>(a, a.getMaxSize(), [](int i){ return i+1; });
        cout << "isFull now? " << (a.isFull() ? "yes" : "no") << '\n';
        printStack("a (full stack of pancakes)", a);

        // Spin the tray like a lazy-Susan 
        testRotate<int>(a);

        // Try adding when tray is full
        cout << "\nTry pushing on full stack a: ";
        try { a.push(999); }
        catch (string& e) { cout << "caught: " << e << '\n'; }

        // Eat (pop) 3 pancakes from top
        cout << "\nPopping three from a:\n";
        for (int i = 0; i < 3; ++i) {
            try {
                cout << "peek=" << a.peek() << " -> pop\n";
                a.pop();
            } catch (string& e) {
                cout << " EXCEPTION (pop/peek): " << e << '\n';
            }
        }
        printStack("a after 3 pancakes eaten", a);

        // Copy constructor — make another tray just like it
        ArrayStack<int> b = a;
        printStack("b (copy of a)", b);

        // Clear b (wash the tray clean)
        b.clear();
        cout << "\nCleared b. isEmpty? " << (b.isEmpty() ? "yes" : "no") << '\n';

        // Try removing/peeking when tray is empty
        cout << "Try pop on empty b: ";
        try { b.pop(); } catch (string& e) { cout << "caught: " << e << '\n'; }
        cout << "Try peek on empty b: ";
        try { (void)b.peek(); } catch (string& e) { cout << "caught: " << e << '\n'; }

        // Assignment operator — copy tray a into tray c
        ArrayStack<int> c;
        c = a;
        printStack("c = a (assignment copy)", c);

        // ===================================================
        //  TEST 2 — String Stack
        // ===================================================
        ArrayStack<string> s(4);  // Tray for 4 flavor pancakes
        cout << "\n\nCreated ArrayStack<string> s(4)\n";

        // Each pancake has a flavor name
        pushRange<string>(s, 4, [](int i){
            static const char* flavors[] = {"chocolate","vanilla","strawberry","banana","blueberry"};
            return string(flavors[i % 5]);
        });

        printStack("s (full flavor stack)", s);

        // Spin the tray both ways again
        testRotate<string>(s);

        // Eat all the pancakes until tray empty
        cout << "\nPopping all from s:\n";
        while (!s.isEmpty()) {
            cout << "peek=" << s.peek() << " -> pop\n";
            s.pop();
        }

        // Try one more peek when tray is empty
        cout << "Now s is empty. Try one more peek: ";
        try { (void)s.peek(); } catch (string& e) { cout << "caught: " << e << '\n'; }

        cout << "\nAll pancake experiments complete! \n";
    }
    catch (const std::exception& ex) {
        cerr << "std::exception: " << ex.what() << '\n';
    }
    return 0;
}
