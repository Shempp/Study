#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <sstream>
#include <iomanip>
#include <atomic>

#include "RenderQueue.h"
#include "Render.h"

std::atomic<bool> terminated;

#ifdef _WIN32
BOOL WINAPI consoleHandler(DWORD fdwCtrlType) {
	// There may be a little delay on reading sides
	// We can use std::stop_token for C++ 20 here
	terminated.store(true, std::memory_order_relaxed);

	switch (fdwCtrlType)
	{
	case CTRL_C_EVENT:
		return TRUE;
	case CTRL_CLOSE_EVENT:
		return TRUE;
	case CTRL_BREAK_EVENT:
		return FALSE;
	case CTRL_LOGOFF_EVENT:
		return FALSE;
	case CTRL_SHUTDOWN_EVENT:
		return FALSE;
	default:
		return FALSE;
	}
}
#endif

eRqCommand getRandomCommand() {
	static std::vector<eRqCommand> COMMANDS{ eRqCommand::CONSOLE_OUTPUT, eRqCommand::BEEP };
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<size_t> dist(0, COMMANDS.size() - 1);
	return static_cast<eRqCommand>(COMMANDS[dist(rng)]);
}

std::string getTime() {
	using namespace std::chrono;
	const auto currentTimePoint{ system_clock::now() };
	const auto currentTime{ system_clock::to_time_t(currentTimePoint) };
	const auto currentLocalTime{ *std::localtime(&currentTime) };
	const auto currentTimeSinceEpoch{ currentTimePoint.time_since_epoch() };
	const auto currentMilliseconds{ duration_cast<milliseconds> (currentTimeSinceEpoch).count() % 1000 };

	std::ostringstream stream;
	stream << std::put_time(&currentLocalTime, "%T") << "." << std::setw(3) << std::setfill('0') << currentMilliseconds;
	return stream.str();
}

void renderThread(CRenderQueue<SRenderEntity>& queue) {
	while (!terminated.load(std::memory_order_relaxed)) {
		SRenderEntity renderEntity; 
		if (queue.PopCommand(renderEntity)) {
			switch (renderEntity.cmd) {
			case eRqCommand::CONSOLE_OUTPUT:
				std::cout << "Producing time: " << renderEntity.consoleOutput << "\t Consuming time: " << getTime() << std::endl;
				break;
			case eRqCommand::BEEP:
#ifdef _WIN32
				Beep(50, renderEntity.beepDuration);
#endif
				break;
			}
		}
	}
}

int main()
{
#ifdef _WIN32
	// For gracefull shutdown with 'CTRL + C'
	if (!SetConsoleCtrlHandler(consoleHandler, TRUE)) {
		std::cerr << "SetConsoleCtrlHandler failed with error: " << GetLastError() << std::endl;
		return EXIT_FAILURE;
	}
#endif
	CRenderQueue<SRenderEntity> queue(5000);

	std::thread th(renderThread, std::ref(queue));

	while (!terminated.load(std::memory_order_relaxed)) {
		// Some work
		std::this_thread::sleep_for(std::chrono::milliseconds(50));

		auto cmd = getRandomCommand();
		switch (cmd) {
		case eRqCommand::CONSOLE_OUTPUT:
			while (!queue.AddCommand({ cmd, getTime() }) && !terminated.load(std::memory_order_relaxed));
			break;
		case eRqCommand::BEEP:
			// Note: beepDuration slows down the consumer's thread (blocking API call)
			while (!queue.AddCommand({ cmd, "", 50 }) && !terminated.load(std::memory_order_relaxed));
			break;
		default:
			continue;
		}
	}

	if (th.joinable()) {
		th.join();
	}

	return 0;
}
