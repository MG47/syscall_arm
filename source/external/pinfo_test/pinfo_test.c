/*
* New system call Demo
* syscall 'pinfo'
*/

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#ifndef SYSCALL_THROUGH_LIBC
extern int __pinfo(int pif);
#endif

struct process_info {
	pid_t pid; 	// process ID
	pid_t tgid; 	// thread group id
	int prio; 	// priority
	char *parent; 	// name of parent task
	char *name; 	// name of task
	unsigned long nvcsw; 		// context switch count
	unsigned long long start_time; 	// start time in ns
};

#ifdef SYSCALL_THROUGH_LIBC
int pinfo_call(int pif)
{
	return pinfo(pif);
}
#else
int pinfo_call(int pif)
{
	__asm("mov x8, #285;"
	" svc #0");

	return 0;
	//	return __pinfo(pif);
}
#endif

int main()
{
//	struct pinfo *pif;
	int pif = 0;
	int ret;

	printf("System Call Demo \n");
	printf("syscall pinfo() \n");

	ret = pinfo_call(pif);
	if (ret < 0) {
//		printf("Error: %s\n", strerror(errno));
		return -1;
	}

	printf("Process info : \n");
#if 0
	printf("Process ID : %d: \n", pif->pid);
	printf("Process tgid : %d\n", pif->tgid);
	printf("Process priority : %d\n", pif->prio);
	printf("Process parent : %s\n", pif->parent);
	printf("Context switch count : %d\n", pif->nvcsw);
	printf("Process start time (ns) : %llu\n", pif->start_time);
#endif
	printf("================= \n\n"); 
    return 0;
}

