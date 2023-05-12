/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:30:07 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/12 14:55:28 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_world	world_stub(void)
{
	return ((t_world){
		.object_count = 0,
		.objects = NULL,
		.lights = NULL,
		.xs = NULL
	});
}

void	assert_matrix_equal(t_matrix a, t_matrix b)
{
	for (size_t i = 0; i < a.size; i++)
	{
		for (size_t j = 0; j < a.size; j++)
			cr_assert_float_eq(a.matrix[i][j], b.matrix[i][j], EPSILON);
	}
}

t_world	default_world(void)
{
	t_world		w;
	t_shape		s1;
	t_shape		s2;

	w = world_stub();
	w.lights = calloc(sizeof(t_light), 1);
	w.objects = calloc(sizeof(t_shape), 2);
	w.object_count = 2;

	s1 = new_sphere();
	s1.material = material();
	s1.material.color = new_color(0.8, 1.0, 0.6);
	s1.material.diffuse = 0.7;
	s1.material.specular = 0.2;
	s1.sphere.radius = 0.5;

	s2 = new_sphere();
	s2.material = material();
	s2.transform = scaling(0.5, 0.5, 0.5);
	s2.sphere.radius = 1.0;

	w.lights[0] = point_light(point(-10, 10, -10), new_color(1, 1, 1));
	w.objects[0] = s1;
	w.objects[1] = s2;
	return (w);
}

//TODO: an "add_light_to_world()" maybe will be needed to test multispot lights
void	add_shape_to_world(t_world *world, t_shape shape)
{
    t_shape *new_objects;
	
	new_objects = ft_calloc(world->object_count + 1, sizeof(t_shape));
    ft_memmove(new_objects, world->objects,
			world->object_count * sizeof(t_shape));
    new_objects[world->object_count] = shape;
    free(world->objects);
    world->objects = new_objects;
    world->object_count++;
}

t_bool	compare_spheres(t_sphere *a, t_sphere *b)
{
	return (
		a->origin.x == b->origin.x
		&& a->origin.y == b->origin.y
		&& a->origin.z == b->origin.z
		&& a->radius == b->radius
	);
}

t_bool	compare_tuples(t_tuple a, t_tuple b)
{
	return (
		a.x == b.x
		&& a.y == b.y
		&& a.z == b.z
	);
}
