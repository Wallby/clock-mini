#include <clock_mini.h>
#include <test_mini.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#if defined(_WIN32)
#include <windows.h>
#else //< #elif defined(__linux__)
#include <unistd.h>
#endif

// tested on windows and accuracy of Sleep is most often within..
// .. 20milliseconds
// v
#define EPSILON_IN_MILLISECONDS 20.0


void clear_line(FILE* a, int lineLength)
{
	fputs("\r", a);
	for(int i = 0; i < lineLength; ++i)
	{
		fputs(" ", a); //< clear line to spaces
	}
}
void flush_line(FILE* a)
{
	int b = fgetc(a);
	while((b != '\n') & (b != EOF))
	{
		b = fgetc(a);
	}
}

int test_1()
{
	double a = cm_get_milliseconds();
#if defined(_WIN32)
	Sleep(1000);
#else //< #elif defined(__linux__)
	sleep(1);
#endif
	double b = cm_get_milliseconds();
	double deltatime = b - a;
	double c = fabs(deltatime - 1000.0);
	if(c > EPSILON_IN_MILLISECONDS)
	{
		printf("error: fabs(deltatime - 1000.0) > %f (fabs(deltatime - 1000.0) == %f)\n", EPSILON_IN_MILLISECONDS, c);
		return 0;
	}
	
	// indicate progress as each repetition of this test takes atleast 1second
	printf("fabs(deltatime - 1000) was %f which is within margin %f\n", c, EPSILON_IN_MILLISECONDS);

	return 1;
}

int test_2()
{
	int timerDurationInSeconds = 5;

	// TODO: maybe use VT100 instead of clearing line by remembering cursor position?
	/*
#ifdef _WIN32
	// https://learn.microsoft.com/en-us/windows/console/clearing-the-screen#example-1
	// https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
	struct
	{
		HANDLE a;
	} stdoutputhandle = GetStdHandle(STD_OUTPUT_HANDLE);

	DWORD consolemode;
	if(GetConsoleMode(stdoutputhandle.a, &consolemode) == FALSE)
	{
		int a;
		getlasterror_to_string(&a, 0);
		char b[a];
		getlasterror_to_string(&a, b);

		fprintf(stderr, "error: %s\n", b);
		return 0;
	}

	DWORD newConsolemode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	if(SetConsoleMode(stdoutputhandle.a, &newConsolemode) == FALSE)
	{
		int a;
		getlasterror_to_string(&a, 0);
		char b[a];
		getlasterror_to_string(&a, b);

		fprintf(stderr, "error: %s\n", b);
		return 0;
	}

	// and below..
	//if(SetConsoleMode(stdoutputhandle.a, consolemode) == FALSE)
	//{
	//  //...
	//}
#endif
	*/

	printf("Starting timer for %i seconds\n", timerDurationInSeconds);
	double a = cm_get_seconds();
	double b = a;
	int stdoutLineLength = 0;
	while(1)
	{
		double deltatime = b - a;
		if((int)deltatime >= timerDurationInSeconds)
		{
			break;
		}

		clear_line(stdout, stdoutLineLength);
		stdoutLineLength = printf("Time %f", deltatime);

		b = cm_get_seconds();
	}
	clear_line(stdout, stdoutLineLength);
	printf("Time %f\n", (float)timerDurationInSeconds);

	fputs("Did the time advance at a correct-looking speed? y/n: ", stdout);
	while(1)
	{
		char a = fgetc(stdin); //< will add \n automatically
		flush_line(stdin);
		if(a == 'n')
		{
			return 0;
		}
		if(a == 'y')
		{
			break;
		}
		fputs("Answer not recognised, try again. y/n: ", stdout);
	}

	return 1;
}

int main(int argc, char** argv)
{
	TM_TEST(1, 4);
	TM_TEST2(2);
	
	return 0;
}
