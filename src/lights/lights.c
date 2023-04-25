/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:11:56 by yde-goes          #+#    #+#             */
/*   Updated: 2023/04/25 12:39:43 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lights.h"

t_light	point_light(t_tuple position, t_color intensity)
{
	return ((t_light){
		.position = position,
		.intensity = intensity,
	});
}
