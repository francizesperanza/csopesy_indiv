#pragma once
#include "consoleManager.h"
#include "marqueeWorkerThread.h"
#include <string>
#include <conio.h>
#include <vector>
#include <thread>
#include <atomic>

class MarqueeWorkerThread;

class MarqueeConsole {
private:
	int pollingRate;
	std::thread inputThread;
	bool isRunning;
	MarqueeWorkerThread* workerThread;

public:
	MarqueeConsole(int pollingRate, MarqueeWorkerThread* worker);
	MarqueeConsole();
	~MarqueeConsole();
	void input_polling();
	void start();
	void stop();
};