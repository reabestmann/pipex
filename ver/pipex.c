/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbestman <rbestman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:13:53 by rbestman          #+#    #+#             */
/*   Updated: 2025/04/28 20:49:01 by rbestman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Function to set up first command to read from infile and write to pipe */
void	child_process(char **argv, char **envp, int *fd)
{
	int	infile;

	infile = open(argv[1], O_RDONLY, 0);
	if (infile == -1)
		error();
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(fd[0]);
	execute(argv[2], envp);
}

/* Function to set up second command to read from pipe and write to outfile */
void	parent_process(char **argv, char **envp, int *fd)
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		error();
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[1]);
	execute(argv[3], envp);
}

void	pipex(char **argv, char **envp, int *fd)
{
	pid_t	pid1;
	pid_t	pid2;

	pid1 = fork();
	if (pid1 == -1)
		error();
	if (pid1 == 0)
		child_process(argv, envp, fd);
	pid2 = fork();
	if (pid2 == -1)
		error();
	if (pid2 == 0)
		parent_process(argv, envp, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

/* Main function that handles input, creates a pipe and runs child & parent processes */
int	main(int params, char **argv, char **envp)
{
	int	fd[2];

	if (!envp)
		error();
	if (params == 5)
	{
		if (pipe(fd) == -1)
			error();
		pipex(argv, envp, fd);
	}
	else
	{
		ft_putstr_fd("Error: Invalid input\n", 2);
		ft_putstr_fd("Usage: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
	}
	return (0);
}
