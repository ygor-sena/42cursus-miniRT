/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:19:51 by yde-goes          #+#    #+#             */
/*   Updated: 2023/05/12 11:27:27 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

void	glassy_shape(t_shape *shape)
{
	shape->material.transparency = 1.0;
	shape->material.refractive_index = 1.5;
}
