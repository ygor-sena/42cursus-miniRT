/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:16:40 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/22 14:42:45 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "rays.h"
#include "tuples.h"

static void	set_pixel_size(t_camera *c);

t_camera	new_camera(float hsize, float vsize, float field_of_view)
{
	t_camera	camera;

	camera.hsize = hsize;
	camera.vsize = vsize;
	camera.field_of_view = field_of_view;
	camera.transform = get_identity_matrix();
	camera.inverse = inverse(camera.transform);
	set_pixel_size(&camera);
	return (camera);
}

t_ray	ray_for_pixel(t_camera *camera, float px, float py)
{
	float	world_x;
	float	world_y;
	t_tuple	pixel;
	t_tuple	origin;
	t_tuple	direction;

	world_x = camera->half_width - (px + 0.5) * camera->pixel_size;
	world_y = camera->half_height - (py + 0.5) * camera->pixel_size;
	pixel = multiply_tp_mx(camera->inverse, point(world_x, world_y, -1));
	origin = multiply_tp_mx(camera->inverse, point(0, 0, 0));
	direction = normalize(subtract(pixel, origin));
	return (new_ray(origin, direction));
}

static void	set_pixel_size(t_camera *camera)
{
	float	half_view;
	float	aspect;

	half_view = tanf(camera->field_of_view / 2);
	aspect = camera->hsize / camera->vsize;
	if (aspect >= 1)
	{
		camera->half_width = half_view;
		camera->half_height = half_view / aspect;
	}
	else
	{
		camera->half_width = half_view * aspect;
		camera->half_height = half_view;
	}
	camera->pixel_size = (camera->half_width * 2) / camera->hsize;
}
