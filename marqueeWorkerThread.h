#pragma once
#include <string>
#include <thread>
#include "consoleManager.h"
#include "marqueeWorkerThread.h"
#include "marqueeConsole.h"

class ConsoleManager;

class MarqueeWorkerThread {
private:
	std::string displayText;
	int refreshRate;
	std::thread workerThread;
	std::vector <std::string> logs;
	bool isRunning;
	std::string commandHolder;
	int start_y;

public:

	MarqueeWorkerThread(std::string displayText, int refreshRate, bool isRunning);
	~MarqueeWorkerThread();
	MarqueeWorkerThread();

	void start();
	void stop();
	void animate();
	void typeChar( char c );
	void backspace();
	void execute_command();
	void capture_log(std::string log);
	std::string getCommandHolder() const;
	void setCommandHolder(const std::string& command);
};