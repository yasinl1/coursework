#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <limits>  // numeric_limits

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
