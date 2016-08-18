/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_buffer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 02:06:46 by sduprey           #+#    #+#             */
/*   Updated: 2016/08/17 04:11:23 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	_IMAGE_BUFFER_H
# define _IMAGE_BUFFER_H


unsigned char	*new_image_buffer(int width, int height);
void			put_pixel_on_buffer(unsigned char *buf, int x, int y, t_color c);
t_color			get_pixel_from_buffer(unsigned char *buf, int x, int y);

#endif
