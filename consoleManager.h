#pragma once
#include <string>
#include <Windows.h>
#include "marqueeWorkerThread.h"
#include "marqueeConsole.h"

class ConsoleManager {
private:
	MarqueeWorkerThread workerThread;
	MarqueeConsole inputThread;


public:
	static ConsoleManager* consoleManager;
	ConsoleManager* getConsoleManager();

	ConsoleManager();
	ConsoleManager(std::string displayText, int refreshRate, int pollingRate);
	static void setCursorPosition(int posX, int posY);
	static COORD checkXYbounds();
	void start();
	static void getCurrentScreenBounds();
	static void clearScreen();
	static void setCursorVisibility();
	static void printHeaderText();
};