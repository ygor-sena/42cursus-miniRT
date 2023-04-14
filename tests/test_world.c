/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:55:26 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/14 17:29:42 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "utils.h"

/* Should return a empty world, containing no objects and no light source. */
Test(world, creating_a_world)
{
	t_world	w;

	w = world_stub();
	cr_assert(eq(ptr, w.objects, NULL));
	cr_assert(eq(ptr, w.lights, NULL));
}

Test(world, the_default_world)
{
	t_world		w;
	t_sphere	*s1;
	t_sphere	*s2;
	t_light		*light;
	t_light		*w_light;

	light = point_light(point(-10, 10, -10), new_color(1, 1, 1));
	w = default_world();

	w_light = w.lights->content;
	cr_assert(eq(flt, w_light->position.x, light->position.x));
	cr_assert(eq(flt, w_light->position.y, light->position.y));
	cr_assert(eq(flt, w_light->position.z, light->position.z));
	cr_assert(eq(flt, w_light->intensity.red, light->intensity.red));
	cr_assert(eq(flt, w_light->intensity.green, light->intensity.green));
	cr_assert(eq(flt, w_light->intensity.blue, light->intensity.blue));

	s1 = w.objects->content;
	cr_assert(eq(flt, s1->radius, 0.5));
	s2 = w.objects->next->content;
	cr_assert(eq(flt, s2->radius, 1.0));
}

Test(world, intersect_a_world_with_a_ray)
{
	t_world			w;
	t_ray			r;
	t_intersection	*xs;
	t_intersection	*s;

	xs = NULL;
	w = default_world();
	r = new_ray(point(0, 0, -5), vector(0, 0, 1));
	xs = intersect_world(&w, r);

	cr_assert(eq(i32, intersection_count(xs), 4));
	s = xs;
	cr_assert(eq(flt, s->t, 4));
	s = s->next;
	cr_assert(eq(flt, s->t, 4.5));
	s = s->next;
	cr_assert(eq(flt, s->t, 5.5));
	s = s->next;
	cr_assert(eq(flt, s->t, 6));
	erase_intersections(&xs);
}
