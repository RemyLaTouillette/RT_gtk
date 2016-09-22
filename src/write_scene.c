/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 19:08:18 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/22 18:41:08 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

#include <stdio.h>
void		write_vector(t_vec v, char *name)
{
	g_print("\t\t- %s:\t%f %f %f\n", name, v.x, v.y, v.z);
}

void		print_camera(t_cam *c)
{
	write_vector(c->ray.pos, "pos");
	write_vector(c->ray.dir, "dir");
	write_vector(c->look_at, "look_at");
	g_print("\t\t- w: %f\n", c->w);
	g_print("\t\t- h: %f\n", c->h);
	g_print("\t\t- d: %f\n", c->d);
}


void		write_light(t_light	*light)
{
	g_print("\t\t- type : %d\n", light->type);
	write_vector(light->pos, "pos");
	write_vector(light->look_at, "look_at");
	g_print("\t\t- color : %f, %f, %f\n", light->color.r, light->color.g, light->color.b);
	g_print("\t\t- angle : %f\n", light->angle);
}

void		write_sphere(t_sphere *s)
{
	g_print("\t\t- radius : %f\n", s->radius);
	write_vector(s->center, "center");
	g_print("\t\t- color : %f, %f, %f\n", s->color.r, s->color.g, s->color.b);
	g_print("\t\t- specular : %f\n", s->specular);
	g_print("\t\t- reflection : %f\n", s->reflection);
	g_print("\t\t- opacity : %f\n", s->opacity);
	g_print("\t\t- ref_index : %f\n", s->ref_index);
	g_print("\t\t- is_negativ : %d\n", s->is_negativ);
	g_print("\t\t- texture : %d\n", s->texture);
}

void		write_elips(t_elips *s)
{
	g_print("\t\t- radius : %f\n", s->radius);
	write_vector(s->center, "center");
	g_print("\t\t- color : %f, %f, %f\n", s->color.r, s->color.g, s->color.b);
	g_print("\t\t- specular : %f\n", s->specular);
	g_print("\t\t- reflection : %f\n", s->reflection);
	g_print("\t\t- opacity : %f\n", s->opacity);
	g_print("\t\t- ref_index : %f\n", s->ref_index);
	g_print("\t\t- is_negativ : %d\n", s->is_negativ);
	g_print("\t\t- texture : %d\n", s->texture);
}

void		write_plane(t_plane *s)
{
	write_vector(s->pos, "pos");
	write_vector(s->normal, "normal");
	g_print("\t\t- color : %f, %f, %f\n", s->color.r, s->color.g, s->color.b);
	g_print("\t\t- specular : %f\n", s->specular);
	g_print("\t\t- reflection : %f\n", s->reflection);
	g_print("\t\t- opacity : %f\n", s->opacity);
	g_print("\t\t- ref_index : %f\n", s->ref_index);
	g_print("\t\t- is_negativ : %d\n", s->is_negativ);
	g_print("\t\t- texture : %d\n", s->texture);
}

void		write_cylinder(t_cylinder *s)
{
	g_print("\t\t- radius : %f\n", s->radius);
	write_vector(s->pos, "pos");
	write_vector(s->dir, "dir");
	g_print("\t\t- color : %f, %f, %f\n", s->color.r, s->color.g, s->color.b);
	g_print("\t\t- length : %f\n", s->length);
	g_print("\t\t- specular : %f\n", s->specular);
	g_print("\t\t- reflection : %f\n", s->reflection);
	g_print("\t\t- opacity : %f\n", s->opacity);
	g_print("\t\t- ref_index : %f\n", s->ref_index);
	g_print("\t\t- is_negativ : %d\n", s->is_negativ);
	g_print("\t\t- texture : %d\n", s->texture);
}

void		write_cone(t_cone *s)
{
	g_print("\t\t- radius : %f\n", s->r);
	write_vector(s->pos, "pos");
	write_vector(s->dir, "dir");
	g_print("\t\t- color : %f, %f, %f\n", s->color.r, s->color.g, s->color.b);
	g_print("\t\t- length : %f\n", s->len);
	g_print("\t\t- specular : %f\n", s->specular);
	g_print("\t\t- reflection : %f\n", s->reflection);
	g_print("\t\t- opacity : %f\n", s->opacity);
	g_print("\t\t- ref_index : %f\n", s->ref_index);
	g_print("\t\t- is_negativ : %d\n", s->is_negativ);
	g_print("\t\t- texture : %d\n", s->texture);
}

void		write_scene(t_scene s)
{
	t_node	*tmp;

	g_print("SCENE [%dx%d]\n", s.w, s.h);
	g_print(" - cartoon : %d\n\n", s.is_real);
	g_print("\tCAMERA:\n");
	print_camera(&(s.cam));
	g_print("\tNODES:\n ");
	if (s.objects == NULL)
	{
		g_print("\t\t- NULL\n");
	}
	else
	{
		tmp = s.objects;
		while (tmp != NULL)
		{
			g_print("\t%s :\n", tmp->name);
			if (tmp->type == SPHERE)
				write_sphere((t_sphere *)(tmp->data));
			if (tmp->type == CYLINDER)
				write_cylinder((t_cylinder *)(tmp->data));
			if (tmp->type == PLANE)
				write_plane((t_plane *)(tmp->data));
			if (tmp->type == CONE)
				write_cone((t_cone *)(tmp->data));
			if (tmp->type == ELIPS)
				write_elips((t_elips *)(tmp->data));
			tmp = tmp->next;
		}
	}
	if (s.lights == NULL)
	{
		g_print("\t\t- NULL\n");
	}
	else
	{
		tmp = s.lights;
		while (tmp != NULL)
		{
			g_print("\t- %s :\n", tmp->name);
			write_light((t_light *)(tmp->data));
			tmp = tmp->next;
		}
	}
}
