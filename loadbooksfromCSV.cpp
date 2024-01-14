#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <limits>  // numeric_limits
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
