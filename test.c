#include <clock_mini.h>
#include <test_mini.h>

#include <stdlib.h>
#include <stdio.h>

#if defined(_WIN32)
#include <windows.h>
#else //< #elif defined(__linux__)
#include <unistd.h>
#endif

// tested on windows and accuracy of Sleep is most often within..
// .. 20milliseconds
// v
#define EPSILON_IN_MILLISECONDS 20


int test_1()
{
	uint64_t a = cm_get_nanoseconds();
#if defined(_WIN32)
	Sleep(1000);
#else //< #elif defined(__linux__)
	sleep(1);
#endif
	uint64_t b = cm_get_nanoseconds();
	if(CM_GET_MILLISECONDS_FROM_NANOSECONDS(abs(b - a)) - 1000 > EPSILON_IN_MILLISECONDS)
	{
		printf("error: CM_GET_MILLISECONDS_FROM_NANOSECONDS(abs(b - a)) - 1000 > %llu (CM_GET_MILLISECONDS_FROM_NANOSECONDS(abs(b - a)) - 1000 == %llu)\n", EPSILON_IN_MILLISECONDS, CM_GET_MILLISECONDS_FROM_NANOSECONDS(abs(b - a)) - 1000);
		return 0;
	}
	
	// indicate progress as each repetition of this test takes atleast 1second
	printf("CM_GET_MILLISECONDS_FROM_NANOSECONDS(abs(b - a)) - 1000 was %llu which is within margin %llu\n", CM_GET_MILLISECONDS_FROM_NANOSECONDS(abs(b - a)) - 1000, EPSILON_IN_MILLISECONDS);

	return 1;
}

int main(int argc, char** argv)
{
	TM_TEST(1, 9);
	
	return 0;
}
