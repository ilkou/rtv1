/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myrand48.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 18:34:48 by oouklich          #+#    #+#             */
/*   Updated: 2019/07/22 18:35:33 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/rtv1.h"

static	void	ft_dorand48(unsigned short xseed[3])
{
	unsigned long			accu;
	unsigned short			temp[2];

	accu = (unsigned long)RAND48_MULT_0 * (unsigned long)xseed[0] +
		(unsigned long)RAND48_ADD;
	temp[0] = (unsigned short)accu;/* lower 16 bits */
	accu >>= sizeof(unsigned short) * 8;
	accu += (unsigned long)RAND48_MULT_0 * (unsigned long)xseed[1] +
		(unsigned long)RAND48_MULT_1 * (unsigned long)xseed[0];
	temp[1] = (unsigned short)accu;/* middle 16 bits */
	accu >>= sizeof(unsigned short) * 8;
	accu += RAND48_MULT_0 * xseed[2] + RAND48_MULT_1 * xseed[1] +
		RAND48_MULT_2 * xseed[0];
	xseed[0] = temp[0];
	xseed[1] = temp[1];
	xseed[2] = (unsigned short)accu;
}

static	double	ft_erand48(unsigned short xseed[3])
{
	ft_dorand48(xseed);
	return (ldexp((double)xseed[0], -48) + ldexp((double)xseed[1], -32) +
			ldexp((double)xseed[2], -16));
}

double			myrand48(void)
{
	static int				i;
	static unsigned short	rand_seed[3];

	if (++i == 1)
	{
		rand_seed[0] = (unsigned short)RAND48_SEED_0;
		rand_seed[1] = (unsigned short)RAND48_SEED_1;
		rand_seed[2] = (unsigned short)RAND48_SEED_2;
	}
	return (ft_erand48(rand_seed));
}