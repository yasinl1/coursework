#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <limits>  // numeric_limits

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
