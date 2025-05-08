/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbestman <rbestman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:23:23 by rbestman          #+#    #+#             */
/*   Updated: 2025/05/07 20:13:00 by rbestman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Function to print & format system error messages and exit the program */
void	error(void)
{
	perror("Error");
	exit(1);
}

/* Function to free array memory */
static void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

/* Function to find the full path to a command */
static char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*part_path;
	char	*path;
	int		i;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
		{
			free_array(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_array(paths);
	return (NULL);
}

/* Function that prepares the command and runs it */
void	execute(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = split_cmd(argv);
	path = find_path(cmd[0], envp);
	if (!path || execve(path, cmd, envp) == -1)
	{
		perror("Error");
		free_array(cmd);
		free(path);
		exit(127);
	}
}
