/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:47:49 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/25 21:59:19 by mdias-ma         ###   ########.fr       */
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

void	set_transform(t_shape *shape, t_matrix transform)
{
	shape->transform = transform;
}
