#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <limits>  // numeric_limits

// Method to issue a book to a member
    void issueBook(int bookId, int memberId) {
// Find the book by its ID using the findBookById method
        Book* book = findBookById(bookId);
// Check if the book with the given ID exists
        if (!book) {
	  std::cout << "Invalid book ID!" << std::endl; //display error message of book not found
            return;
        }
// Check if the member ID is valid
        if (members.size() < memberId) {
	  std::cout << "Invalid member ID!" << std::endl; //display error message if invalid id
            return;
        }
 // Check if the book is already borrowed by someone
        if (book->isBorrowed) {
	  std::cout << "Book is already borrowed!" << std::endl; //display error message if already borrowed
            return;
        }
// If all checks pass, set the book as borrowed and update its due date
        book->isBorrowed = true; // Set the book's borrowed status to true
        time_t now = time(0);
        book->dueDate = now + 3 * 24 * 60 * 60; // 3 days from now
        members[memberId - 1].borrowedBooks.push_back(book); // Get the current time in seconds

	// success message book borrowed
        std::cout << "Book issued successfully!" << std::endl;
    }
