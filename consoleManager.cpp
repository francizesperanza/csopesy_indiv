#include "consoleManager.h"
#include "marqueeWorkerThread.h"
#include "marqueeConsole.h"
#include <Windows.h>
#include <iostream>
#include <thread>
#include <string>
#include <chrono>


ConsoleManager* ConsoleManager::consoleManager = nullptr;

ConsoleManager* ConsoleManager::getConsoleManager() {
	return consoleManager;
}

ConsoleManager::ConsoleManager()
{
}

ConsoleManager::ConsoleManager(std::string displayText, int refreshRate, int pollingRate):
	workerThread(displayText, refreshRate, true), inputThread(pollingRate, &workerThread){
}


void ConsoleManager::setCursorPosition(int posX, int posY) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = posX;
	pos.Y = posY;
	SetConsoleCursorPosition(hConsole, pos);
}

void ConsoleManager::start() {
	std::thread inputThread(&MarqueeConsole::input_polling, &inputThread);
	std::thread workerThread(&MarqueeWorkerThread::animate, &workerThread);

	inputThread.join();
	workerThread.join();
}

void ConsoleManager::printHeaderText() {
	setCursorPosition(0, 0);
	std::cout << "**********************************************" << std::endl;
	std::cout << "* Displaying a marquee console! *" << std::endl;
	std::cout << "**********************************************" << std::endl;
}

void ConsoleManager::clearScreen() {
	std::system("cls");
}

void ConsoleManager::setCursorVisibility() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(consoleHandle, &info);
	info.bVisible = false;
	SetConsoleCursorInfo(consoleHandle, &info);
}

COORD ConsoleManager::checkXYbounds() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD loc;

	GetConsoleScreenBufferInfo(hConsole, &csbi);

	loc.X = csbi.dwCursorPosition.X;
	loc.Y = csbi.dwCursorPosition.Y;
	return loc;
};

void ConsoleManager::getCurrentScreenBounds() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	int width, height;

	width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	std::cout << "Width: " << width << std::endl;
	std::cout << "Height: " << height << std::endl;
}