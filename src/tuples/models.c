/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   models.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:53:44 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/24 11:15:15 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuples.h"

t_tuple	tuple(double x, double y, double z, double w)
{
	return ((t_tuple){x, y, z, w});
}

t_tuple	point(double x, double y, double z)
{
	return (tuple(x, y, z, 1.0));
}

t_tuple	vector(double x, double y, double z)
{
	return (tuple(x, y, z, 0.0));
}
