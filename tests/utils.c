/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:30:07 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/24 19:47:58 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_world	world_stub(void)
{
	return ((t_world){
		.objects = NULL,
		.lights = NULL,
		.object_count = 0,
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
	t_sphere	*s1;
	t_sphere	*s2;
	t_light		*light;

	w = world_stub();
	w.objects = ft_calloc(sizeof(t_shape), 3);
	w.object_count = 2;
	s1 = sphere_stub();
	s1->material.color = new_color(0.8, 1.0, 0.6);
	s1->material.diffuse = 0.7;
	s1->material.specular = 0.2;
	s2 = sphere_stub();
	s2->transform = scaling(0.5, 0.5, 0.5);
	light = point_light(point(-10, 10, -10), new_color(1, 1, 1));
	s1->radius = 0.5;
	s2->radius = 1.0;
	ft_lstadd_back(&w.lights, ft_lstnew(light));
	w.objects[0].sphere = *s1;
	w.objects[1].sphere = *s2;
	return (w);
}

t_sphere	*sphere_stub()
{
	t_sphere	*s;

	s = oom(malloc(sizeof(t_sphere)));
	s->origin = point(0, 0, 0);
	s->radius = 1.0;
	s->transform = get_identity_matrix();
	s->material = material();
	return (s);
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
