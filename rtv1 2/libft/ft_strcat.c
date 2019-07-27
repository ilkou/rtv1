/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jadi <md.eljadi@outlook.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 21:25:10 by mel-jadi          #+#    #+#             */
/*   Updated: 2018/10/05 21:35:37 by mel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	int		i;
	int		size;

	size = -1;
	i = 0;
	while (dest[i])
	{
		size++;
		i++;
	}
	i = 0;
	while (src[i])
	{
		dest[size + i + 1] = src[i];
		i++;
	}
	dest[size + i + 1] = '\0';
	return (dest);
}
