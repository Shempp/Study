#pragma once

#include <cstdint>
#include <string>

enum class eRqCommand {
	UNKNOWN,
	CONSOLE_OUTPUT,
	BEEP
};

struct SRenderEntity {
	eRqCommand cmd = eRqCommand::UNKNOWN;
	std::string consoleOutput;
	std::uint32_t beepDuration = 0;
};
