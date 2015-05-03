/*
 * system_calls_use.c
 *
 *  Created on: 19/4/2015
 *      Author: Alejandro Zalazar
 */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

int useLs() {
	FILE *fp;
	fp = fopen("/tmp/1.txt", "w");
	fprintf(fp, "a\n");
	fprintf(fp, "d\n");
	fprintf(fp, "c\n");
	fprintf(fp, "e\n");
	fprintf(fp, "f\n");
	fprintf(fp, "b\n");
	fprintf(fp, "z\n");
	fprintf(fp, "h\n");
	fclose(fp);

	enum PIPES {
	    READ, WRITE
	};
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;
	int fd = open("/tmp/resultFile.txt", O_RDWR | O_CREAT, mode);


	 int filedes[2];
	    int filedes2[2];
	    int filedes3[2];
//	    int filedes4[2];
	    pipe(filedes);
	    pipe(filedes2);
	    pipe(filedes3);
//	    pipe(filedes4);

	    pid_t pid = fork();
	    if (pid == 0) {
	        dup2(filedes[WRITE], 1);
	    char *argv[] = {"cat", "/tmp/1.txt", NULL};
	        int result = execv("/bin/cat", argv);
	        printf("proc %d, if CAT file result = %d\n", result, pid);
	    }
	    else {
	        close(filedes[1]);
	        printf("proc %d, if ELSE CAT file\n", pid);
	    }

	    pid_t pid2 = fork();
	    if (pid2 == 0) {
	    dup2(filedes[READ], 0);
	    dup2(filedes2[WRITE], 1);
	        char *argv[] = {"fakemap.sh", "-c", NULL};
	        int result = execv("/home/utnso/Documentos/fakemap.sh", argv);
	        printf("proc %d, if MAP file result = %d\n", result, pid2);
	    }
	    else {
	        close(filedes2[1]);
	        printf("proc %d, if ELSE MAP file\n", pid2);
	    }

	    pid_t pid3 = fork();
	    if (pid3 == 0) {


	        dup2(filedes2[READ], 0);
	        dup2(filedes3[WRITE], 1);
	        char *argv1[] = {"sort", NULL};
			int result = execv("/usr/bin/sort", argv1);
			printf("proc %d, if SORT file result = %d\n", result, pid3);
	    } else {
	    	close(filedes3[1]);
	    	printf("proc %d, if ELSE SORT file\n", pid3);
	    }

	    pid_t pid4 = fork();
	    if (pid4 == 0) {


	        dup2(filedes3[READ], 0);
	        dup2(fd, 1);
	        char *argv1[] = {"fakereduce.sh", NULL};
			int result = execv("/home/utnso/Documentos/fakereduce.sh", argv1);
			printf("proc %d, if REDUCE file result = %d\n", result, pid4);
	    } else {

	    	printf("proc %d, if ELSE REDUCE file\n", pid4);
	    }


	    waitpid(pid, (int *)NULL, (int)NULL);
	    waitpid(pid2, (int *)NULL, (int)NULL);
	    waitpid(pid3, (int *)NULL, (int)NULL);

	    time_t now = time (NULL);
	    dprintf(fd, "%s\n", asctime (localtime (&now)));

	    close(fd);
	    close(filedes3[0]);
	    close(filedes3[1]);
	    close(filedes[0]);
	    close(filedes[1]);
	    close(filedes2[0]);
	    close(filedes2[1]);
//	    close(filedes4[0]);
//	    close(filedes4[1]);
	    printf("closing\n");
	    return 0;
}


