/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guards.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:26:40 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/16 11:10:34 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

void	*oom(void *ptr)
{
	if (ptr == NULL)
	{
		perror("minirt");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

t_bool	is_equal_float(float a, float b)
{
	if (fabsf(a - b) < 0.00001)
		return (TRUE);
	return (FALSE);
}

void	swap(float *t1, float *t2)
{
	float	tmp;

	tmp = *t1;
	*t1 = *t2;
	*t2 = tmp;
}
