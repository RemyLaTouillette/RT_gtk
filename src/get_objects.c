/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/09 02:29:09 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/14 16:47:48 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_sphere	*init_sphere(void)
{
	t_sphere	*sphere;

	if (!(sphere = (t_sphere *)malloc(sizeof(t_sphere))))
		return (NULL);
	sphere->radius = 0;
	sphere->center = init_vector(0, 0, 0);
	sphere->color = init_color(0, 0, 0);
	sphere->specular = 0;
	sphere->reflection = 0;
	sphere->opacity = 1;
	sphere->ref_index = 1;
	sphere->is_negativ = 0;
	sphere->texture = NONE;
	return (sphere);
}

t_plane	*init_plane(void)
{
	t_plane	*plane;

	if (!(plane = (t_plane *)malloc(sizeof(t_plane))))
		return (NULL);
	plane->pos = init_vector(0, 0, 0);
	plane->normal = init_vector(0, 0, 0);
	plane->color = init_color(0, 0, 0);
	plane->specular = 0;
	plane->reflection = 0;
	plane->opacity = 1;
	plane->ref_index = 1;
	plane->is_negativ = 0;
	plane->texture = NONE;
	return (plane);
}

t_cylinder	*init_cylinder(void)
{
	t_cylinder	*cylinder;

	if (!(cylinder = (t_cylinder *)malloc(sizeof(t_cylinder))))
		return (NULL);
	cylinder->radius = 0;
	cylinder->pos = init_vector(0, 0, 0);
	cylinder->dir = init_vector(0, 0, 0);
	cylinder->color = init_color(0, 0, 0);
	cylinder->length = 0;
	cylinder->h = 0;
	cylinder->specular = 0;
	cylinder->reflection = 0;
	cylinder->opacity = 1;
	cylinder->ref_index = 1;
	cylinder->is_negativ = 0;
	cylinder->texture = NONE;
	cylinder->is_closed = 0;
	return (cylinder);
}

t_cone	*init_cone(void)
{
	t_cone	*cone;

	if (!(cone = (t_cone *)malloc(sizeof(t_cone))))
		return (NULL);
	cone->r = 0;
	cone->pos = init_vector(0, 0, 0);
	cone->dir = init_vector(0, 0, 0);
	cone->color = init_color(0, 0, 0);
	cone->len = 0;
	cone->specular = 0;
	cone->reflection = 0;
	cone->opacity = 1;
	cone->ref_index = 1;
	cone->is_negativ = 0;
	cone->texture = NONE;
	cone->is_closed = 0;
	return (cone);
}

t_parallelo	*init_para(void)
{
	t_parallelo	*para;

	if (!(para = (t_parallelo *)malloc(sizeof(t_parallelo))))
		return (NULL);
	para->v0 = init_vector(0, 0, 0);
	para->v1 = init_vector(0, 0, 0);
	para->v2 = init_vector(0, 0, 0);
	para->color = init_color(0, 0, 0);
	para->specular = 0;
	para->reflection = 0;
	para->opacity = 1;
	para->ref_index = 1;
	para->texture = NONE;
	para->is_negativ = 0;
	return (para);
}

t_parallelo	*get_para(t_part *part)
{
	t_elem		*tmp2;
	t_vec		*pos1;
	t_vec		*pos2;
	t_vec		*pos3;
	t_color		*color;
	t_parallelo	*para;

	pos1 = NULL;
	pos2 = NULL;
	pos3 = NULL;
	color = NULL;
	if (!(para = init_para()))
		return (NULL);
	tmp2 = part->elems;
	while (tmp2)
	{
		if (!ft_strcmp(tmp2->name, "v0"))
		{
			if (!get_new_vec(tmp2, &pos1))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "v1"))
		{
			if (!get_new_vec(tmp2, &pos2))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "v2"))
		{
			if (!get_new_vec(tmp2, &pos3))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "color"))
		{
			if (!get_new_color(tmp2, &color, OBJECT))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "specular"))
		{
			if (!get_secur_num(tmp2, (double *)(&(para->specular)), 0, 100))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "reflection"))
		{
			if (!get_secur_num(tmp2, (double *)(&(para->reflection)), 0, 1))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "opacity"))
		{
			if (!get_secur_num(tmp2, (double *)(&(para->opacity)), 0, 1))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "ref_index"))
		{
			ft_putendl("'rectangle' : 'ref_index' always == 1\n\n");
			return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "is_negativ"))
		{
			if (!get_secur_is(tmp2, &(para->is_negativ)))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "texture"))
		{
			if (!get_secur_enum(tmp2, &(para->texture)))
				return (NULL);
		}
		else
		{
			return_invalid_arg(tmp2->name);
			return (NULL);
		}
		tmp2 = tmp2->next;
	}
	if (!pos1 || !pos2 || !pos3 || !color)
	{
		if (!pos1)
			ft_putendl("'v0' missing");
		if (!pos2)
			ft_putendl("'v1' missing");
		if (!pos3)
			ft_putendl("'v2' missing");
		if (!color)
			ft_putendl("'color' missing");
	}
	para->v0 = *pos1;
	para->v1 = *pos2;
	para->v2 = *pos3;
	para->color = *color;
	free(pos1);
	free(pos2);
	free(pos3);
	free(color);
	return (para);
}

