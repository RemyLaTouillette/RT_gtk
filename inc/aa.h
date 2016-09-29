/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aa.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/04 00:11:00 by sduprey           #+#    #+#             */
/*   Updated: 2016/09/29 19:43:39 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _AA_H
# define _AA_H

# include <objects.h>

# define SEPIA		1
# define NOIR_BLANC	2

void	sepia_filter(void *b, void *n, int f, t_iter iter);
void	aa(void *b, void *n, int u, int d);

#endif
