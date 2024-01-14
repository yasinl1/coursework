#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <limits>  // numeric_limits

//structure to represent book
struct Book {
    int id;
  std::string name; //book name
  std::string author; //author name
    std::string type;  // e.g., "Science Fiction", "Satire", etc.
  int pageCount; // number of pages
    bool isBorrowed = false;
  time_t dueDate; //due date set for 3 days later after  borrowing
};

//structure to represnt member id
struct Member {
  std::string name; //member name
  std::string email; //member email
  std::string address; //member address
  std::vector<Book*> borrowedBooks; //books members have borrowed
};
//library class to mange books and members
class Library {
private:
  std::vector<Book> books; //list of books
  std::vector<Member> members; //list of members registered with library

  //method to find book by id
public:
    Book* findBookById(int id) {
        for (auto& book : books) {
            if (book.id == id) {
                return &book;
            }
        }
        return nullptr;  // Return nullptr if book not found
    }

  //method to add member to library
  void addMember(const std::string& name, const std::string& email, const std::string& address) {
    static int memberIdCounter = 1;
    Member newMember = {name, email, address};
    // add new member to members vector
    members.push_back(newMember);
    // Display a success message indicating that the member has been added
    std::cout << "Member added successfully with ID: " << memberIdCounter << std::endl;
    memberIdCounter++;
}

  //method to load books from csv file into library system
void loadBooksFromCSV(const std::string& filename) {
  //open csv file
    std::ifstream file(filename);
    //check if csv file opened successfully
    if (!file.is_open()) {
      std::cerr << "Error opening file: " << filename << std::endl; //display error messageif unsuccessful read of csv file
        return;
    }

    std::string line; // String to store each line read from the file
    // Read each line from the CSV file until the end of the file is reached
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        Book book;

    // Extract and store the ID of the book
        std::getline(ss, token, ',');  // id
        token.erase(std::remove_if(token.begin(), token.end(), ::isspace), token.end());  
        book.id = std::stoi(token);
// Extract and store the name, author, and type of the book
        std::getline(ss, book.name, ',');
        std::getline(ss, book.author, ',');
        std::getline(ss, book.type, ',');
// Extract and store the page count of the book
        std::getline(ss, token);  // page count
        book.pageCount = std::stoi(token);

        books.push_back(book);  
    }

    file.close();

 // Display a success message indicating that the books have been loaded from the CSV file
    std::cout << "Books loaded successfully from CSV!" << std::endl;
}
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

  
// Method to display books borrowed by a specific member
void displayBooksByMember(int memberId) {
// Check if the provided memberId is valid
    if (members.size() < static_cast<size_t>(memberId)) {
        std::cout << "Invalid member ID!" << std::endl;// Display error message if member ID is invalid
        return;
    }
    
    std::cout << "Books borrowed by Member ID " << memberId << ":" << std::endl;
// Iterate through the borrowedBooks vector of the specified member and display details of each book
    for (const auto& book : members[memberId - 1].borrowedBooks) {
        std::cout << "ID: " << book->id << ", Name: " << book->name << ", Author: " << book->author << std::endl;
    }
}

};

int main() {
    Library library;
    bool shouldExit = false;

    //open the library.csv file to read the information
    std::ifstream myFile; 
    myFile.open("library.csv");

    //check if the csv file is open
    if (!myFile.is_open()) {
      std::cerr << "Error opening file: library.csv" << std::endl; //print errror message if not able to open csv file
        return 1; // Return with an error code
    }

    //print each line from csv file and print it to the console
    std::string line;
    while (std::getline(myFile, line)) { // Read each line from the file
        std::cout << line << std::endl; // Print each line to the console
    }

    //close file after readin its content
    myFile.close();
     

    int choice; //variable to store users meanu choice
    int memberId, bookId; //variable to store member and book id   
    std::string memberName;
    std::string memberEmail;
    std::string memberAddress; //variable to store member details

    //this displays main menu and handles user input
        do {
	  //Displays menu option to user
	  
        std::cout << "\nLibrary Management System\n";
        std::cout << "1. Add Member\n";
        std::cout << "2. Issue Book\n";
        std::cout << "3. Return Book\n";
        std::cout << "4. Display Books Borrowed by Member\n";
        std::cout << "5. Exit Library\n";
        std::cout << "Enter your choice: ";

	//get user choice and validates it
	
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a valid number.\n";
            std::cin.clear();  // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear input buffer
            continue;  // this skips to next iteration of the loop
        }
       
	//handle user choice using a switch statement
        switch (choice) {
	  //add a new member to the library	  
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

    //case 2 issues book
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
                break; //Breal out of the switch case to re=prompt

		
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
                break; //break out of the switch case to re-prompt

		//case 4 display books by member 	
	    
            case 4:
                std::cout << "Enter Member ID to display books borrowed: ";
                std::cin >> memberId;
                library.displayBooksByMember(memberId);
                break; 



		//case 5 to exit library mangement system
		
		    case 5:
                std::cout << "Exiting the program. Goodbye!\n";
                shouldExit = true;  
                break;  // Exit the switch case
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;  // Exit the switch case
        }

    } while (!shouldExit);  // Loop will continue until shouldExit is true

	return 0; //indicates successful excutution  
}
