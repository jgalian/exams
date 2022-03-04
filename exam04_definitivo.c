#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int ft_strlen(char *str)
{
	int len = 0;
	while (str[len])
		len++;
	return len;
}

void print_error(char *str1, char *str2, int end)
{
	write(2, str1, ft_strlen(str1));
	if (str2)
		write(2, str2, ft_strlen(str2));
	write(2, "\n", 1);
	if (end)
		exit(EXIT_FAILURE);
}

char **get_next(char **argv, char *str)
{
	while (argv && *argv)
	{
		if (!strcmp(*argv, str))
		{
			*argv = NULL;
			return ++argv;
		}
		argv++;
	}
	return NULL;
}

void builtin_cd(char **argv)
{
	if (!argv || *(argv + 1))
		print_error("error: cd: bad arguments", NULL, 0);
	else if (argv && *argv)
	{
		if (chdir(*argv) == -1)
			print_error("error: cd: cannot change directory to ", *argv, 0);
	}
}

void execute_cmd(char **argv, char **env, int *fd_pipe, int fd_in)
{
	int childpid = fork();

	if (childpid == -1)
		print_error("error: fatal", NULL, 1);
	else if (childpid == 0)
	{
		if (fd_in)
			if (dup2(fd_in, 0) == -1)
				print_error("error: fatal", NULL, 1);
		if (fd_pipe[1] != 1)
			if (dup2(fd_pipe[1], 1) == -1)
				print_error("error: fatal", NULL, 1);
		if (execve(*argv, argv, env) == -1)
			print_error("error: fatal", NULL, 0);
		exit(EXIT_FAILURE);
	}
	waitpid(childpid, NULL, 0);
}

void execute(char **argv, char **env)
{
	char **next;
	int fd_in = 0;
	int fd_pipe[2];

	fd_pipe[0] = 0;
	while (argv && *argv)
	{
		fd_pipe[1] = 1;
		next = get_next(argv, "|");
		if (!strcmp(*argv, "cd"))
			builtin_cd(++argv);
		else
		{
			if (next)
			{
				if (pipe(fd_pipe) == -1)
					print_error("error: fatal", NULL, 1);
			}
			execute_cmd(argv, env, fd_pipe, fd_in);
			if (fd_in)
				if (close(fd_in) == -1)
					print_error("error: fatal", NULL, 1);
			if (fd_pipe[1] != 1)
				if (close(fd_pipe[1]) == -1)
					print_error("error: fatal", NULL, 1);
			if (fd_pipe[0] != 0)
				fd_in = fd_pipe[0];
		}
		argv = next;
	}
}

int main(int argc, char **argv, char **env)
{
	char **next;

	argv++;
	while (argv && *argv)
	{
		next = get_next(argv, ";");
		execute(argv, env);
		argv = next;
	}
	return 0;
}
