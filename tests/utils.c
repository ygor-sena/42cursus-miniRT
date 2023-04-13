/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:30:07 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/11 14:45:22 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"
#include "materials.h"

t_sphere	sphere_stub(void)
{
	return ((t_sphere){
		.origin = point(0, 0, 0),
		.radius = 1.0,
		.transform = get_identity_matrix(),
		.material = material()
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
