/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbestman <rbestman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 01:15:53 by rbestman          #+#    #+#             */
/*   Updated: 2025/04/29 01:53:27 by rbestman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include <stdlib.h>
#include <stdio.h>

static int count_words(char *str)
{
	int	i;
	int	words;
	int	in_quote;

	i = 0;
	words = 0;
	in_quote = 0;

	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i])
			words++;
		while (str[i] && (in_quote || str[i] != ' '))
		{
			if (str[i] == '\'')
			in_quote = !in_quote;
			i++;
		}
	}
	return (words);
}

static int word_len(char *str)
{
    int i = 0;
    int in_quotes = 0;

    while (str[i] && (in_quotes || str[i] != ' '))
    {
        if (str[i] == '\'')
            in_quotes = !in_quotes;
        i++;
    }
    return (i);
}

static char *malloc_word(int len)
{
    char *word = malloc(sizeof(char) * (len + 1));
    if (!word)
        return (NULL);
    word[len] = '\0';
    return (word);
}

void copy_letters(char *dst, char *src, int len)
{
    int i = 0;
    int j = 0;
    int in_quotes = 0;

    while (i < len)
    {
        if (src[i] == '\'')
        {
            in_quotes = !in_quotes;
            i++;
            continue;
        }
        dst[j++] = src[i++];
    }
    dst[j] = '\0';
}

static char *copy_word(char *str, int *i)
{
    int len = word_len(str + *i);
    char *word = malloc_word(len);

    if (!word)
        return (NULL);
    copy_letters(word, str + *i, len);
    *i += len;
    return (word);
}

char    **split_cmd(char *str)
{
	int		i;
	int		j;
	int		wc;
	char	**words;

	i = 0;
	j = 0;
	if (!ft_strchr(str, 39))
		return (ft_split(str, ' '));
	wc = count_words(str);
	words = malloc(sizeof(char *) * (wc + 1));
	if (!words)
		return (NULL);
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i])
			words[j++] = copy_word(str, &i);
	}
	words[j] = NULL;
	return (words);
}
