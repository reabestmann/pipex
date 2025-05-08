/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbestman <rbestman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:55:10 by rbestman          #+#    #+#             */
/*   Updated: 2025/04/27 20:50:23 by rbestman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Function that creates and handles a child process that executes a command and sends its output to a pipe */
void	child_process(char *argv, char **envp)
{
	pid_t	pid; // space for process ID for the child
	int		fd[2]; // space for the read and write end of pipe

	if (pipe(fd) == -1) // create pipe
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0) // inside child
	{
		close(fd[0]); // read end not needed (child is writing)
		dup2(fd[1], STDOUT_FILENO); // write to pipe instead of stdout
		execute(argv, envp); // run cmd
	}
	else // inside parent
	{
		close(fd[1]); // write end not needed (parent is reading)
		dup2(fd[0], STDIN_FILENO); // read from pipe instead of stdin
		waitpid(pid, NULL, 0); // wait for the child process to finish execution
	}
}

/* Function that handles 'here_doc' input and writes it into a pipe */
void	here_doc(char *limiter, int params)
{
	pid_t	reader; // variable for process ID of the child process
	char	*line; // store each line of input from user
	int		fd[2]; // space for read and write ends of pipe

	if (params < 6) // here_doc need min 6 params
		usage();
	if (pipe(fd) == -1) //  create pipe
		error();
	reader = fork(); // forking a child process
	if (reader == -1)
		error();
	if (reader == 0) // inside the child
	{
		close(fd[0]); // read end is not needed (child is writing)
		while (get_next_line(&line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(0); // exit child process when limiter is reached
			write(fd[1], line, ft_strlen(line)); // write line into pipe
		}
	}
	else // inside the parent
	{
		close(fd[1]); // write end is not needed (parent is reading)
		dup2(fd[0], STDIN_FILENO); // read from pipe instead of stdin
		wait(NULL); // wait for child to finish before continuing
	}
}

/* main function that handles multiple pipes and supports here_doc */
int	main(int params, char **argv, char **envp)
{
	int	i;
	int	infile;
	int	outfile;

	if (params >= 5) // correct input
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0) // here_doc mode
		{
			i = 3; // skip program name, "here_doc" & limiter to get to cmd1
			outfile = open_file(argv[params - 1], 0); 
			infile = open_file(argv[1], 2);
			dup2(infile, STDIN_FILENO); // read from infile instead of stdin
		}
		else // normal mode
		{
			i = 2; // skip only program name & infile to get to cmd1
			outfile = open_file(argv[params - 1], 1);
			infile = open_file(argv[1], 2);
			dup2(infile, STDIN_FILENO); // read from infile instead of stdin
		}
		while (i < params - 2)
			child_process(argv[i++], envp); // create process for each cmd
		dup2(outfile, STDOUT_FILENO); // write into outfile instead of stdout
		execute(argv[params - 2], envp); // run final command
	}
	usage(); // show how to use program if not enough arguments
}
