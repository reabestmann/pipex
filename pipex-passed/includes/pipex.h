/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbestman <rbestman@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:57:15 by rbestman          #+#    #+#             */
/*   Updated: 2025/05/08 18:53:01 by rbestman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

/* utils.c */
void	execute(char *argv, char **envp);
void	error(char *msg, int status);

/* utils_cmd.c */
char	**split_cmd(char *str);

/* utils_bonus.c */
int		get_next_line(char **line);
int		open_file(char *argv, int i);
void	usage(void);

#endif
