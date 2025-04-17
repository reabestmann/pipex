/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned_int.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbestman <rbestman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 22:55:00 by rbestman          #+#    #+#             */
/*   Updated: 2025/04/02 12:38:21 by rbestman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_print_unsigned_int(unsigned int num)
{
	int		len;
	char	*str;

	len = 0;
	str = ft_utoa(num);
	if (str)
	{
		len = ft_strlen(str);
		ft_putstr_fd(str, 1);
		free(str);
	}
	return (len);
}
