#pragma once
#include <string>

namespace ExceptionsStacktrace
{
	class AutoSymInitialize
	{
	public:
		AutoSymInitialize();
		~AutoSymInitialize();
		AutoSymInitialize(const AutoSymInitialize&) = delete;
		AutoSymInitialize& operator=(const AutoSymInitialize&) = delete;
		AutoSymInitialize(AutoSymInitialize&& other) noexcept = delete;
		AutoSymInitialize& operator=(AutoSymInitialize&& other) noexcept = delete;
	private:

		static std::wstring getExePath();
	};
}

