/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 01:31:39 by sduprey           #+#    #+#             */
/*   Updated: 2016/09/29 16:19:59 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SCENE_H
# define _SCENE_H

# define REALISTIC		1
# define CARTOON		2

# include <objects.h>
# include <node.h>

typedef struct	s_scene
{
	int			is_real;
	int			is_dof;
	double		dof;
	double		blur;
	int			filter;
	double		ambient_index;
	t_color		ambient_color;
	double		reflection;
	int			r;
	double		*blur_array;
	t_cam		cam;
	int			w;
	int			h;
	t_node		*objects;
	t_node		*lights;
	int		aa; // 0 = off | 1 = on
	int		aax; // 1 = matrice 33 | 2 = matrice 55 | 3 = matrice 99

}				t_scene;

t_scene			*init_scene(void);
void			free_scene(t_scene **scene);

#endif
