#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct User {
  std::string name;
  int age;
  std::vector<std::string> interests;
};

int main() {
  std::vector<User> users; // Vector to store multiple user objects

  // Read user data from a JSON file
  std::ifstream user_file("users.json");
  json user_data;
  user_file >> user_data;

  // Iterate over the JSON array and create a User object for each entry
  for (json::const_iterator it = user_data["users"].begin(); it != user_data["users"].end(); ++it) {
    User user;
    user.name = (*it)["name"];
    user.age = (*it)["age"];
    user.interests = (*it)["interests"];
    users.push_back(user);
  }

  // Process the user data (in this case, just add an "s" to each interest)
  for (std::vector<User>::iterator it = users.begin(); it != users.end(); ++it) {
    for (std::vector<std::string>::iterator it2 = (*it).interests.begin(); it2 != (*it).interests.end(); ++it2) {
      (*it2) += "s";
    }
  }

  // Write the processed user data to a new JSON file
  json processed_data;
  processed_data["users"] = users;
  std::ofstream processed_file("processed_users.json");
  processed_file << processed_data;

  return 0;
}
