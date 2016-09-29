/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/25 17:53:36 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/28 18:07:16 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _THREAD_H
# define _THREAD_H

# include <scene.h>
# include <pthread.h>

typedef struct			s_thread
{
	t_scene				*scene;
	unsigned char		*buf;
	unsigned char		*buf_tmp;
	int					y_start;
	int					y_end;
	t_pthread			pth;
	t_mutex				*mutex;
	t_env				*env;
}						t_thread;

#endif
