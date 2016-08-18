/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 01:43:09 by nbelouni          #+#    #+#             */
/*   Updated: 2016/08/17 04:00:53 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdio.h>

t_color		diffuse_shadow(t_hit curr_px, t_ray *light_ray, t_light *light, t_hit tmp_content)
{
	double	angle;
	double	coef;
	t_color	tmp_color;

	angle = fabs(dot_product(light_ray->dir, curr_px.point_norm));
	coef = 1 - tmp_content.opacity;
	tmp_color.r = curr_px.color.r * angle * light->color.r * coef;
	tmp_color.g = curr_px.color.g * angle * light->color.g * coef;
	tmp_color.b = curr_px.color.b * angle * light->color.b * coef;
	return (tmp_color);
}

t_color		diffuse_light(t_hit curr_px, t_ray *light_ray, t_light *light)
{
	double	angle;
	double	coef;
	t_color	tmp_color;

	angle = dot_product(light_ray->dir, curr_px.point_norm);
	angle /= get_length(light_ray->dir);
	angle /= get_length(curr_px.point_norm);
	tmp_color = init_color(0, 0, 0);

	coef = curr_px.opacity;
	if (angle < 0)
	{
		angle = -angle;
		if (curr_px.opacity >= 0.5)
			coef = 1 - curr_px.opacity;
	}
	tmp_color.r = curr_px.color.r * angle * light->color.r * coef;
	tmp_color.g = curr_px.color.g * angle * light->color.g * coef;
	tmp_color.b = curr_px.color.b * angle * light->color.b * coef;
	return (tmp_color);
}

t_color		specular_light(t_hit curr_px, t_vec reflection, t_light *light, t_ray *cam_ray)
{
	t_color	tmp_color;
	double	spec;
	double coef;

	if (curr_px.opacity == 1)
		spec = pow(dot_product(normalize(cam_ray->dir), normalize(reflection)), curr_px.specular + 1);
	else
		spec = pow(dot_product(normalize(cam_ray->dir), normalize(reflection)), curr_px.specular);

	if (spec < 0)
		coef = fabs(spec) * curr_px.opacity;
	else
		coef = 1;
	tmp_color.r = spec * light->color.r * coef;
	tmp_color.g = spec * light->color.g * coef;
	tmp_color.b = spec * light->color.b * coef;
	return (tmp_color);
}

t_color		apply_light(t_scene *scene, t_hit curr_pixel, t_ray *cam_ray)
{
	t_hit		tmp_content;
	t_node		*tmp_light;
	t_node		*tmp_object;
	t_ray		*light_ray;
	t_vec		obj_pos;
	t_color		tmp_color;
	t_vec		tmp_light_ray;
	int			shadow;
	t_vec		reflection;
	t_hit		closest_hit;
	t_hit		negativ_hit;

	t_vec		light_look;
	double		angle2;

	tmp_color.r = tmp_color.g = tmp_color.b = 0;
	tmp_light = scene->lights;
	obj_pos = vec_add(cam_ray->pos, scalar_product(cam_ray->dir, curr_pixel.t));
	if (!(light_ray = (t_ray *)malloc(sizeof(t_ray))))
		return (curr_pixel.color);
	light_ray->pos = obj_pos;
	while (tmp_light)
	{
		shadow = 0;
		if (((t_light *)(tmp_light->data))->type == PARALLEL)
		{
			light_ray->dir = normalize(scalar_product(((t_light *)(tmp_light->data))->pos, -1));
			light_ray->length = 100;
		}
		else
		{
			tmp_light_ray = vec_sub(light_ray->pos, ((t_light *)(tmp_light->data))->pos);
			light_ray->length = get_length(tmp_light_ray);
			light_ray->dir = normalize(tmp_light_ray);
		}

		tmp_object = scene->objects;
		tmp_content = init_hit();
		closest_hit = init_hit();
		negativ_hit = init_hit();
		while (tmp_object)
		{
			if (tmp_object->type == SPHERE)
				tmp_content = is_sphere_hit(light_ray, (t_sphere *)tmp_object->data);
			else if (tmp_object->type == CYLINDER)
				tmp_content = is_cylinder_hit(light_ray, (t_cylinder *)tmp_object->data);
			else if (tmp_object->type == PLANE)
				tmp_content = is_plane_hit(light_ray, (t_plane *)tmp_object->data);
			else if (tmp_object->type == CONE)
				tmp_content = is_cone_hit(light_ray, (t_cone *)tmp_object->data);
			else if (tmp_object->type == ELIPS)
				tmp_content = is_elips_hit(light_ray, (t_elips *)tmp_object->data);
//			printf("CLOSE : bool : %d, t : %f, t_max : %f, is_neg : %d\n", tmp_content.bool, tmp_content.t, tmp_content.t_max, tmp_content.is_negativ);
			if (tmp_content.bool == 1)
			{
				if (tmp_content.is_negativ == 1)
				{
					negativ_hit = tmp_content;
				}
				else if (tmp_content.t > 0.0 && tmp_content.t <= light_ray->length)
				{
					shadow = 1;
					if (closest_hit.bool == 0 || tmp_content.opacity >= closest_hit.opacity)
					{
//				
						closest_hit = tmp_content;
					}
				}
			}
			tmp_object = tmp_object->next;
		}
//			printf("NEG : bool : %d, t : %f, t_max : %f\n", negativ_hit.bool, negativ_hit.t, negativ_hit.t_max);
//			printf("CLOSE : bool : %d, t : %f, t_max : %f\n", closest_hit.bool, closest_hit.t, closest_hit.t_max);
//			printf("CURR: bool : %d, t : %f, t_max : %f\n\n", curr_pixel.bool, curr_pixel.t, curr_pixel.t_max);
//			sleep(1);
		if (negativ_hit.bool == 1)// && negativ_hit.t > 0)
		{
//			printf("type : %d, is_neg : %d\n", curr_pixel.type, curr_pixel.is_negativ);
//			if (closest_hit.type == SPHERE)
//			{
//			}
	//		if (/*closest_hit.t <= closest_hit.t_max && negativ_hit.t <= negativ_hit.t_max &&*/ closest_hit.t <= closest_hit.t_max)
