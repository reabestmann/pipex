/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbestman <rbestman@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:07:54 by rbestman          #+#    #+#             */
/*   Updated: 2025/04/17 15:11:36 by rbestman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int	main(void)
{
	int	*pfd;
	char	*str;

	pipe(pfd);
	write(pfd[1], "hello", 5);
	read(pfd[0], str, 2);
	str[2] = '\0'
	printf("%s\n", str);
}


