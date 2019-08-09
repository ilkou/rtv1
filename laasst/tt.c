/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 21:05:47 by oouklich          #+#    #+#             */
/*   Updated: 2019/08/06 21:21:29 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int				ft_hit_cone(t_object *o, t_ray *r, t_interval t, t_hit *rec)
{
	t_vector	oc;
	t_vector	temp;
	double		delta;

	oc = ft_sub(r->origin, o->pos);
	rec->coef[0] = ft_dot(r->dir, r->dir) - (1 + pow(tan(o->size), 2))
		* pow(ft_dot(r->dir, o->rot), 2);
	rec->coef[1] = 2 * (ft_dot(r->dir, oc) - (1 + pow(tan(o->size), 2))
			* ft_dot(r->dir, o->rot) * ft_dot(oc, o->rot));
	rec->coef[2] = ft_dot(oc, oc) - (1 + pow(tan(o->size), 2))
		* pow(ft_dot(oc, o->rot), 2);
	delta = rec->coef[1] * rec->coef[1] - 4 * rec->coef[0] * rec->coef[2];
	if (delta < 0)
		return (0);
	rec->r[0] = (-rec->coef[1] - sqrt(delta)) / (2 * rec->coef[0]);
	rec->r[1] = (-rec->coef[1] + sqrt(delta)) / (2 * rec->coef[0]);
	rec->r[0] = rec->r[0] < rec->r[1] ? rec->r[0] : rec->r[1];
	if (rec->r[0] < t.t_max && rec->r[0] > t.t_min)
	{
		rec->t = rec->r[0];
		rec->p = ft_ray_function(r, rec->t);
		temp = ft_pro_k(o->rot, (ft_dot(r->dir, o->rot) * rec->t
					+ ft_dot(oc, o->rot)));
		temp = ft_pro_k(temp, (1 + pow(tan(o->size), 2)));
		rec->n = ft_normalize(ft_sub(ft_sub(rec->p, o->pos), temp));
		return (1);
	}
	return (0);
}
