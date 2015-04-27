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
	    int filedes4[2];
	    pipe(filedes);
	    pipe(filedes2);
	    pipe(filedes3);
	    pipe(filedes4);

	    pid_t pid = fork();
	    if (pid == 0) {
	        dup2(filedes[WRITE], 1);
	    char *argv[] = {"cat", "/tmp/1.txt", NULL};
	        execv("/bin/cat", argv);
	    }
	    else {
	        close(filedes[1]);
	        printf("else 1\n");
	    }

	    pid_t pid2 = fork();
	    if (pid2 == 0) {
	    dup2(filedes[READ], 0);
	    dup2(filedes2[WRITE], 1);
	        char *argv[] = {"fakemap.sh", "-c", NULL};
	        execv("/home/utnso/Documentos/fakemap.sh", argv);
	    }
	    else {
	        close(filedes2[1]);
	        printf("else 2\n");
	    }

	    pid_t pid3 = fork();
	    if (pid3 == 0) {


	        dup2(filedes2[READ], 0);
	        dup2(filedes3[WRITE], 1);
	        char *argv1[] = {"sort", NULL};
			execv("/usr/bin/sort", argv1);
	    } else {
	    	close(filedes3[1]);
	    	printf("else 3\n");
	    }

	    pid_t pid4 = fork();
	    if (pid4 == 0) {


	        dup2(filedes3[READ], 0);
	        dup2(fd, 1);
	        char *argv1[] = {"fakereduce.sh", NULL};
			execv("/home/utnso/Documentos/fakereduce.sh", argv1);
	    } else {

	    	printf("else 4\n");
	    }


	    waitpid(pid, (int *)NULL, (int)NULL);
	    waitpid(pid2, (int *)NULL, (int)NULL);
	    waitpid(pid3, (int *)NULL, (int)NULL);

	    time_t now = time (NULL);
	    dprintf(fd, "%s\n", asctime (localtime (&now)));

	    close(fd);
	    close(filedes3);
	    printf("closing\n");
	    return 0;
}
