/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:11:56 by yde-goes          #+#    #+#             */
/*   Updated: 2023/04/25 16:45:16 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lights.h"

t_light	point_light(t_point position, t_color intensity)
{
	return ((t_light){
		.position = position,
		.intensity = intensity,
		.in_shadow = FALSE
	});
}
