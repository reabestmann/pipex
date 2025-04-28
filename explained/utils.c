/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbestman <rbestman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:23:23 by rbestman          #+#    #+#             */
/*   Updated: 2025/04/27 19:26:30 by rbestman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* function to print error messages and exit the program safely */
void	error(void)
{
	perror("Error"); // prints & formats system error message (based on errno) 
	exit(1);
}

/* Function to free array memory */
void    free_array(char **array)
{
        int     i;

        i = -1;
        while (array[++i])
                free(array[i]);
        free(array);
}

/* function to find the full path to a command */
char	*find_path(char *cmd, char **envp)
{
	char	**paths; // variable to store directories with executable files
	char	*part_path;
	char	*path; // variables to temporarily hold string results as we combine paths
	int		i;

	i = 0;
	while (!strnstr(envp[i], "PATH", 4))
		i++; // loop through environment array until "PATH" is found
	paths = ft_split(envp[i] + 5, ':'); // store directories after "PATH="
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd); // eg: '/usr/bin' becomes 'usr/bin/ls'
		free(part_path);
		if (access(path, F_OK) == 0) // checks if command exists in path (yes = 0, no = -1)
		{
			free_array(paths);
			return (path);
		} // if command is found, free paths array & return path
		free(path);
		i++; // else we free & check the next possible path
	}
	free_array(paths); // free paths array
	return (0);
}

/* Function that prepares & runs the command */
void	execute(char *argv, char **envp)
{
	char	**cmd; // array that holds each part of the command
	int	i;
	char	*path;

	i = -1;
	cmd = ft_split(argv, ' '); // seperate command name from arguments/flags
	path = find_path(cmd[0], envp); // find the command's path
	// replace the current process with the command
	if (!path || execve(path, cmd, envp == -1))
	{
		free_array(cmd);
		error();
	} // free memory & exit program if path is not found or execve fails
}
