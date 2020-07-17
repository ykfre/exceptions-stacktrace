#pragma warning(push, 0)
#include "backward.h"
#pragma warning(pop)

#include "StackTracePrinter.h"
#include "Globals.h"

using namespace backward;

namespace ExceptionsStacktrace
{
	std::mutex g_stackTracePrinter;

	void printStacktrace()
	{
		for (const auto& stacktrace : t_currentExceptionStacktraces)
		{
			printStacktrace(stacktrace);
		}
		clearCollectedExceptionsInfo();
	}

	void printStacktrace(const std::vector<void*> addresses)
	{
		StackTrace st;
		st.load_from(addresses);
		std::scoped_lock<std::mutex> scoped_lock(g_stackTracePrinter);
		TraceResolver tr;
		tr.load_stacktrace(st);
		std::cout << "stacktrace is" << std::endl;
		for (size_t i = 0; i < st.size(); ++i) {
			auto trace = tr.resolve(st[i]);
			if (trace.has_value())
			{
				std::cout << "#" << i
					<< " " << trace->object_filename
					<< " " << trace->object_function
					<< " line: " << trace->source.line
					<< " [" << trace->addr << "]"
					<< std::endl;
			}
			else
			{
				std::cout << "#" << i << " " << st[i].addr << std::endl;
			}
		}
	}
}