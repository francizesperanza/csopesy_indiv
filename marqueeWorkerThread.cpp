
#include <conio.h>
#include <string>
#include <thread>
#include <chrono>
#include "consoleManager.h"
#include "marqueeWorkerThread.h"
#include "marqueeConsole.h"
#include <iostream>

std::string MarqueeWorkerThread::getCommandHolder() const {
	return commandHolder;
}

void MarqueeWorkerThread::setCommandHolder(const std::string& command) {
	commandHolder = command;
}

void MarqueeWorkerThread::execute_command() {
	if (commandHolder == "test") {
		capture_log("Enter a command in MARQUEE_CONSOLE: " + commandHolder + "\n");
		capture_log("test command detected. \n");
	}
	else {
		capture_log("Enter a command in MARQUEE_CONSOLE: " + commandHolder + "\n");
		capture_log("Command not found. \n");
	}
	commandHolder = "";
	start_y += 2;
}

void MarqueeWorkerThread::capture_log(std::string log)
{
	logs.push_back(log);
}


MarqueeWorkerThread::MarqueeWorkerThread(std::string displayText, int refreshRate, bool isRunning):
	displayText(displayText), refreshRate(refreshRate), isRunning(isRunning){};

void MarqueeWorkerThread::start() {
	workerThread = std::thread(&MarqueeWorkerThread::animate, this);
	workerThread.join();
}

void MarqueeWorkerThread::stop() {
	isRunning = false;
	if (workerThread.joinable()) {
		workerThread.join();
	}
}

MarqueeWorkerThread::~MarqueeWorkerThread() {
	stop();
}

MarqueeWorkerThread::MarqueeWorkerThread(){}

void MarqueeWorkerThread::animate() {
	int sceneWidth = 101;
	int sceneHeight = 20;

	std::string clear = std::string(displayText.length(), ' ');

	COORD current_pos = ConsoleManager::checkXYbounds();

	int start_line = 4;

	int curr_x = 0 + current_pos.X;
	int curr_y = (sceneHeight + current_pos.Y) / 2;


	bool forward = true;
	bool up = true;

	start_y = 21;


	while (true) {

		ConsoleManager::clearScreen();
		ConsoleManager::printHeaderText();
		ConsoleManager::setCursorPosition(curr_x, curr_y);
		std::cout << displayText;

		if (forward) {
			if (up && curr_y != start_line) {
				if (curr_x == sceneWidth - displayText.length()) {
					forward = false;
				}
				else {
					curr_x += 2;
					curr_y -= 2;
				}
			}
			else if (up && curr_y == start_line) {
				up = false;
			}
			else if (!up && curr_y != sceneHeight) {
				if (curr_x == sceneWidth - displayText.length()) {
					forward = false;
				}
				else {
					curr_x += 2;
					curr_y += 2;
				}
			}
			else if (!up && curr_y == sceneHeight) {
				up = true;
			}
		}
		else {
			if (up && curr_y != start_line) {
				if (curr_x == 0) {
					forward = true;
				}
				else {
					curr_x -= 2;
					curr_y -= 2;
				}
			}
			else if (up && curr_y == start_line) {
				up = false;
			}
			else if (!up && curr_y != sceneHeight) {
				if (curr_x == 0) {
					forward = true;
				}
				else {
					curr_x -= 2;
					curr_y += 2;
				}
			}
			else if (!up && curr_y == sceneHeight) {
				up = true;
			}
		}

		ConsoleManager::setCursorPosition(0, 21);
		for (auto log : logs)
			std::cout << log;

		ConsoleManager::setCursorPosition(0, start_y);
		std::cout << "Enter a command in MARQUEE_CONSOLE: ";

		ConsoleManager::setCursorPosition(36, start_y);
		std::cout << commandHolder;
		std::flush(std::cout);

		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / refreshRate));
	}
}

void MarqueeWorkerThread::typeChar( char c )
{
	commandHolder += c;
}

void MarqueeWorkerThread::backspace()
{
	commandHolder.pop_back();
}