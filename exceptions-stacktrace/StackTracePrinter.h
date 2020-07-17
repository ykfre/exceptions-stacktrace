#pragma once

namespace ExceptionsStacktrace
{
	void printStacktrace();

	void printStacktrace(const std::vector<void*> addresses);
}
