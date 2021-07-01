#pragma once

template <typename Ch>
bool isSpace(Ch& symbol)
{
	return std::isspace(static_cast<unsigned char>(symbol));
}

template <typename Str>
void trimAll(Str& str)
{
	// Trim leading spaces
	auto it = str.begin();
	for (; it != str.end(); ++it) {
		if (!isSpace(*it)) {
			break;
		}
	}
	str.erase(str.begin(), it);

	// Trim trailing spaces
	it = str.end();
	for (; it != str.begin();) {
		if (!isSpace(*(--it))) {
			++it;
			break;
		}
	}
	str.erase(it, str.end());

	// Trim inner spaces
	for (it = str.begin(); it != str.end();) {
		if (isSpace(*it)) {
			auto itBeginRange = it;
			bool moreThanOne = false;
			while (isSpace(*(++it))) {
				moreThanOne = true;
			}

			if (moreThanOne) {
				it = str.erase(itBeginRange, it - 1);
			}
		}
		else {
			++it;
		}
	}
}