/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:47:49 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/24 17:00:08 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

t_shape	new_shape(void)
{
	return ((t_shape){
		.transform = get_identity_matrix(),
		.material = material(),
	});
}

t_shape	sphere(void)
{
	t_shape	object;

	object = new_shape();
	object.id = SPHERE;
	object.sphere.origin = point(0, 0, 0);
	object.sphere.radius = 1.0;
	return (object);
}