//			{
//				printf("__________1\n");
//				closest_hit.t = negativ_hit.t_max;
//				closest_hit.point_norm = curr_pixel.point_norm;//scalar_product(negativ_hit.point_norm, 1);
//				if (negativ_hit.t_max < closest_hit.t_max)
				
				if (negativ_hit.t > 0.0 && negativ_hit.t <= light_ray->length &&
				(negativ_hit.t < closest_hit.t || negativ_hit.t_max < closest_hit.t))// && negativ_hit.t_max > closest_hit.t_max)
					shadow = 0;
//				else if (closest_hit.type == SPHERE)
//				{
//					printf("NEG : t : %f, t_max : %f\n", negativ_hit.t, negativ_hit.t_max);
//					printf("CLOSE : t : %f, t_max : %f\n", closest_hit.t, closest_hit.t_max);
//					sleep(3);
//				}

				closest_hit = init_hit();
//			}
		}

		if (((t_light *)(tmp_light->data))->type == DIRECT)
		{
			light_look = vec_sub(((t_light *)(tmp_light->data))->look_at, ((t_light *)(tmp_light->data))->pos);
			angle2 = dot_product(light_ray->dir, light_look);
			angle2 /= get_length(light_ray->dir);
			angle2 /= get_length(light_look);
		}
		else
		{
			angle2 = 1;
		}

		if (((t_light *)(tmp_light->data))->type != DIRECT || acos(angle2) < ((t_light *)(tmp_light->data))->angle)
		{
			if (shadow == 0 || curr_pixel.opacity < 1)
			{
				tmp_color = add_color(tmp_color, diffuse_light(curr_pixel, light_ray, ((t_light *)(tmp_light->data))));
			}
			else if (closest_hit.opacity < 1 && shadow == 1)
				tmp_color = add_color(tmp_color, diffuse_shadow(curr_pixel, light_ray, ((t_light *)(tmp_light->data)), closest_hit));
//			else if (shadow == 1)
//				return (init_color(123, 123, 123));
			reflection = vec_sub(scalar_product(curr_pixel.point_norm, dot_product(light_ray->dir, curr_pixel.point_norm) * 2), light_ray->dir);
			if ((shadow == 0 || closest_hit.opacity < 1) && curr_pixel.t != curr_pixel.t_max)
				tmp_color = add_color(tmp_color, (specular_light(curr_pixel, reflection, ((t_light *)(tmp_light->data)), cam_ray)));
		}
		tmp_light = tmp_light->next;
	}
	free(light_ray);
	curr_pixel.color = tmp_color;
	return (curr_pixel.color);
}
