/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/10 17:50:40 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/26 18:46:13 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_light		*init_light(void)
{
	t_light	*light;

	if (!(light = (t_light *)malloc(sizeof(t_light))))
		return (NULL);
	light->type = 0;
	light->pos = init_vector(0, 0, 0);
	light->look_at = init_vector(0, 0, 0);
	init_color(&(light->color), 0, 0, 0);
	light->angle = 0;
	return (light);
}

int			light_invalid(t_light *light, t_vec *pos, t_vec *lk, t_color *color)
{
	if (!light->type || !pos || !color)
	{
		if (!pos)
			print_error("'pos' missing", 1);
		if (!color)
			print_error("'color' missing", 1);
		return (1);
	}
	if (light->type == DIRECT && !lk)
	{
		print_error("'lk' missing", 1);
		return (1);
	}
	return (0);
}

int			get_light_att2(t_elem *tmp2, t_light *light, t_vec **v, t_color **c)
{
	if (!ft_strcmp(tmp2->name, "pos"))
	{
		if (!get_new_vec(tmp2, &v[0]))
			return (0);
	}
	else if (!ft_strcmp(tmp2->name, "dir"))
	{
		if (!get_new_vec(tmp2, &v[1]))
			return (0);
	}
	else if (!ft_strcmp(tmp2->name, "color"))
	{
		if (!get_new_color(tmp2, c, LIGHT))
			return (0);
	}
	else if (!ft_strcmp(tmp2->name, "angle"))
	{
		if (!get_secur_num(tmp2, &(light->angle), 0, 180))
			return (0);
		light->angle = deg_to_rad(light->angle);
	}
	else
		return (return_invalid_arg(tmp2->name));
	return (1);
}

int			get_light_att(t_part *tmp, t_light *light)
{
	t_elem	*tmp2;
	t_vec	*v[2];
	t_color	*color;

	tmp2 = tmp->elems;
	color = NULL;
	v[0] = NULL;
	v[1] = NULL;
	while (tmp2)
	{
		if (!get_light_att2(tmp2, light, v, &color))
			return (0);
		tmp2 = tmp2->next;
	}
	if (light_invalid(light, v[0], v[1], color))
		return (0);
	light->pos = *v[0];
	light->color = *color;
	free(v[0]);
	free(color);
	light->look_at = (light->type == DIRECT) ? *v[1] : init_vector(0, 0, 0);
	if (v[1])
		free(v[1]);
	return (1);
}

t_scene		*get_lights(t_scene *scene, t_part *part)
{
	t_node	*node;
	t_light	*light;
	t_part	*tmp;

	if (!(tmp = part->sub_parts))
		return (NULL);
	while (tmp)
	{
		if (!(light = init_light()))
			return (NULL);
		light->type = tmp->type;
		if (!get_light_att(tmp, light))
			return (NULL);
		if (!(node = init_node(part->type, light, "light")))
			return (NULL);
		node_add(&(scene->lights), node);
		tmp = tmp->next;
	}
	return (scene);
}
