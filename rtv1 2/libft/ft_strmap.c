/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jadi <md.eljadi@outlook.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 18:12:35 by mel-jadi          #+#    #+#             */
/*   Updated: 2018/10/18 18:05:46 by mel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	unsigned int	i;
	unsigned int	size;
	char			*new;

	if (s == NULL || f == NULL)
		return (NULL);
	i = 0;
	size = ft_strlen(s);
	new = (char *)malloc(size + 1);
	if (new == NULL)
		return (NULL);
	while (s[i])
	{
		new[i] = (*f)(s[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}
