/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spheres.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:05:41 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/06 09:20:16 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERES_H
# define SPHERES_H

# include "matrices.h"
# include "tuples.h"

typedef t_tuple	t_point;
typedef t_tuple	t_vector;

typedef struct s_ray
{
	t_point		origin;
	t_vector	direction;
}	t_ray;

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

/* rays.c */
t_ray			new_ray(t_point origin, t_vector direction);
t_point			position(t_ray ray, float distance);
t_ray			transform(t_ray ray, t_matrix matrix);

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
