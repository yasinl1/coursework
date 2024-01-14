#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <limits>  // numeric_limits

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
