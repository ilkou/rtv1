/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbr_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jadi <md.eljadi@outlook.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 21:40:58 by mel-jadi          #+#    #+#             */
/*   Updated: 2018/10/17 21:41:20 by mel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nbr_words(char const *str, char c)
{
	int		nbr;
	int		i;

	nbr = 0;
	i = 0;
	if (str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] != c && str[i])
		{
			i = i + ft_word_size(str, c, i);
			nbr++;
		}
		else
			i++;
	}
	return (nbr);
}
