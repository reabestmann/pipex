/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_signed_int.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbestman <rbestman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 22:54:30 by rbestman          #+#    #+#             */
/*   Updated: 2025/04/02 12:37:58 by rbestman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_print_signed_int(int num)
{
	int		len;
	char	*str;

	len = 0;
	str = ft_itoa(num);
	if (str)
	{
		ft_putstr_fd(str, 1);
		len = ft_strlen(str);
		free(str);
	}
	return (len);
}
