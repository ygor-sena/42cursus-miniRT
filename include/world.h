/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:17:44 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/14 17:18:16 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "lights.h"
# include "shapes.h"

// PERF: use arrays
typedef struct s_world
{
	t_list	*objects;
	t_list	*lights;
}	t_world;

t_intersection	*intersect_world(t_world *world, t_ray ray);

#endif
