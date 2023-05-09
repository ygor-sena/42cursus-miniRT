/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:13:05 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/09 12:38:09 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

Test(camera, new_camera)
{
	int			hsize;
	int			vsize;
	t_camera	c;
	t_matrix	identity;

	hsize = 160;
	vsize = 120;
	c = new_camera(hsize, vsize, M_PI_2);
	cr_assert(eq(i32, c.hsize, hsize));
	cr_assert(eq(i32, c.vsize, vsize));
	cr_assert_float_eq(c.field_of_view, M_PI_2, EPSILON);

	identity = get_identity_matrix();
	assert_matrix_equal(c.transform, identity);
}

Test(camera, pixel_size_on_horizontal_canvas)
{
	t_camera	c;

	c = new_camera(200, 125, M_PI_2);
	cr_assert_float_eq(c.pixel_size, 0.01, EPSILON);
}

Test(camera, pixel_size_on_vertical_canvas)
{
	t_camera	c;

	c = new_camera(125, 200, M_PI_2);
	cr_assert_float_eq(c.pixel_size, 0.01, EPSILON);
}

Test(camera, ray_through_the_center_of_the_canvas)
{
	t_camera	c;
	t_ray		r;

	c = new_camera(201, 101, M_PI_2);
	r = ray_for_pixel(&c, 100, 50);
	cr_assert_float_eq(r.origin.x, 0, EPSILON);
	cr_assert_float_eq(r.origin.y, 0, EPSILON);
	cr_assert_float_eq(r.origin.z, 0, EPSILON);
	cr_assert_float_eq(r.direction.x, 0, EPSILON);
	cr_assert_float_eq(r.direction.y, 0, EPSILON);
	cr_assert_float_eq(r.direction.z, -1, EPSILON);
}

Test(camera, ray_through_the_corner_of_the_canvas)
{
	t_camera	c;
	t_ray		r;

	c = new_camera(201, 101, M_PI_2);
	r = ray_for_pixel(&c, 0, 0);
	cr_assert_float_eq(r.origin.x, 0, EPSILON);
	cr_assert_float_eq(r.origin.y, 0, EPSILON);
	cr_assert_float_eq(r.origin.z, 0, EPSILON);
	cr_assert_float_eq(r.direction.x, 0.66519, EPSILON);
	cr_assert_float_eq(r.direction.y, 0.33259, EPSILON);
	cr_assert_float_eq(r.direction.z, -0.66851, EPSILON);
}

Test(camera, ray_with_transformed_camera)
{
	t_camera	c;
	t_ray		r;

	c = new_camera(201, 101, M_PI_2);
	c.transform = multiply_mx_mx(rotation_y(M_PI_4), translation(0, -2, 5));
	r = ray_for_pixel(&c, 100, 50);
	cr_assert_float_eq(r.origin.x, 0, EPSILON);
	cr_assert_float_eq(r.origin.y, 2, EPSILON);
	cr_assert_float_eq(r.origin.z, -5, EPSILON);
	cr_assert_float_eq(r.direction.x, sqrt(2)/2, EPSILON);
	cr_assert_float_eq(r.direction.y, 0, EPSILON);
	cr_assert_float_eq(r.direction.z, -sqrt(2)/2, EPSILON);
}

// NOTE: This test does not pass in the Git environment.
// Test(camera, rendering_a_world_with_a_camera)
// {
// 	t_world		w;
// 	t_camera	c;
// 	t_tuple		from;
// 	t_tuple		to;
// 	t_tuple		up;
// 	t_canvas	image;
// 	int			result;
// 	int			expected;
//
// 	w = default_world();
// 	from = point(0, 0, -5);
// 	to = point(0, 0, 0);
// 	up = vector(0, 1, 0);
// 	c = new_camera(11, 11, M_2_PI);
// 	c.transform = view_transform(from, to, up);
// 	render_scene(&image, &w, &c);
//
// 	result = pixel_at(&image, 5, 5);
// 	expected = rgb(new_color(0.38066, 0.47583, 0.2855));
// 	cr_assert(eq(i32, result, expected));
//
// 	mlx_destroy_image(image.mlx_ptr, image.img_ptr);
// 	mlx_destroy_display(image.mlx_ptr);
// 	free(image.mlx_ptr);
// }
