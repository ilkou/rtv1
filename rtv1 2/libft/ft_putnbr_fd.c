/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jadi <md.eljadi@outlook.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 15:45:17 by mel-jadi          #+#    #+#             */
/*   Updated: 2018/10/07 15:47:12 by mel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	int size;
	int test;

	if (nb < 0)
	{
		nb = -nb;
		ft_putchar_fd('-', fd);
	}
	if (nb == -2147483648)
	{
		ft_putchar_fd(50, fd);
		nb = 147483648;
	}
	size = 1;
	test = nb;
	while ((test /= 10) != 0)
		size *= 10;
	while (size != 0)
	{
		test = nb / size;
		nb %= size;
		size /= 10;
		ft_putchar_fd(test + 48, fd);
	}
}
