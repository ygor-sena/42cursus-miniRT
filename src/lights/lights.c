/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:11:56 by yde-goes          #+#    #+#             */
/*   Updated: 2023/04/13 20:29:13 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lights.h"

t_light	*point_light(t_tuple point, t_color intensity)
{
	t_light	*light;

	light = oom(malloc(sizeof(t_light)));
	light->position = point;
	light->intensity = intensity;
	return (light);
}
