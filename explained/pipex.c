/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbestman <rbestman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:13:53 by rbestman          #+#    #+#             */
/*   Updated: 2025/04/27 16:19:27 by rbestman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* function to set up the first command to read from file1 and write to pipe */
void	child_process(char **argv, char **envp, int *fd)
{
	int	infile;

	infile = open(argv[1], O_RDONLY, 0); // open for reading only, no permission bits needed
	if (infile == -1)
		error();
	// calling dub2 to re-route input/output to pass through the pipe
	dup2(fd[1], STDOUT_FILENO); // redirect stdout to the write end of pipe
	dup2(infile, STDIN_FILENO); // redirect stdin to the infile
	close(fd[0]); // child process doesn't need the read end of pipe
	execute(argv[2], envp); // run cmd1
}

/* function to set up the second command to read from pipe and write to outfile */
void	parent_process(char **argv, char **envp, int *fd)
{
	int	outfile;

	//  O_WRONLY = open for writing, O_CREAT = create file if it doesnt exist, O_TRUNC = empty file if it does
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644); // permit only user to write, others read
	if (outfile == -1)
		error();
	dup2(fd[0], STDIN_FILENO); // redirect stdin to read end of pipe
	dup2(outfile, STDOUT_FILENO); // redirect stdout to outfile
	close(fd[1]); // parent process doesn't need the write end of file
	execute(argv[3], envp); // run cmd2
}

/* Main function that checks validity of arguments and run child & parent process */
int	main(int params, char **argv, char **envp)
{
	int	fd[2]; // 2 ends of the pipe: fd[0] = read end, fd[1] = write end
	pid_t	pid1; // variable to store the process ID

	if (params == 5) // only accepting "./pipex file1 cmd1 cmd2 file2"
	{
		if (pipe(fd) == -1) // pipe(fd) fills fd[0] & fd[1] with file descriptors, creating the pipe
			error();
		pid1 = fork(); // forking a child process
		if (pid1 == -1)
			error();
		if (pid1 == 0) // 0 = child, >0 = parent
			child_process(argv, envp, fd); // read infile, run cmd1, write into pipe
		waitpid(pid1, NULL, 0); // parent process waiting until child process finishes
		parent_process(argv, envp, fd); // read from pipe, run cmd 2, write into outfile
	}
	else
	{
		ft_putstr_fd("Error: Invalid input\n", 2);
		ft_putstr_fd("Usage: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
	} // handling invalid input
	return (0);
}
