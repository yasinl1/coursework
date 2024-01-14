// Library.cpp
#include "Library.h"

Book* Library::findBookById(int id) {
    for (auto& book : books) {
        if (book.id == id) {
            return &book;
        }
    }
    return nullptr;
}

// Method to add a member to the library
void Library::addMember(const std::string& name, const std::string& email, const std::string& address) {
    static int memberIdCounter = 1;
    Member newMember = {name, email, address};
    members.push_back(newMember);
    std::cout << "Member added successfully with ID: " << memberIdCounter << std::endl;
    memberIdCounter++;
}

// Method to load books from a CSV file into the library system
void Library::loadBooksFromCSV(const std::string& filename) {
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

        std::getline(ss, token, ',');
        token.erase(std::remove_if(token.begin(), token.end(), ::isspace), token.end());
        book.id = std::stoi(token);

        std::getline(ss, book.name, ',');
        std::getline(ss, book.author, ',');
        std::getline(ss, book.type, ',');
        
        std::getline(ss, token);
        book.pageCount = std::stoi(token);

        books.push_back(book);
    }

    file.close();
    std::cout << "Books loaded successfully from CSV!" << std::endl;
}

// Method to issue a book to a member
void Library::issueBook(int bookId, int memberId) {
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
    book->dueDate = now + 3 * 24 * 60 * 60;
    members[memberId - 1].borrowedBooks.push_back(book);
    std::cout << "Book issued successfully!" << std::endl;
}

// Method to return a borrowed book
void Library::returnBook(int bookId, int memberId) {
    Book* book = findBookById(bookId);
    if (!book) {
        std::cout << "Invalid book ID!" << std::endl;
        return;
    }

    if (memberId <= 0 || memberId > static_cast<int>(members.size())) {
        std::cout << "Invalid member ID!" << std::endl;
        return;
    }

    if (!book->isBorrowed) {
        std::cout << "Book is not borrowed!" << std::endl;
        return;
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

// Method to display books borrowed by a specific member
void Library::displayBooksByMember(int memberId) {
    if (members.size() < static_cast<size_t>(memberId)) {
        std::cout << "Invalid member ID!" << std::endl;
        return;
    }

    std::cout << "Books borrowed by Member ID " << memberId << ":" << std::endl;
    for (const auto& book : members[memberId - 1].borrowedBooks) {
        std::cout << "ID: " << book->id << ", Name: " << book->name << ", Author: " << book->author << std::endl;
    }
}
