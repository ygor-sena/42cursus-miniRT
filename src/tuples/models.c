/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   models.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:53:44 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/03/17 12:54:07 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuples.h"

t_tuple	tuple(float x, float y, float z, float w)
{
	return ((t_tuple){x, y, z, w});
}

t_tuple	point(float x, float y, float z)
{
	return (tuple(x, y, z, 1.0));
}

t_tuple	vector(float x, float y, float z)
{
	return (tuple(x, y, z, 0.0));
}
