#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Base class Employee
class Employee {
protected:
    string name, department;
    int id;
    double salary;

public:
    Employee() {} // Default constructor

    Employee(string n, int i, string dept, double sal)
        : name(n), id(i), department(dept), salary(sal) {}

    virtual void displayDetails() {
        cout << "ID: " << id << ", Name: " << name
             << ", Department: " << department
             << ", Salary: " << salary << endl;
    }

    int getID() { return id; }

    virtual void saveToFile(ofstream &outfile) {
        outfile << id << " " << name << " " << department << " " << salary << "\n";
    }

    virtual ~Employee() {} // Virtual destructor for proper cleanup
};

// Derived class PermanentEmployee
class PermanentEmployee : public Employee {
private:
    double bonus;

public:
    PermanentEmployee(string n, int i, string dept, double sal, double b)
        : Employee(n, i, dept, sal), bonus(b) {}

    void displayDetails() override {
        cout << "[Permanent Employee] ";
        Employee::displayDetails();
        cout << "Bonus: " << bonus << endl;
    }

    void saveToFile(ofstream &outfile) override {
        outfile << "P " << id << " " << name << " " << department << " " << salary << " " << bonus << "\n";
    }
};

// Derived class ContractEmployee
class ContractEmployee : public Employee {
private:
    int contractDuration; // in months

public:
    ContractEmployee(string n, int i, string dept, double sal, int duration)
        : Employee(n, i, dept, sal), contractDuration(duration) {}

    void displayDetails() override {
        cout << "[Contract Employee] ";
        Employee::displayDetails();
        cout << "Contract Duration: " << contractDuration << " months\n";
    }

    void saveToFile(ofstream &outfile) override {
        outfile << "C " << id << " " << name << " " << department << " " << salary << " " << contractDuration << "\n";
    }
};

// Function Overloading: Add Employee by taking different inputs
Employee* addEmployee(string type) {
    string name, department;
    int id;
    double salary;

    cout << "Enter Employee ID: ";
    cin >> id;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Department: ";
    cin >> department;
    cout << "Enter Salary: ";
    cin >> salary;

    if (type == "P") {
        double bonus;
        cout << "Enter Bonus: ";
        cin >> bonus;
        return new PermanentEmployee(name, id, department, salary, bonus);
    } else if (type == "C") {
        int duration;
        cout << "Enter Contract Duration (months): ";
        cin >> duration;
        return new ContractEmployee(name, id, department, salary, duration);
    }
    return new Employee(name, id, department, salary);
}

// Function to Save Employees to File
void saveEmployeesToFile(vector<Employee*> &employees) {
    ofstream outfile("employees.txt");
    for (auto emp : employees) {
        emp->saveToFile(outfile);
    }
    outfile.close();
    cout << "Employees saved successfully!\n";
}

// Function to Load Employees from File
vector<Employee*> loadEmployeesFromFile() {
    vector<Employee*> employees;
    ifstream infile("employees.txt");
    if (!infile) {
        cout << "No existing employee records found.\n";
        return employees;
    }

    char type;
    string name, department;
    int id;
    double salary;

    while (infile >> type >> id >> name >> department >> salary) {
        if (type == 'P') {
            double bonus;
            infile >> bonus;
            employees.push_back(new PermanentEmployee(name, id, department, salary, bonus));
        } else if (type == 'C') {
            int duration;
            infile >> duration;
            employees.push_back(new ContractEmployee(name, id, department, salary, duration));
        } else {
            employees.push_back(new Employee(name, id, department, salary));
        }
    }
    infile.close();
    return employees;
}

// Function to Display All Employees
void displayEmployees(vector<Employee*> &employees) {
    if (employees.empty()) {
        cout << "No employees found!\n";
        return;
    }
    cout << "\n--- Employee List ---\n";
    for (auto emp : employees) {
        emp->displayDetails();
    }
}

// Function to Delete Employee
void deleteEmployee(vector<Employee*> &employees, int id) {
    for (auto it = employees.begin(); it != employees.end(); ++it) {
        if ((*it)->getID() == id) {
            delete *it; // Free memory
            employees.erase(it);
            cout << "Employee with ID " << id << " deleted successfully!\n";
            return;
        }
    }
    cout << "Employee with ID " << id << " not found!\n";
}

// Main Menu Function
void menu() {
    vector<Employee*> employees = loadEmployeesFromFile();
    int choice;

    do {
        cout << "\n==== Employee Management System ====\n";
        cout << "1. Add Employee\n";
        cout << "2. View Employees\n";
        cout << "3. Delete Employee\n";
        cout << "4. Save and Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string type;
                cout << "Enter Employee Type (P for Permanent, C for Contract): ";
                cin >> type;
                employees.push_back(addEmployee(type));
                break;
            }
            case 2:
                displayEmployees(employees);
                break;
            case 3: {
                int id;
                cout << "Enter Employee ID to delete: ";
                cin >> id;
                deleteEmployee(employees, id);
                break;
            }
            case 4:
                saveEmployeesToFile(employees);
                for (auto emp : employees) delete emp; // Free memory before exit
                cout << "Exiting...\n";
                return;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (true);
}

// Main Function
int main() {
    menu();
    return 0;
}
