/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blur.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/23 13:26:24 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/17 16:20:33 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLUR_H
# define BLUR_H

# include <rtv1.h>

typedef struct	s_blur
{
	int			p_obj;
	double		t;
}				t_blur;

t_color			mix_color(t_color *mixed_color, int n_color);
t_color			*new_color_array(int blur_lvl);

#endif
