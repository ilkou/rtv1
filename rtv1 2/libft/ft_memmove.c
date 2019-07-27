/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jadi <md.eljadi@outlook.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:29:17 by mel-jadi          #+#    #+#             */
/*   Updated: 2018/10/18 18:47:39 by mel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int	i;

	i = -1;
	if (src < dst)
		while ((int)(--len) >= 0)
			((unsigned char *)dst)[len] = ((unsigned char *)src)[len];
	else
		while (++i < (int)len)
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
	return (dst);
}
