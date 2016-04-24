#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int		pipe_start_prgm(char *argv[], char **env)
{
	int		pipefd[2] = {0, 1};
	pid_t	child_pid;
	pid_t	tpid;
	int		child_status;
	char	c;

	pipe(pipefd);
	child_pid = fork();
	tpid = 0;
	if (child_pid == 0)
	{
		execve(argv[0], argv, env);
		close(pipefd[1]);
		printf("....\n");
		while (read(pipefd[0], &c, 1))
			write(1, &c, 1);
		printf("....\n");
		close(pipefd[0]);
		exit(0);
	}
	else
	{
		close(pipefd[0]);          /* Close unused read end */
		argv[1] = "????????????????????";       
		write(pipefd[1], argv[1], 10);
		close(pipefd[1]);
		wait(&child_pid);                /* Wait for child */
		printf("<%s>\n", argv[1]);
	}
	return (child_status);
}

int main(int argc, char **argv, char **env)
{
	int fds[2];// = {0, 1};
	char	*args1[] = {"/bin/ls", NULL};
	char	*args2[] = {"/bin/cat", NULL};
	char	c;

	pipe_start_prgm(args1, env);
//	start_prgm(fds, args2, env);
}