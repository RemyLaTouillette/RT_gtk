/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 23:46:59 by bhenne            #+#    #+#             */
/*   Updated: 2016/09/19 19:26:58 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _OBJECTS_H
# define _OBJECTS_H

# include <camera.h>
# include <vector.h>

# define NONE		0
# define MARBLE		1
# define CHECKER	2

typedef struct			s_color
{
	double				r;
	double				g;
	double				b;
}						t_color;

typedef struct			s_hit
{
	int					type;
	double				t;
	double				t_max;
	double				dist_from_center;
	double				radius;
	t_vec				pos;
	double				length;
	t_color				color;
	int					bool;
	t_vec				nml;
	t_vec				nml_max;
	int					specular;
	double				reflection;
	double				opacity;
	double				ref_index;
	int					is_negativ;
	int					texture;
	t_vec				dir;
}						t_hit;

typedef pthread_t		t_pthread;
typedef pthread_mutex_t	t_mutex;

typedef	struct			s_iter
{
	int					i;
	int					j;
}						t_iter;

typedef struct			s_env
{
	int					x;
	GtkBuilder			*builder;
	unsigned char		*buf;
	void				*mlx;
	void				*win;
	void				*img;
	t_vec				pos_plan;
	t_cam				cam;
	int					fd;
	double				**tab_noise;
	// UI values
	int				mode; // cartoon or not (0, 1)
	int				filter; // (0, 1, 2)
	int				dof;
	double				focus;
	double				blur;
	t_color				amblight;
	double				ambindex;
	int				loop;

}						t_env;
#endif
