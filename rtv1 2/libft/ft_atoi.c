/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jadi <md.eljadi@outlook.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 14:50:35 by mel-jadi          #+#    #+#             */
/*   Updated: 2018/10/11 20:56:09 by mel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int		i;
	int		nbr;
	int		test;

	test = 0;
	i = 0;
	nbr = 0;
	while ((str[i] == '\n' || str[i] == '\t' || str[i] == '\r' ||
				str[i] == '\v' || str[i] == '\f' || str[i] == ' ') && str[i])
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			test++;
		i++;
	}
	while ((*(str + i) >= '0') && (*(str + i) <= '9'))
	{
		nbr = nbr * 10 + *(str + i) - 48;
		i++;
	}
	if (test == 1)
		return (-nbr);
	return (nbr);
}
