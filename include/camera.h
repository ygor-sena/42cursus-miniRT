/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:29:11 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/19 16:48:18 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "tuples.h"
# include "matrices.h"
# include "rays.h"

typedef struct s_camera
{
	float		hsize;
	float		vsize;
	float		field_of_view;
	float		half_width;
	float		half_height;
	float		pixel_size;
	t_matrix	transform;
}	t_camera;

t_matrix	view_transform(t_tuple from, t_tuple to, t_tuple up);
t_camera	new_camera(float hsize, float vsize, float field_of_view);
t_ray		ray_for_pixel(t_camera *camera, float px, float py);

#endif
