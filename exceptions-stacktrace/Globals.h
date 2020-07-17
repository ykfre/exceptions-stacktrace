#pragma once
#include <Windows.h>
#include <vector>
#include <optional>

namespace ExceptionsStacktrace
{
	inline thread_local std::vector<std::vector<void*>> t_currentExceptionStacktraces;

	inline void clearCollectedExceptionsInfo()
	{
		t_currentExceptionStacktraces.clear();
	}
}