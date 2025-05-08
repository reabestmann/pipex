/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbestman <rbestman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:55:35 by rbestman          #+#    #+#             */
/*   Updated: 2025/04/27 20:02:26 by rbestman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Function to handle incorrect Input */
void	usage(void)
{
	ft_putstr_fd("Error: Input Invalid\n", 2);
	ft_putstr_fd("Usage: ./pipex <file1> <cmd1> <cmd2> <...> <file2>\n", 1);
	ft_putstr_fd("	     ./pipex \"here doc\" <LIMITER> <cmd> <cmd1> <file>\n", 1);
	exit(0);
}

/* Function to open file based on the case */
int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	// here_doc output: collecting content line for line
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0644);
	// normal output: clear old content and write new
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// input file
	else if (i == 2)
		file = open(argv, O_RDONLY, 0);
	// error
	if (file == -1)
		error();
	return (file);
}

/* Function that reads one line at a time from stdin, and returns the number of characters read */
int	get_next_line(char **line)
{
	char    *buffer; // to store the line
	int             i; // index for each character stored
	int             r; // number of characters read
	char    c; // the character being read

	i = 0;
	r = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1); // indicating failure
	r = read(0, &c, 1); // read the first byte from stdin (0) into c
	while (r && c != '\n' && c != '\0')
	{
		if (c && c != '\n')
			buffer[i] = c; // store each character before the newline
		i++;
		r = read(0, &c, 1); // read next byte into c (read moves to next byte after each call)
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer; // line is now stored in the array passed to function
	free(buffer);
	return (r); // full line = r > 0, EOF = r == 0, error = r == -1
}
