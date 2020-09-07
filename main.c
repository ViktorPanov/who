#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#define SHOWHOST

void show_info (struct utmp *utmpfp);
void show_time (long);

char *ut_type[] = {"EMPTY", "RUN_LVL", "BOOT_TIME", "OLD_TIME",
			"NEW_TIME", "INIT_PROCESS", "LOGIN_PROCESS",
			"USER_PROCESS", "DEAD_PROCESS", NULL};

int main ()
{
	struct utmp current_record;
	int utmpfd;
	int reclen = sizeof (current_record);
	printf ("UTPM_FILE = %s\n\n", UTMP_FILE);
	if ((utmpfd = open (UTMP_FILE, O_RDONLY)) == -1) {
		perror (UTMP_FILE);
		exit (1);
	}

	while (read (utmpfd, &current_record, reclen) == reclen)
		show_info (&current_record);
	close (utmpfd);
	return 0;
}

void show_info (struct utmp *utmpfp)
{
	printf ("%.13s\t", ut_type[utmpfp->ut_type]);
	printf ("%8.8s", utmpfp->ut_name);
	printf (" ");
	printf ("%8.8s", utmpfp->ut_line);
	printf (" ");
	show_time (utmpfp->ut_time);
	printf (" ");
#ifdef SHOWHOST
	if (utmpfp->ut_host[0] != '\0')
		printf ("(%s)", utmpfp->ut_host);
#endif
	printf ("\n");
	return;
}

void show_time (long timeval)
{
	char *cp;
	cp = ctime (&timeval);
	printf ("%24.24s", cp);
}
