//write a program that PROCESSING the data initialized by the user in the json files and stores all the oparation in the json format in history.json using rabbit json, uses struct, and is doing some operation with user data, calculating the age from the birth day to now, showing the result in a pretty way in the console and if its corret store the result in the json file
#include <iostream>
#include <fstream>
#include <string>
#include <ctime> // for time() and localtime()
#include <rabbit/rabbit.h> // for RabbitJSON

// Struct to hold user data
struct UserData
{
  std::string name;
  std::string birth_date; // in the format "YYYY-MM-DD"
};

// Function to calculate age from birth date
int calculateAge(const std::string& birth_date)
{
  // Parse the birth date to extract the year, month, and day
  int year = std::stoi(birth_date.substr(0, 4));
  int month = std::stoi(birth_date.substr(5, 2));
  int day = std::stoi(birth_date.substr(8, 2));

  // Get the current time
  time_t current_time = time(0);
  tm* now = localtime(&current_time);

  // Calculate the age
  int age = now->tm_year + 1900 - year;
  if (now->tm_mon < month || (now->tm_mon == month && now->tm_mday < day))
  {
    // If the current month and day is before the birth month and day, subtract 1 from the age
    age--;
  }

  return age;
}

int main()
{
  // Open the input file
  std::ifstream input_file("user_data.json");
  if (!input_file)
  {
    std::cerr << "Error: unable to open user_data.json" << std::endl;
    return 1;
  }

  // Read the user data from the input file
  UserData user_data;
  input_file >> user_data.name >> user_data.birth_date;

  // Calculate the age
  int age = calculateAge(user_data.birth_date);

  // Print the user data and calculated age in a pretty format
  rabbit::object result;
  result["name"] = user_data.name;
  result["birth_date"] = user_data.birth_date;
  result["age"] = age;
  std::cout << rabbit::json(result) << std::endl;

  // Prompt the user to confirm the results
  std::cout << "Is the above information correct? (y/n) ";
  std::string response;
  std::cin >> response;

  if (response == "y")
  {
    // Open the history file
    std::ofstream history_file("history.json");
    if (!history_file)
    {
      std::cerr << "Error: unable to open history.json" << std::endl;
      return 1;
    }

    // Write the user data and calculated age to the history file in JSON format
    history_file << rabbit::json(result) << std::endl;
  }

  return 0;
}
