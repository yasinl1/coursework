#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <limits>  // numeric_limits

// Method to return a borrowed book
void returnBook(int bookId, int memberId) {
  // Find the book by its ID using the findBookById method
    Book* book = findBookById(bookId);

     // Check if the book with the given ID exists
    if (!book) {
        std::cout << "Invalid book ID!" << std::endl;  // Display error message if book not found
        return;  // Return without further processing
    }
    
// Check if the member ID is valid
    if (memberId <= 0 || memberId > static_cast<int>(members.size())) {
      std::cout << "Invalid member ID!" << std::endl; //display message if member id nit found
        return;  // Return without further processing

   }

 // Check if the book is currently borrowed

    if (!book->isBorrowed) {
        std::cout << "Book is not borrowed!" << std::endl;// Display error message if book is not borrowed
        return;  // Return without further processing
    }
// Calculate the fine, if applicable, based on the due date of the book    

    time_t now = time(0);//get current time in seconds
    double diff = difftime(now, book->dueDate);
    if (diff > 0) {
      int fine = static_cast<int>(diff / (24 * 60 * 60)); //calculate number days overdue 
      std::cout << "Fine to be paid: £" << fine << std::endl; //fine amount
    }
// Find the book in the member's list of borrowed books
    // Find the book in the member's list of borrowed books
    std::vector<Book*>& memberBorrowedBooks = members[memberId - 1].borrowedBooks;
    auto it = std::find(memberBorrowedBooks.begin(), memberBorrowedBooks.end(), book);

   // If the book is found in the member's list of borrowed books, return the book
    
    if (it != memberBorrowedBooks.end()) {
        memberBorrowedBooks.erase(it);
        book->isBorrowed = false;
        std::cout << "Book returned successfully!" << std::endl;
    } else {
     // If the book is not found in the member's list of borrowed books, display an error message
        std::cout << "The book with ID " << bookId << " is not borrowed by member ID " << memberId << std::endl;
    }
}
