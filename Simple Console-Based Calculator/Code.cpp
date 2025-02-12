#include <iostream>
using namespace std;

void add(double a, double b) 
{ 
    cout << "Result: " << a + b << endl; 
}
void subtract(double a, double b)
{ 
    cout << "Result: " << a - b << endl; 
}
void multiply(double a, double b)
{ 
    cout << "Result: " << a * b << endl; 
}
void divide(double a, double b) 
{
    if (b == 0) 
        cout << "Error! Division by zero." << endl;
    else 
        cout << "Result: " << a / b << endl;
}

int main() 
{
    int choice;
    double num1, num2;

    do {
        cout << "\nSimple Calculator\n";
        cout << "1. Add\n2. Subtract\n3. Multiply\n4. Divide\n5. Exit\n";
        cout << "Choose an operation: ";
        cout << "Enter your choice [1 to 4] :";
        cin >> choice;

        if (choice >= 1 && choice <= 4) 
        {
            cout << "Enter two numbers: ";
            cin >>  num1 >> num2;
        }

        switch (choice)
         {
            case 1: add(num1, num2); break;
            case 2: subtract(num1, num2); break;
            case 3: multiply(num1, num2); break;
            case 4: divide(num1, num2); break;
            case 5: cout << "Exiting..."; break;
            default: cout << "Invalid choice!";
        }
    } while(choice != 5);

    return 0;
}
