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
