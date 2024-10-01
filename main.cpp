#include <Windows.h>
#include <iostream>
#include <string>


int main()
{
    std::string input;

    while (input != "exit") {
        std::cout << "Enter a command: ";
        std::getline(std::cin, input);

        if (input == "nvidia-smi") {
            std::cout << "nvidia-smi command detected." << std::endl;
        }
        else if (input == "exit") {
            std::cout << "Program exiting..." << std::endl;
        }
        else {
            std::cout << "Command not found." << std::endl;
        }
    }

    return 0;
}