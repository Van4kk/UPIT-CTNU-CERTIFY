//write a complex calculator console app in c++11 with pretty console interface, have instructions, uses struct for each type of calculations, shows the result in the console in a pretty way, and stores all the operation in json file

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Struct for storing calculation history
struct Calculation {
  std::string operation;
  std::vector<double> parameters;
  double result;
};

// Struct for storing different types of calculations
struct Calculator {
  std::vector<Calculation> addition_history;
  std::vector<Calculation> subtraction_history;
  std::vector<Calculation> multiplication_history;
  std::vector<Calculation> division_history;
};

// Function prototypes
void print_instructions();
bool is_valid_operation(const std::string& op);
double calculate(const std::string& op, const std::vector<double>& params);
void print_result(double result);
void write_to_file(const Calculator& calc);

int main() {
  // Print instructions
  print_instructions();

  // Create a Calculator object to store calculation history
  Calculator calc;

  // Read and process input from the user
  std::string operation;
  std::vector<double> parameters;
  double x;
  while (std::cin >> operation) {
    // Check if the operation is valid
    if (!is_valid_operation(operation)) {
      std::cout << "Invalid operation. Please try again." << std::endl;
      continue;
    }

    // Read the parameters for the operation
    parameters.clear();
    while (std::cin >> x) {
      parameters.push_back(x);
    }

    // Calculate the result of the operation
    double result = calculate(operation, parameters);

    // Print the result in a pretty way
    print_result(result);

    // Store the calculation in the appropriate history vector
    Calculation calc_data;
    calc_data.operation = operation;
    calc_data.parameters = parameters;
    calc_data.result = result;
    if (operation == "+") {
      calc.addition_history.push_back(calc_data);
    }
else if (operation == "-") {
  calc.subtraction_history.push_back(calc_data);
} else if (operation == "*") {
  calc.multiplication_history.push_back(calc_data);
} else if (operation == "/") {
  calc.division_history.push_back(calc_data);
}

// Write the calculation history to a JSON file
write_to_file(calc);

return 0;
}

// Function definitions
void print_instructions() {
  std::cout << "Welcome to the calculator app!" << std::endl;
  std::cout << "To perform a calculation, enter the operation followed by the parameters." << std::endl;
  std::cout << "Supported operations: +, -, *, /" << std::endl;
  std::cout << "For example: + 3 4" << std::endl;
  std::cout << "Enter 'q' to quit the program." << std::endl;
}

bool is_valid_operation(const std::string& op) {
  // Check if the operation is one of the supported operations
  return (op == "+" || op == "-" || op == "*" || op == "/");
}

double calculate(const std::string& op, const std::vector<double>& params) {
  // Check if there are at least two parameters for the operation
  if (params.size() < 2) {
    std::cout << "Not enough parameters for the operation. Please try again." << std::endl;
    return 0;
  }

  // Perform the calculation based on the operation
  double result = params[0];
  for (int i = 1; i < params.size(); i++) {
    if (op == "+") {
      result += params[i];
    } else if (op == "-") {
      result -= params[i];
    } else if (op == "*") {
      result *= params[i];
    } else if (op == "/") {
      // Check for division by zero
      if (params[i] == 0) {
        std::cout << "Division by zero. Please try again." << std::endl;
        return 0;
	}
