#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Book {
public:
    string title, author;
    int id;

    void getData() {
        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Book Title: ";
        getline(cin, title);
        cout << "Enter Author Name: ";
        getline(cin, author);
    }

    void displayData() {
        cout << "ID: " << id << ", Title: " << title << ", Author: " << author << endl;
    }
};

// Save book details to file
void saveBook(Book book) {
    ofstream file("books.txt", ios::app);
    file << book.id << "," << book.title << "," << book.author << endl;
    file.close();
}

// Read books from file
void showBooks() {
    ifstream file("books.txt");
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

int main() {
    int choice;
    while (true) {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n2. View Books\n3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            Book book;
            book.getData();
            saveBook(book);
        } else if (choice == 2) {
            showBooks();
        } else {
            break;
        }
    }

    return 0;
}
