#include <conio.h>
#include <string>
#include <thread>
#include <chrono>
#include "consoleManager.h"
#include "marqueeConsole.h"
#include "marqueeWorkerThread.h"
#include <iostream>

MarqueeConsole::MarqueeConsole(int pollingRate, MarqueeWorkerThread* worker):
	isRunning (true), pollingRate(pollingRate), workerThread(worker){}


MarqueeConsole::MarqueeConsole()
{
}


MarqueeConsole::~MarqueeConsole()
{
	stop();
}

void MarqueeConsole::input_polling() {
	std::string commandHolder = "";
	char c;

	while (true) {
		
		if (_kbhit()) {
			c = _getch();
			if (c != '\b' && c != '\r') {
				workerThread->typeChar(c);
			}
			else if (c == '\b' && commandHolder.length() != 0) {
				workerThread->backspace();
			}
			else if (c == '\r') {
				workerThread->execute_command();
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / pollingRate));
	}

}



void MarqueeConsole::start()
{
	inputThread = std::thread(&MarqueeConsole::input_polling, this);
	inputThread.join();
}

void MarqueeConsole::stop()
{
	isRunning = false;
	if (inputThread.joinable()) {
		inputThread.join();
	}
}
