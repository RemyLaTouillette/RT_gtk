/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 16:09:06 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/22 16:20:03 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLER_H
# define ERROR_HANDLER_H

/*
**  crit = 0 -> exit
**         1 -> no img
**         2 -> warning
*/

typedef struct	s_error
{
	int			crit;
	char		*msg;
}				t_error;

char			*join(char *s1, char *s2, char *s3);
void			print_error(char *msg, int crit);

#endif
