/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 01:41:15 by sduprey           #+#    #+#             */
/*   Updated: 2016/10/04 16:20:10 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void		complete_scene(t_scene *s, double *tmp)
{
	s->w = WIDTH;
	s->h = HEIGHT;
	s->objects = NULL;
	s->lights = NULL;
	s->is_dof = 0;
	s->dof = 0;
	s->reflection = 1;
	s->blur_array = tmp;
	s->is_real = 0;
	s->blur = 0;
	s->filter = NONE;
	s->ambient_index = 0.0;
	s->aa = 0;
	init_color(&(s->ambient_color), 255, 255, 255);
}

t_scene		*init_scene(void)
{
	t_scene	*s;
	double	*tmp;
	int		i;

	i = -1;
	if (!(tmp = (double *)malloc(sizeof(double) * HEIGHT * WIDTH)))
		return (NULL);
	while (++i < HEIGHT * WIDTH)
		tmp[i] = 0.0;
	if (!(s = (t_scene *)malloc(sizeof(t_scene))))
		return (NULL);
	complete_scene(s, tmp);
	return (s);
}

void		free_scene(t_scene **scene)
{
	free((*scene)->blur_array);
	if ((*scene)->objects)
		free_node_list(&((*scene)->objects));
	if ((*scene)->lights)
		free_node_list(&((*scene)->lights));
	free(*scene);
	*scene = NULL;
}
