/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 06:31:18 by sduprey           #+#    #+#             */
/*   Updated: 2016/10/04 17:05:12 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void		continue_bmp_info_header(int fd)
{
	int		x;

	x = 1;
	write(fd, &x, 2);
	x = 24;
	write(fd, &x, 2);
	x = 0;
	write(fd, &x, 4);
	write(fd, &x, 4);
	x = 0;
	write(fd, &x, 4);
	write(fd, &x, 4);
	x = 0x00000000;
	write(fd, &x, 4);
	write(fd, &x, 4);
}

void		init_bmp_info_header(int fd)
{
	int		x;

	x = 0x42;
	write(fd, &x, 1);
	x = 0x4D;
	write(fd, &x, 1);
	x = WIDTH * HEIGHT * 24 + 54;
	write(fd, &x, 4);
	x = 0x00000000;
	write(fd, &x, 4);
	x = 54;
	write(fd, &x, 4);
	x = 40;
	write(fd, &x, 4);
	x = WIDTH;
	write(fd, &x, 4);
	x = HEIGHT;
	write(fd, &x, 4);
	continue_bmp_info_header(fd);
}

int			find_file_name(void)
{
	char	*file_name;
	int		i;
	int		fd;

	if (!(file_name = (char *)malloc(sizeof(char) * (17))))
		return (-1);
	file_name = ft_strcpy(file_name, "save_img.bmp");
	i = 1;
	fd = open(file_name, O_WRONLY | O_CREAT | O_EXCL, 0777);
	while (fd == -1 && i < 100)
	{
		file_name = ft_strcpy(file_name, "save_img(");
		file_name = ft_strcat(file_name, ft_itoa(i));
		file_name = ft_strcat(file_name, ").bmp");
		i++;
		fd = open(file_name, O_WRONLY | O_CREAT | O_EXCL, 0777);
	}
	free(file_name);
	return (fd);
}

void		complete_pixel_color(char *data, t_color c)
{
	data[0] = (int)c.b;
	data[1] = (int)c.g;
	data[2] = (int)c.r;
}

void		save_bmp(unsigned char *buf)
{
	int		i;
	int		j;
	t_color	c;
	int		fd;
	char	data[3];

	fd = find_file_name();
	if (fd > 0)
	{
		init_bmp_info_header(fd);
		j = HEIGHT - 1;
		while (j >= 0)
		{
			i = 0;
			while (i < WIDTH)
			{
				c = get_pixel_from_buffer(buf, i, j);
				complete_pixel_color(data, c);
				write(fd, &data, sizeof(data));
				i++;
			}
			j--;
		}
		close(fd);
	}
}
