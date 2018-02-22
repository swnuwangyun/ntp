#include <stdio.h>
#include <time.h>
#include <sys/timeb.h>

namespace libtimestamp
{

long int seconds()
{
	time_t timestamp_sec;
	time(&timestamp_sec);
	return (long int)timestamp_sec;
}

long long int milliseconds()
{
	struct timeb timer_msec;
	long long int timestamp_msec;
	ftime(&timer_msec);
	timestamp_msec = ((long long int) timer_msec.time) * 1000ll + (long long int) timer_msec.millitm;
	return timestamp_msec;
}

}