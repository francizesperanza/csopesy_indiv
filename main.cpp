#include <Windows.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "consoleManager.h"
#include "marqueeConsole.h"


static constexpr int REFRESH_RATE = 60;
static constexpr int POLLING_RATE = 100;


std::vector <std::string> logs;


void capture_log(std::string log)
{
	logs.push_back(log);
}


void execute_command(std::string command) {
	if (command == "test") {
		capture_log("Enter a command in MARQUEE_CONSOLE: " + command + "\n");
		capture_log("test command detected. \n");
	}
	else {
		capture_log("Enter a command in MARQUEE_CONSOLE: " + command + "\n");
		capture_log("Command not found. \n");
	}
}

int main()
{
    // THREADED
    ConsoleManager consoleManager("Hello world in marquee!", REFRESH_RATE, POLLING_RATE);
    consoleManager.setCursorVisibility();

    consoleManager.start();

    // NON-THREADED
	//ConsoleManager::setCursorVisibility();
	//std::string commandHolder = "";
	//char c;
	//int start_y = 21;

 //   std::string displayText = "Hello world in marquee!";

 //   int sceneWidth = 101;
 //   int sceneHeight = 20;

 //   std::string clear = std::string(displayText.length(), ' ');

 //   COORD current_pos = ConsoleManager::checkXYbounds();

 //   int start_line = 4;

 //   int curr_x = 0 + current_pos.X;
 //   int curr_y = (sceneHeight + current_pos.Y) / 2;


 //   bool forward = true;
 //   bool up = true;

 //   while (true) {
	//	ConsoleManager::clearScreen();
	//	ConsoleManager::printHeaderText();
	//	ConsoleManager::setCursorPosition(curr_x, curr_y);
	//	std::cout << displayText;

	//	if (forward) {
	//		if (up && curr_y != start_line) {
	//			if (curr_x == sceneWidth - displayText.length()) {
	//				forward = false;
	//			}
	//			else {
	//				curr_x += 2;
	//				curr_y -= 2;
	//			}
	//		}
	//		else if (up && curr_y == start_line) {
	//			up = false;
	//		}
	//		else if (!up && curr_y != sceneHeight) {
	//			if (curr_x == sceneWidth - displayText.length()) {
	//				forward = false;
	//			}
	//			else {
	//				curr_x += 2;
	//				curr_y += 2;
	//			}
	//		}
	//		else if (!up && curr_y == sceneHeight) {
	//			up = true;
	//		}
	//	}
	//	else {
	//		if (up && curr_y != start_line) {
	//			if (curr_x == 0) {
	//				forward = true;
	//			}
	//			else {
	//				curr_x -= 2;
	//				curr_y -= 2;
	//			}
	//		}
	//		else if (up && curr_y == start_line) {
	//			up = false;
	//		}
	//		else if (!up && curr_y != sceneHeight) {
	//			if (curr_x == 0) {
	//				forward = true;
	//			}
	//			else {
	//				curr_x -= 2;
	//				curr_y += 2;
	//			}
	//		}
	//		else if (!up && curr_y == sceneHeight) {
	//			up = true;
	//		}
	//	}

	//	//std::this_thread::sleep_for(std::chrono::milliseconds(1000 / REFRESH_RATE));

	//	ConsoleManager::setCursorPosition(0, 21);
	//	for (auto log : logs)
	//		std::cout << log;

	//	ConsoleManager::setCursorPosition(0, start_y);
	//	std::cout << "Enter a command in MARQUEE_CONSOLE: ";

	//	ConsoleManager::setCursorPosition(36, start_y);
	//	std::cout << commandHolder;
	//	std::flush(std::cout);
	//	ConsoleManager::setCursorPosition(0, 0);
	//	if (_kbhit()) {
	//		c = _getch();
	//		if (c != '\b' && c != '\r') {
	//			commandHolder += c;
	//		}
	//		else if (c == '\b' && commandHolder.length() != 0) {
	//			commandHolder.pop_back();
	//		}
	//		else if (c == '\r') {
	//			execute_command(commandHolder);
	//			commandHolder = "";
	//			start_y += 2;
	//		}
	//	}
	//	ConsoleManager::setCursorPosition(0, 0);

	//	std::this_thread::sleep_for(std::chrono::milliseconds(1000 / POLLING_RATE));
    //}

    return 0;
}