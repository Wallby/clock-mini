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

int main(int argc, char** argv)
{
	TM_TEST(1, 9);
	
	return 0;
}
