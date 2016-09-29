/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_tool2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 14:21:37 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/28 18:35:55 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static inline t_color	diffuse_shadow(t_hit *p, t_ray *r, t_light *l, t_hit *t)
{
	double	angle;
	double	coef;
	t_color	tmp_color;

	angle = fabs(dot_product(r->dir, p->nml));
	coef = 1 - t->opacity;
	tmp_color.r = p->color.r * angle * l->color.r * coef;
	tmp_color.g = p->color.g * angle * l->color.g * coef;
	tmp_color.b = p->color.b * angle * l->color.b * coef;
	return (tmp_color);
}

static inline t_color	diffuse_light(t_hit *pxl, t_ray *light_ray, t_light *l)
{
	double	angle;
	double	coef;
	t_color	tmp_color;

	angle = dot_product(light_ray->dir, pxl->nml);
	angle /= get_length(light_ray->dir);
	angle /= get_length(pxl->nml);
	init_color(&tmp_color, 0, 0, 0);
	coef = pxl->opacity;
	if (angle < 0)
	{
		angle = -angle;
		if (pxl->opacity >= 0.5)
			coef = 1 - pxl->opacity;
	}
	tmp_color.r = pxl->color.r * angle * l->color.r * coef;
	tmp_color.g = pxl->color.g * angle * l->color.g * coef;
	tmp_color.b = pxl->color.b * angle * l->color.b * coef;
	return (tmp_color);
}

static inline t_color	specular_light(t_hit *p, t_vec *r, t_light *l, t_ray *c)
{
	t_color	tmp_color;
	double	spec;
	double	coef;
	double	tmp;

	tmp = dot_product(c->dir, normalize(*r));
	init_color(&tmp_color, 0, 0, 0);
	if (!(tmp < 0 && p->opacity == 1))
	{
		if (p->opacity == 1)
			spec = pow(tmp, p->specular + 1);
		else
			spec = pow(tmp, p->specular);
		if (spec < 0)
			coef = fabs(spec) * p->opacity;
		else
			coef = 1;
		tmp_color.r = spec * l->color.r * coef;
		tmp_color.g = spec * l->color.g * coef;
		tmp_color.b = spec * l->color.b * coef;
	}
	return (tmp_color);
}

t_color					set_color1(t_node *tmp, t_ray *r, t_hit *hit, int s)
{
	t_color		c2;

	init_color(&c2, 0, 0, 0);
	if (s == 0 || hit[0].opacity < 1)
		c2 = diffuse_light(&hit[0], r, ((t_light *)(tmp->data)));
	else if (hit[1].opacity < 1 && s == 1)
		c2 = diffuse_shadow(&hit[0], r, ((t_light *)(tmp->data)), &hit[1]);
	return (c2);
}

t_color					set_color2(t_node *tmp, t_ray *c, t_ray *r, t_hit *hit)
{
	t_color		c2;
	t_vec		refl;
	double		dot;

	dot = dot_product(r->dir, hit[0].nml);
	refl = vec_sub(scalar_product(hit[0].nml, dot * 2), r->dir);
	c2 = (specular_light(&hit[0], &refl, ((t_light *)(tmp->data)), c));
	return (c2);
}
