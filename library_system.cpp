#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

const int MAX = 100;

class Book {
private:
    int bookId;
    string title;
    string author;
    int publicationYear;
    int totalCopies;
    int availableCopies;

public:
    Book() {
        bookId = 0;
        title = "Unknown";
        author = "Unknown";
        publicationYear = 0;
        totalCopies = 0;
        availableCopies = 0;
    }

    Book(int id, string t, string a, int year, int copies) {
        bookId = id;
        title = t;
        author = a;
        publicationYear = year;
        totalCopies = copies;
        availableCopies = copies;
    }

    int getId() const {
        return bookId;
    }

    string getTitle() const {
        return title;
    }

    string getAuthor() const {
        return author;
    }

    int getYear() const {
        return publicationYear;
    }

    int getTotalCopies() const {
        return totalCopies;
    }

    int getAvailableCopies() const {
        return availableCopies;
    }

    void display() const {
        cout << "ID: " << bookId << " | Title: " << title << " | Author: " << author
             << " | Year: " << publicationYear << " | Total: " << totalCopies
             << " | Available: " << availableCopies << "\n";
    }

    void issueBook() {
        if (availableCopies == 0) {
            throw runtime_error("No copies available to issue.");
        }
        availableCopies--;
    }

    void returnBook() {
        if (availableCopies == totalCopies) {
            throw runtime_error("All copies are already in the library.");
        }
        availableCopies++;
    }
};

int searchBook(Book books[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (books[i].getId() == id) {
            return i;
        }
    }
    return -1;
}

void addBook(Book books[], int &count, int id, string title, string author, int year, int copies) {
    if (count >= MAX) {
        throw runtime_error("Library is full.");
    }
    if (copies < 0) {
        throw runtime_error("Copies cannot be negative.");
    }
    if (searchBook(books, count, id) != -1) {
        throw runtime_error("A book with this ID already exists.");
    }
    books[count] = Book(id, title, author, year, copies);
    count++;
}

void displayAll(Book books[], int count) {
    if (count == 0) {
        cout << "No books in the library.\n";
        return;
    }
    for (int i = 0; i < count; i++) {
        books[i].display();
    }
}

void displayByAuthor(Book books[], int count, string author) {
    bool found = false;
    for (int i = 0; i < count; i++) {
        if (books[i].getAuthor() == author) {
            books[i].display();
            found = true;
        }
    }
    if (!found) {
        cout << "No books found for this author.\n";
    }
}

void sortByYear(Book books[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (books[j].getYear() > books[j + 1].getYear()) {
                Book temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
}

bool readAndAddBook(Book books[], int &count) {
    int id, year, copies;
    string title, author;

    cout << "Book ID: ";
    cin >> id;
    cout << "Title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Author: ";
    getline(cin, author);
    cout << "Publication Year: ";
    cin >> year;
    cout << "Total Copies: ";
    cin >> copies;

    try {
        addBook(books, count, id, title, author, year, copies);
        cout << "Book added.\n";
        return true;
    } catch (runtime_error &e) {
        cout << "Error: " << e.what() << "\n";
        return false;
    }
}

int main() {
    Book books[MAX];
    int count = 0;
    int n;

    cout << "How many books do you want to add? ";
    cin >> n;
    while (n < 0 || n > MAX) {
        cout << "Enter a number between 0 and " << MAX << ": ";
        cin >> n;
    }

    while (count < n) {
        cout << "\nBook " << count + 1 << "\n";
        readAndAddBook(books, count);
    }

    cout << "\nBook Catalogue\n";
    displayAll(books, count);

    int choice;
    do {
        cout << "\n1. Add a new book\n2. Search for a book\n3. Issue a book\n4. Return a book\n";
        cout << "5. Display all books\n6. Search books by author\n";
        cout << "7. Display books sorted by publication year\n8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        try {
            switch (choice) {
            case 1:
                readAndAddBook(books, count);
                break;
            case 2: {
                int id;
                cout << "Book ID: ";
                cin >> id;
                int index = searchBook(books, count, id);
                if (index == -1) {
                    throw runtime_error("Book does not exist.");
                }
                books[index].display();
                break;
            }
            case 3: {
                int id;
                cout << "Book ID: ";
                cin >> id;
                int index = searchBook(books, count, id);
                if (index == -1) {
                    throw runtime_error("Book does not exist.");
                }
                books[index].issueBook();
                cout << "Book issued.\n";
                break;
            }
            case 4: {
                int id;
                cout << "Book ID: ";
                cin >> id;
                int index = searchBook(books, count, id);
                if (index == -1) {
                    throw runtime_error("Book does not exist.");
                }
                books[index].returnBook();
                cout << "Book returned.\n";
                break;
            }
            case 5:
                displayAll(books, count);
                break;
            case 6: {
                string author;
                cout << "Author Name: ";
                cin.ignore();
                getline(cin, author);
                displayByAuthor(books, count, author);
                break;
            }
            case 7: {
                Book sorted[MAX];
                for (int i = 0; i < count; i++) {
                    sorted[i] = books[i];
                }
                sortByYear(sorted, count);
                displayAll(sorted, count);
                break;
            }
            case 8:
                break;
            default:
                cout << "Invalid choice.\n";
            }
        } catch (runtime_error &e) {
            cout << "Error: " << e.what() << "\n";
        }
    } while (choice != 8);

    return 0;
}
