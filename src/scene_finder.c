/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_finder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 17:58:57 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/19 21:31:46 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static int	file_counter(char *path)
{
	DIR				*dir;
	struct dirent	*file;
	int				n;

	n = 0;
	if ((dir = opendir(path)) == NULL)
		return (n);
	else
	{
		while ((file = readdir(dir)) != NULL)
		{
			if (ft_strcmp(file->d_name, ".") && ft_strcmp(file->d_name, "..") &&
				file->d_name[0] != '.')
				n++;
		}
	}
	closedir(dir);
	return (n);
}

char		**scene_finder(char *path)
{
	DIR				*dir;
	struct dirent	*file;
	char			**scenes;
	int				n;
	int				i;

	if ((dir = opendir(path)) == NULL)
		return (NULL);
	else
	{
		n = file_counter(path);
		if (n < 1 || !(scenes = (char **)malloc(sizeof(char *) * (n + 1))))
			return (NULL);
		i = 0;
		while ((file = readdir(dir)) != NULL)
		{
			if (ft_strcmp(file->d_name, ".") && ft_strcmp(file->d_name, "..") &&
				file->d_name[0] != '.')
				scenes[i++] = ft_strdup(file->d_name);
		}
		scenes[i] = NULL;
	}
	closedir(dir);
	return (scenes);
}
