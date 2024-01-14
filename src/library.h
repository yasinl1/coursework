// Library.h
#ifndef LIBRARY_H
#define LIBRARY_H

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
  Book* findBookById(int id);

  public:
    void addMember(const std::string& name, const std::string& email, const std::string& address);
    void loadBooksFromCSV(const std::string& filename);
    void issueBook(int bookId, int memberId);
    void returnBook(int bookId, int memberId);
    void displayBooksByMember(int memberId);
};

    #endif
