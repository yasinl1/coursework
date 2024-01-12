#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <limits>  // numeric_limits

struct Book {
    int id;
    std::string name;
    std::string author;
    std::string type;  // e.g., "Science Fiction", "Satire", etc.
    int pageCount;
    bool isBorrowed = false;
    time_t dueDate;
};

struct Member {
    std::string name;
    std::string email;
    std::string address;
    std::vector<Book*> borrowedBooks;
};

class Library {
private:
    std::vector<Book> books;
    std::vector<Member> members;

public:
    // Method to find a book by its ID
    Book* findBookById(int id) {
        for (auto& book : books) {
            if (book.id == id) {
                return &book;
            }
        }
        return nullptr;  // Return nullptr if book not found
    }

  void addMember(const std::string& name, const std::string& email, const std::string& address) {
    static int memberIdCounter = 1;
    Member newMember = {name, email, address};
    members.push_back(newMember);
    std::cout << "Member added successfully with ID: " << memberIdCounter << std::endl;
    memberIdCounter++;
}

  
void loadBooksFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        Book book;

        
        std::getline(ss, token, ',');  // id
        token.erase(std::remove_if(token.begin(), token.end(), ::isspace), token.end());  
        book.id = std::stoi(token);

        std::getline(ss, book.name, ',');
        std::getline(ss, book.author, ',');
        std::getline(ss, book.type, ',');

        std::getline(ss, token);  // page count
        book.pageCount = std::stoi(token);

        books.push_back(book);  
    }

    file.close();
    std::cout << "Books loaded successfully from CSV!" << std::endl;
}
  
    void issueBook(int bookId, int memberId) {
        Book* book = findBookById(bookId);
        if (!book) {
            std::cout << "Invalid book ID!" << std::endl;
            return;
        }
        if (members.size() < memberId) {
            std::cout << "Invalid member ID!" << std::endl;
            return;
        }
        if (book->isBorrowed) {
            std::cout << "Book is already borrowed!" << std::endl;
            return;
        }
        book->isBorrowed = true;
        time_t now = time(0);
        book->dueDate = now + 3 * 24 * 60 * 60; // 3 days from now
        members[memberId - 1].borrowedBooks.push_back(book);
        std::cout << "Book issued successfully!" << std::endl;
    }

 
void returnBook(int bookId, int memberId) {
    Book* book = findBookById(bookId);
    
    if (!book) {
        std::cout << "Invalid book ID!" << std::endl;
        return;  // Return without further processing
    }

    if (memberId <= 0 || memberId > static_cast<int>(members.size())) {
        std::cout << "Invalid member ID!" << std::endl;
        return;  // Return without further processing
    }

    if (!book->isBorrowed) {
        std::cout << "Book is not borrowed!" << std::endl;
        return;  // Return without further processing
    }

    time_t now = time(0);
    double diff = difftime(now, book->dueDate);
    if (diff > 0) {
        int fine = static_cast<int>(diff / (24 * 60 * 60));
        std::cout << "Fine to be paid: £" << fine << std::endl;
    }

    std::vector<Book*>& memberBorrowedBooks = members[memberId - 1].borrowedBooks;
    auto it = std::find(memberBorrowedBooks.begin(), memberBorrowedBooks.end(), book);
    
    if (it != memberBorrowedBooks.end()) {
        memberBorrowedBooks.erase(it);
        book->isBorrowed = false;
        std::cout << "Book returned successfully!" << std::endl;
    } else {
        std::cout << "The book with ID " << bookId << " is not borrowed by member ID " << memberId << std::endl;
    }
}




void displayBooksByMember(int memberId) {
    if (members.size() < static_cast<size_t>(memberId)) {
        std::cout << "Invalid member ID!" << std::endl;
        return;
    }
    
    std::cout << "Books borrowed by Member ID " << memberId << ":" << std::endl;
    for (const auto& book : members[memberId - 1].borrowedBooks) {
        std::cout << "ID: " << book->id << ", Name: " << book->name << ", Author: " << book->author << std::endl;
    }
}

};

int main() {
    Library library;
    bool shouldExit = false;

    std::ifstream myFile; 
    myFile.open("library.csv");

    if (!myFile.is_open()) {
        std::cerr << "Error opening file: library.csv" << std::endl;
        return 1; // Return with an error code
    }

    std::string line;
    while (std::getline(myFile, line)) { // Read each line from the file
        std::cout << line << std::endl; // Print each line to the console
    }

    myFile.close();
     

 int choice;
    int memberId, bookId;
    std::string memberName;
    std::string memberEmail;
std::string memberAddress;

    do {
        std::cout << "\nLibrary Management System\n";
        std::cout << "1. Add Member\n";
        std::cout << "2. Issue Book\n";
        std::cout << "3. Return Book\n";
        std::cout << "4. Display Books by Member\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a valid number.\n";
            std::cin.clear();  // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear input buffer
            continue;  // this skips to next iteration of the loop
        }

        switch (choice) {
      case 1:
    std::cin.ignore();
    std::cout << "Enter Member Name: ";
    std::getline(std::cin, memberName);
    std::cout << "Enter Member Email: ";
    std::getline(std::cin, memberEmail);  
    std::cout << "Enter Member Address: ";
    std::getline(std::cin, memberAddress);  
    library.addMember(memberName, memberEmail, memberAddress);  
    break;

            case 2:
                std::cout << "Enter Book ID to issue: ";
                if (!(std::cin >> bookId)) {
                    std::cout << "Invalid input for Book ID!" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
                std::cout << "Enter Member ID: ";
                if (!(std::cin >> memberId)) {
                    std::cout << "Invalid input for Member ID!" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
                library.issueBook(bookId, memberId);
                break;

       
            case 3: // Return Book
                std::cout << "Enter Book ID to return: ";
                if (!(std::cin >> bookId)) {
                    std::cout << "Invalid input for Book ID. Please try again.\n";
                    std::cin.clear();  // Clear error flags
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear input buffer
                    break;  // Break out of the switch case to re-prompt
                }
                std::cout << "Enter Member ID: ";
                if (!(std::cin >> memberId)) {
                    std::cout << "Invalid input for Member ID. Please try again.\n";
                    std::cin.clear();  // Clear error flags
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear input buffer
                    break;  // Break out of the switch case to re-prompt
                }
                library.returnBook(bookId, memberId);
                break;

            case 4:
                std::cout << "Enter Member ID to display books: ";
                std::cin >> memberId;
                library.displayBooksByMember(memberId);
                break;




    case 5:
                std::cout << "Exiting the program. Goodbye!\n";
                shouldExit = true;  
                break;  // Exit the switch case
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;  // Exit the switch case
        }

    } while (!shouldExit);  // Loop will continue until shouldExit is true

    return 0;  
}
