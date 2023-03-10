/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 21:36:19 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/10/18 21:01:13 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

void	flag_left(t_param *spec)
{
	spec->flags[LEFT] = TRUE;
	spec->flags[ZERO] = FALSE;
}

void	flag_padding(t_param *spec)
{
	if (spec->flags[LEFT])
		return ;
	spec->flags[ZERO] = TRUE;
}

void	flag_showsign(t_param *spec)
{
	spec->flags[PLUS] = TRUE;
	spec->flags[SPACE] = FALSE;
}

void	flag_space(t_param *spec)
{
	if (spec->flags[PLUS])
		return ;
	spec->flags[SPACE] = TRUE;
}

void	flag_hash(t_param *spec)
{
	spec->flags[HASH] = TRUE;
}
