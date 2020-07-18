# Add stacktrace to every exception

## Overview

exceptions-stacktrace  is a c++17 library which its purpose is to add a stacktrace to exception, even if it was thrown from some external lib you use like stl/boost/any other third party lib, with no code changes to your original code.

A use case for example:

```
#include <vector>
#include <iostream>
#include <string>
int f()
{
	std::vector<int> d;
	d.at(2);
	return 0;
}

int main()
{
	try
	{
		f();
	}
	catch(const std::exception& e)
	{
		std::cout << std::string(e.what());
	}
}
```

In order to get some stacktrace for this code, until now you needed to do something like this:

```
#include <stdexcept>
class MyException : public std::runtime_error
{
MyException():
	std::runtime_error(collect_stacktrace()) {}
};

int f()
{
	std::vector<int> d;
	if(d.size()<2)
	{
		throw MyException();
	}
}
```

or something like that, you may even wrapped the external code usage with a small wrapper (in this example the external code is std::vector), just to get a stacktrace, or a meaningful error message.

**but you don't need it anymore!!!**
You can just use this library.

## **Usage**

```
#include <vector>
#include "AutoSymInitialize.h"
#include "AutoExceptionStacktraceRegister.h"
#include "StackTracePrinter.h"

using namespace ExceptionsStacktrace;
int f()
{
	std::vector<int> d;
	d.at(2);
	return 0;
}

void g()
{
	try
	{
		f();
	}
	catch(const std::exception& e)
	{
		printStacktrace();
	}
}

int main()
{
	AutoSymInitialize autoSymInitialize;
	AutoExceptionStacktraceRegister autoExceptionStacktraceRegister;
	g();
}
```

Result:

![](C:\Users\idowe\Desktop\stacktrace.PNG)

For more examples please view Main.cpp under example dir.

## Installation

- Clone the project
- Add exceptions-stacktrace\exceptions-stacktrace.vcxproj to your visual studio solution.



## **Limitations**

- Works for now only on Windows 
  - Needs some work to think about a way to make it work on lld-link, maybe -wrap flag or LD_PRELOAD for .so files.
- There is some weird issue with rethrow - meaning empty throw. which for not ununderstood able yet reason calls the Veh handler two times, instead of only one - so for now for rethrow we have two stacktraces, and we print them both.
- You need the pdb file of the executable to be in the same directory as the executable in order to work on a computer which the executable wasn't compiled on.
- You need to install dbgHelp.dll in the computer which the executable should run in. preferably via [Debugging Tools For Windows](https://www.microsoft.com/?ref=go).
  - In the future you may only need to add dbghelp.dll to the executable dir.

## Used libs

[backward-cpp](https://github.com/bombela/backward-cpp)

## Testing

Was done with MSVC 2019 and Clang 2019

## Contributing

`exceptions-stacktrace` is developed on GitHub at [exceptions-stacktrace](https://github.com/ykfre/exceptions-stacktrace). Feel free to report an issue or send a pull request, use the [issues-tracker](https://github.com/ykfre/exceptions-stacktrace/issues).