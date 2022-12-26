//write a complex calculator console app in c++17 with pretty console interface, has instructions, uses struct for each type of calculations, shows the result in the console in a pretty way, and stores all the operation in json file using rapid.json

#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

struct Calculator
{
    double result;
    std::string operation;
};

Calculator add(double x, double y)
{
    Calculator calc;
    calc.result = x + y;
    calc.operation = "addition";
    return calc;
}

Calculator subtract(double x, double y)
{
    Calculator calc;
    calc.result = x - y;
    calc.operation = "subtraction";
    return calc;
}

Calculator multiply(double x, double y)
{
    Calculator calc;
    calc.result = x * y;
    calc.operation = "multiplication";
    return calc;
}

Calculator divide(double x, double y)
{
    Calculator calc;
    calc.result = x / y;
    calc.operation = "division";
    return calc;
}

void displayMenu()
{
    std::cout << "Calculator Menu" << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << "1. Addition" << std::endl;
    std::cout << "2. Subtraction" << std::endl;
    std::cout << "3. Multiplication" << std::endl;
    std::cout << "4. Division" << std::endl;
    std::cout << "5. Quit" << std::endl;
}

int getMenuChoice()
{
    int choice = 0;
    std::cin >> choice;
    return choice;
}

void performCalculation(int choice, double x, double y)
{
    Calculator result;
    if (choice == 1)
    {
        result = add(x, y);
    }
    else if (choice == 2)
    {
        result = subtract(x, y);
    }
    else if (choice == 3)
    {
        result = multiply(x, y);
    }
    else if (choice == 4)
    {
        result = divide(x, y);
    }

    std::cout << "The result of " << result.operation << " is: " << result.result << std::endl;
}

int main()
{
    std::cout << "Welcome to the calculator app!" << std::endl;

    displayMenu();
    int choice = getMenuChoice();

    while (choice != 5)
    {
        std::cout << "Enter the first number: ";
        double x;
        std::cin >> x;
        std::cout << "Enter the second number: ";
        double y;
        std::cin >> y;

performCalculation(choice, x, y);

displayMenu();
choice = getMenuChoice();
}

rapidjson::Document doc;
doc.SetObject();
rapidjson::Document::AllocatorType& alloc = doc.GetAllocator();
doc.AddMember("addition", add(x, y).result, alloc);
doc.AddMember("subtraction", subtract(x, y).result, alloc);
doc.AddMember("multiplication", multiply(x, y).result, alloc);
doc.AddMember("division", divide(x, y).result, alloc);

rapidjson::StringBuffer buffer;
rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
doc.Accept(writer);

std::cout << "The JSON representation of the results is: " << buffer.GetString() << std::endl;

return 0;
}