t_triangle	*init_triangle(void)
{
	t_triangle	*triangle;

	if (!(triangle = (t_triangle *)malloc(sizeof(t_triangle))))
		return (NULL);
	triangle->v0 = init_vector(0, 0, 0);
	triangle->v1 = init_vector(0, 0, 0);
	triangle->v2 = init_vector(0, 0, 0);
	triangle->color = init_color(0, 0, 0);
	triangle->specular = 0;
	triangle->reflection = 0;
	triangle->opacity = 1;
	triangle->ref_index = 1;
	triangle->texture = NONE;
	triangle->is_negativ = 0;
	return (triangle);
}
t_tetra *init_tetra(void)
{
	t_tetra *tetra;

	if(!(tetra = (t_tetra *)malloc(sizeof(t_tetra))))
		return(NULL);
	tetra->v0 = init_vector(0, 0, 0);
	tetra->v1 = init_vector(0, 0, 0);
	tetra->v2 = init_vector(0, 0, 0);
	tetra->v3 = init_vector(0, 0, 0);
	tetra->color = init_color(0, 0, 0);
	tetra->specular = 0;
	tetra->reflection = 0;
	tetra->opacity = 1;
	tetra->ref_index = 1;
	tetra->texture = NONE;
	tetra->is_negativ = 0;
	return(tetra);
}


t_tetra	*get_tetra(t_part *part)
{
	t_elem		*tmp2;
	t_vec		*pos1;
	t_vec		*pos2;
	t_vec		*pos3;
	t_vec		*pos4;
	t_color		*color;
	t_tetra		*tetra;

	pos1 = NULL;
	pos2 = NULL;
	pos3 = NULL;
	pos4 = NULL;
	color = NULL;
	if (!(tetra = init_tetra()))
		return (NULL);
	tmp2 = part->elems;
	while (tmp2)
	{
		if (!ft_strcmp(tmp2->name, "v0"))
		{
			if (!get_new_vec(tmp2, &pos1))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "v1"))
		{
			if (!get_new_vec(tmp2, &pos2))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "v2"))
		{
			if (!get_new_vec(tmp2, &pos3))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "v3"))
		{
			if (!get_new_vec(tmp2, &pos4))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "color"))
		{
			if (!get_new_color(tmp2, &color, OBJECT))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "specular"))
		{
		if (!get_secur_num(tmp2, &(tetra->specular), 0, 100))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "reflection"))
		{
		if (!get_secur_num(tmp2, &(tetra->reflection), 0, 1))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "opacity"))
		{
		if (!get_secur_num(tmp2, &(tetra->opacity), 0, 1))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "ref_index"))
		{
		if (!get_secur_num(tmp2, &(tetra->ref_index), 1, 10))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "is_negativ"))
		{
		if (!get_secur_is(tmp2, &(tetra->is_negativ)))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "texture"))
		{
		if (!get_secur_enum(tmp2, &(tetra->texture)))
				return (NULL);
		}
		else
		{
			return_invalid_arg(tmp2->name);
			return (NULL);
		}
		tmp2 = tmp2->next;
	}
	if (!pos1 || !pos2 || !pos3 || !color || !pos4)
	{
		if (!pos1)
			ft_putendl("'v0' missing");
		if (!pos2)
			ft_putendl("'v1' missing");
		if (!pos3)
			ft_putendl("'v2' missing");
		if (!pos4)
			ft_putendl("'v3' missing");
		if (!color)
			ft_putendl("'color' missing");
	}
	tetra->v0 = *pos1;
	tetra->v1 = *pos2;
	tetra->v2 = *pos3;
	tetra->v3 = *pos4;
	tetra->color = *color;
	free(pos1);
	free(pos2);
	free(pos3);
	free(color);
	return (tetra);

}


t_elips	*init_elips(void)
{
	t_elips	*elips;

	if (!(elips = (t_elips *)malloc(sizeof(t_elips))))
		return (NULL);
	elips->radius = 0;
	elips->center = init_vector(0, 0, 0);
	elips->quad.a = 0;
	elips->quad.b = 0;
	elips->quad.c = 0;
	elips->color = init_color(0, 0, 0);
	elips->specular = 0;
	elips->reflection = 0;
	elips->opacity = 1;
	elips->ref_index = 1;
	elips->is_negativ = 0;
	elips->texture = NONE;
	return (elips);
}

t_scene		*get_objects(t_scene *scene, t_part *part)
{
	t_node	*node;
	t_part	*tmp;
	void	*data;

	if (!(tmp = part->sub_parts))
	{
		ft_putendl("Empty Object\n");
		return (NULL);
	}
	while (tmp)
	{
		data = NULL;
		if (tmp->type == SPHERE)
		{
			if (!(data = get_sphere(tmp)))
			{
				return (NULL);
			}
		}
		else if (tmp->type == CYLINDER)
		{
			if (!(data = get_cylinder(tmp)))
				return (NULL);
		}
		else if (tmp->type == PLANE)
		{
			if (!(data = get_plane(tmp)))
				return (NULL);
		}
		else if (tmp->type == CONE)
		{
			if (!(data = get_cone(tmp)))
				return (NULL);
		}
		else if (tmp->type == ELIPS)
		{
			if (!(data = get_elips(tmp)))
				return (NULL);
		}
		else if (tmp->type == TRIAN)
		{
			if (!(data = get_triangle(tmp)))
				return (NULL);
		}
		else if (tmp->type == PARA)
		{
			if (!(data = get_para(tmp)))
				return (NULL);
		}
		else if (tmp->type == TETRA)
		{
			if (!(data = get_tetra(tmp)))
				return (NULL);
		}
		else
			return (NULL);
		if (!(node = init_node(tmp->type, data, "obj", 0)))
			return (NULL);
		node_add(&(scene->objects), node);
		tmp = tmp->next;
	}
	return (scene);
}
