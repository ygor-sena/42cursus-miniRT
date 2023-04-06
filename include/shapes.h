/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:05:41 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/06 10:36:54 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "rays.h"

typedef struct s_sphere
{
	t_point		origin;
	float		radius;
	t_matrix	transform;
}	t_sphere;

typedef union u_object
{
	t_sphere	sphere;
}	t_object;

typedef struct s_intersection
{
	float					t;
	t_object				object;
	struct s_intersection	*next;
}	t_intersection;

typedef struct s_hit_points
{
	float	t1;
	float	t2;
	float	delta;
}	t_hit_points;

/* spheres.c */
t_intersection	*intersect(t_sphere sphere, t_ray ray);
void			set_transform(t_sphere *sphere, t_matrix transform);

/* intersections.c */
t_intersection	*intersection(float t, t_sphere sphere);
void			insert_intersection(t_intersection **xs, t_intersection *i);
t_intersection	*hit(t_intersection *xs);
int				intersection_count(t_intersection *xs);
void			erase_intersections(t_intersection **xs);

#endif
