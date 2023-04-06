/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:30:07 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/06 11:02:36 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

t_sphere	sphere_stub(void)
{
	return ((t_sphere){
		.origin = point(0, 0, 0),
		.radius = 1.0,
		.transform = get_identity_matrix(),
	});
}

t_bool	compare_spheres(t_sphere a, t_sphere b)
{
	return (
		a.origin.x == b.origin.x
		&& a.origin.y == b.origin.y
		&& a.origin.z == b.origin.z
		&& a.radius == b.radius
	);
}
