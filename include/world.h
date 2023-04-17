/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:17:44 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/17 14:42:01 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "lights.h"
# include "shapes.h"

// PERF: use arrays
// t_object	*objects;
// t_light		*lights;
typedef struct s_world
{
	t_list	*objects;
	t_list	*lights;
}	t_world;

typedef struct s_comps
{
	float		t;
	t_object	object;
	t_point		point;
	t_sight		sight;
	t_vector	eyev;
	t_vector	normalv;
	t_bool		inside;
}	t_comps;

t_intersection	*intersect_world(t_world *world, t_ray ray);
t_comps			prepare_computations(t_intersection *intersection, t_ray ray);
t_color			shade_hit(t_world world, t_comps comps);
t_color			color_at(t_world world, t_ray ray);

#endif
