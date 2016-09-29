/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_buffer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 02:06:46 by sduprey           #+#    #+#             */
/*   Updated: 2016/09/29 19:45:22 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _IMAGE_BUFFER_H
# define _IMAGE_BUFFER_H

unsigned char	*new_image_buffer(void);
void			put_pixel_on_buffer(unsigned char *b, int x, int y, t_color c);
t_color			get_pixel_from_buffer(unsigned char *buf, int x, int y);

void			mount_image(t_env *e, t_scene *s);
void			threads_effects(t_env *e);

void			draw_blur_effect(unsigned char *ref, t_thread *t, int size,
		t_iter iter);
void			draw_dof_effect(unsigned char *ref, t_thread *t, int size,
		t_iter iter);
void			draw_filter_effect(unsigned char *ref, t_thread *t, int size,
		t_iter iter);

#endif
