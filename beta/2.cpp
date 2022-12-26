//C++11 program that implements a more complex calculator app with a console interface, instructions, a struct for operations, and a file for storing operations:

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>

// Struct for storing calculation history
struct Calculation {
  std::string operation;
  std::vector<double> parameters;
  double result;
};

// Function prototypes
void print_instructions();
bool is_valid_operation(const std::string& op);
double calculate(const std::string& op, const std::vector<double>& params);
void print_result(double result);
void write_to_file(const Calculation& calc, std::ofstream& out);

int main() {
  // Print instructions
  print_instructions();

  // Open a file for storing calculation history
  std::ofstream history_file("calculation_history.txt");

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

    // Create a Calculation object and write it to the history file
    Calculation calc;
    calc.operation = operation;
    calc.parameters = parameters;
    calc.result = result;
    write_to_file(calc, history_file);
  }

  // Close the history file
  history_file.close();

  return 0;
}

// Function definitions
void print_instructions() {
  std::cout << "Welcome to the calculator app!" << std::endl;
  std::cout << "To perform a calculation, enter the operation followed by the parameters." << std::endl;
  std::cout << "Supported operations: +, -, *, /" << std::endl;
  std::cout << "For example: + 3 4" << std::endl;
  std::cout << "Enter 'q' to quit the program." << std::endl
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
      result /= params[i];
    }
  }
  return result;
}

void print_result(double result) {
  // Print the result with a fixed number of decimal places
  std::cout << "Result: " << std::fixed << std::setprecision(2) << result << std::endl;
}

void write_to_file(const Calculation& calc, std::ofstream& out) {
  // Write the calculation to the file in the format:
  // operation x y z ... result
  out << calc.operation;
  for (int i = 0; i < calc.parameters.size(); i++) {
    out << " " << calc.parameters[i];
  }
  out << " " << calc.result << std::endl;
}
