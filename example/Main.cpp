#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <vector>
#include <filesystem>
#include "AutoSymInitialize.h"
#include "AutoExceptionStacktraceRegister.h"
#include "StackTracePrinter.h"
#include <iostream>
using namespace ExceptionsStacktrace;

extern int g;
void throw_func()
{
	if (g)
	{
		throw 1;
	}
	throw 4;
}

void test_rethrow()
{
	try
	{
		try
		{
			throw_func();
		}
		catch (int)
		{
			throw;
		}
	}
	catch (int)
	{	
		printStacktrace();
	}

}
void seh()
{
	
		int* a = nullptr;
		*a = 0;
	
}
#pragma optimize( "", off )
void test_seh()
{
	try
	{
		seh();
	}
	catch (...)
	{
		printStacktrace();
	}
}

void trans_func(unsigned int u, EXCEPTION_POINTERS*)
{
	throw 1;
}

#pragma optimize( "", on )
int main(int argc, char** argv)
{
	AutoSymInitialize autoSymInitialize;
	AutoExceptionStacktraceRegister autoExceptionStacktraceRegister;

	test_rethrow();
	_set_se_translator(trans_func);

	test_seh();
	return 0;
}