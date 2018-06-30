/*
* New system call Demo
* syscall 'pinfo'
*/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#ifndef SYSCALL_THROUGH_LIBC

int pinfo(struct prcs_info *pif, pid_t pid)
{
	__asm("mov x8, #285;" //x8 holds syscall no
		  " svc #0;" 			// supervisor call
//		  "ret"); 				// return with X0 holding the errno
	);

		printf("ret was useless \n");
		return 0; //placeholder return
}
#endif

int main()
{
	int ret;
	pid_t pid;

	printf("System Call Demo \n");
	printf("syscall pinfo() \n");

	struct prcs_info pif =
	{
		.prio = -1,
		.state = -1,	/* -1 unrunnable, 0 runnable, >0 stopped */
		.cpu = 0,
		.nvcsw = 0,
		.start_time = 0,
	};

	//TODO: parse /proc/<pid> to select a process
//	pid = getpid(); // current process
//	pid = 1; // for init process
	pid = -1; // to test errno

	ret = pinfo(&pif, pid);
	if (ret < 0) {
		printf("System call error no: %d\n", ret);
		return -1;
	}

	printf("Process info : \n");
	printf("Process priority : %d\n", pif.prio);
	printf("Process state : %ld\n", pif.state);
	printf("Current CPU : %d\n", pif.cpu);
	printf("Context switch count : %lu\n", pif.nvcsw);
	printf("Process start time (ns) : %llu\n", pif.start_time);

	printf("================= \n\n"); 
    return 0;
}

