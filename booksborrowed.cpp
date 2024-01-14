#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <limits>  // numeric_limits

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
