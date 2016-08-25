/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/25 17:53:36 by tlepeche          #+#    #+#             */
/*   Updated: 2016/08/25 18:48:47 by tlepeche         ###   ########.fr       */
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
	int					y_start;
	int					y_end;
	t_pthread			pth;
	t_mutex				*mutex;
	t_env				*env;
}						t_thread;

#endif
