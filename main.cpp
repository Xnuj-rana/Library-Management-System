
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string CYAN = "\033[36m";
const string MAGENTA = "\033[35m";

class Person {
protected:
    string name;
    int id;

public:
    Person(string n, int i) {
        name = n;
        id = i;
    }

    void displayInfo() {
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
    }
};

class Student : public Person {
public:
    Student(string n, int i) : Person(n, i) {
    }

    void displayStudent() {
        cout << GREEN << "\n--- STUDENT PROFILE ---\n"
             << RESET;
        displayInfo();
        cout << "Role: Book Borrower\n";
    }
};

class Librarian : public Person {
public:
    Librarian(string n, int i) : Person(n, i) {
    }

    void displayLibrarian() {
        cout << MAGENTA << "\n--- LIBRARIAN PROFILE ---\n"
             << RESET;
        displayInfo();
        cout << "Role: Library Manager\n";
    }
};

class Book {
private:
    int bookID;
    string title;
    string author;
    int issued;

public:
    Book() {
        bookID = 0;
        title = "";
        author = "";
        issued = 0;
    }

    void addBook(int id, string t, string a) {
        bookID = id;
        title = t;
        author = a;
        issued = 0;
    }

    int getID() {
        return bookID;
    }

    string getTitle() {
        return title;
    }

    int getIssued() {
        return issued;
    }

    void issueBook() {
        issued = 1;
    }

    void returnBook() {
        issued = 0;
    }

    void displayBook() {
        cout << left
             << setw(10) << bookID
             << setw(25) << title
             << setw(22) << author;

        if (issued == 1) {
            cout << RED << "Issued" << RESET;
        } else {
            cout << GREEN << "Available" << RESET;
        }

        cout << endl;
    }
};

class Library {
private:
    Book books[100];
    int count;

public:
    Library() {
        count = 0;
    }

    void addBook() {
        if (count >= 100) {
            cout << RED << "\nLibrary is full!\n" << RESET;
            return;
        }

        int id;
        string title, author;

        cout << YELLOW << "\n--- ADD NEW BOOK ---\n" << RESET;

        cout << CYAN << "Enter Book ID: " << RESET;
        cin >> id;

        if (id <= 0) {
            cout << RED << "Book ID must be positive!\n" << RESET;
            return;
        }

        for (int i = 0; i < count; i++) {
            if (books[i].getID() == id) {
                cout << RED << "This ID already exists!\n" << RESET;
                return;
            }
        }

        cin.ignore(10000, '\n');

        cout << CYAN << "Enter Book Title: " << RESET;
        getline(cin, title);

        cout << CYAN << "Enter Author Name: " << RESET;
        getline(cin, author);

        if (title.empty() || author.empty()) {
            cout << RED << "Title and author cannot be empty!\n"
                 << RESET;
            return;
        }

        books[count].addBook(id, title, author);
        count++;

        cout << GREEN << "\nBook added successfully!\n" << RESET;
    }

    void displayBooks() {
        cout << YELLOW << "\n========== BOOK COLLECTION ==========\n"
             << RESET;

        if (count == 0) {
            cout << RED << "No books available.\n" << RESET;
            return;
        }

        cout << left
             << setw(10) << "Book ID"
             << setw(25) << "Title"
             << setw(22) << "Author"
             << "Status" << endl;

        cout << "----------------------------------------------------------"
             << endl;

        for (int i = 0; i < count; i++) {
            books[i].displayBook();
        }

        cout << "\nTotal books: " << count << endl;
    }

    void searchBook() {
        int id;
        int found = 0;

        cout << CYAN << "\nEnter Book ID to search: " << RESET;
        cin >> id;

        for (int i = 0; i < count; i++) {
            if (books[i].getID() == id) {
                cout << GREEN << "\nBook found!\n" << RESET;
                books[i].displayBook();
                found = 1;
                break;
            }
        }

        if (found == 0) {
            cout << RED << "Book not found!\n" << RESET;
        }
    }

    void issueBook() {
        int id;
        int found = 0;

        cout << CYAN << "\nEnter Book ID to issue: " << RESET;
        cin >> id;

        for (int i = 0; i < count; i++) {
            if (books[i].getID() == id) {
                found = 1;

                if (books[i].getIssued() == 1) {
                    cout << RED << "Book is already issued!\n"
                         << RESET;
                } else {
                    books[i].issueBook();
                    cout << GREEN << "Book issued successfully!\n"
                         << RESET;
                }

                break;
            }
        }

        if (found == 0) {
            cout << RED << "Book not found!\n" << RESET;
        }
    }

    void returnBook() {
        int id;
        int found = 0;

        cout << CYAN << "\nEnter Book ID to return: " << RESET;
        cin >> id;

        for (int i = 0; i < count; i++) {
            if (books[i].getID() == id) {
                found = 1;

                if (books[i].getIssued() == 0) {
                    cout << RED << "Book was not issued!\n"
                         << RESET;
                } else {
                    books[i].returnBook();
                    cout << GREEN << "Book returned successfully!\n"
                         << RESET;
                }

                break;
            }
        }

        if (found == 0) {
            cout << RED << "Book not found!\n" << RESET;
        }
    }
};

int main() {
    Library library;

    Student student("Alex", 101);
    Librarian librarian("Jordan", 501);

    int choice;

    cout << CYAN << "\n";
    cout << "============================================\n";
    cout << "       LIBRARY MANAGEMENT SYSTEM\n";
    cout << "============================================\n";
    cout << "     Read More | Learn More | Grow More\n";
    cout << "============================================\n" << RESET;

    do {
        cout << YELLOW << "\n============== MAIN MENU ==============\n"
             << RESET;

        cout << GREEN;
        cout << "1. Add New Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. Student Profile\n";
        cout << "7. Librarian Profile\n";
        cout << RED << "0. Exit\n" << RESET;

        cout << CYAN << "\nEnter your choice: " << RESET;
        cin >> choice;

        switch (choice) {
            case 1:
                library.addBook();
                break;

            case 2:
                library.displayBooks();
                break;

            case 3:
                library.searchBook();
                break;

            case 4:
                library.issueBook();
                break;

            case 5:
                library.returnBook();
                break;

            case 6:
                student.displayStudent();
                break;

            case 7:
                librarian.displayLibrarian();
                break;

            case 0:
                cout << MAGENTA
                     << "\nThanks for visiting the library!\n"
                     << "Keep reading and keep growing!\n"
                     << RESET;
                break;

            default:
                cout << RED << "Invalid choice! Try again.\n"
                     << RESET;
        }

    } while (choice != 0);

    return 0;
}
