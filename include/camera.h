/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:29:11 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/06/16 13:39:48 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// @file camera.h
#ifndef CAMERA_H
# define CAMERA_H

# include "tuples.h"
# include "matrices.h"
# include "rays.h"

/**
 * ABOUT THE HEADER CAMERA.H
 *
 * This header contains all functions regarding camera implementation.
 */

/**
 * @brief The structure of type t_camera contains the necessary information for
 *        camera configuration, rendering and transformation.
 * @param hsize Stores the horizontal size (in pixels).
 * @param vsize Stores the vertical size (in pixels).
 * @param field_of_view This field stores angle that describes how much the
 *                      camera can see. When the field of view is small, the
 *                      view will be "zoomed in", magnifying a smaller area of
 *                      the scene.
 * @param half_width Stores the camera's half hsize value.
 * @param half_height Stores the camera's half vsize value.
 * @param pixel_size Stores the camera's pixel size calculated from half_width
 *                   and hsize values.
 * @param transform Stores the transformation matrix for the camera.
 * @param inverse Stores the inverse matrix for the camera.
 * @param transpose Stores the transpose matrix for the camera.
 */
typedef struct s_camera
{
	float		hsize;
	float		vsize;
	float		field_of_view;
	float		half_width;
	float		half_height;
	float		pixel_size;
	t_matrix	transform;
	t_matrix	inverse;
	t_matrix	transpose;
}	t_camera;

/* ************************************************************************** */
/*                             VIEW_TRANSFORM.C                               */
/* ************************************************************************** */

/**
 * @brief Computes the view transformation matrix given the position of the
 *        camera and the point to look at.
 *
 * This function returns a transformation matrix that orients the world
 * relative to the camera's eye. You specify the position of the camera with
 * the `from` parameter, the point to look at with the `to` parameter,
 * and a vector indicating which direction is up with the `up` parameter.
 *
 * @param from The position of the camera in the world.
 * @param to The point in the world to look at.
 * @param up A vector indicating which direction is up.
 * @return Returns the view transformation matrix.
 */
t_matrix	view_transform(t_point from, t_point to, t_vector up);

/* ************************************************************************** */
/*                                 CAMERA.C                                   */
/* ************************************************************************** */

/**
 * @brief Creates a new camera with the given attributes.
 *
 * This function creates a virtual camera that can be used to "take pictures"
 * of a three-dimensional scene. The camera is defined by its horizontal and
 * vertical size in pixels, the field of view angle, and a transform matrix
 * that orients the world relative to the camera.
 *
 * @param hsize The horizontal size (in pixels) of the canvas that the picture
 *              will be rendered to.
 * @param vsize The vertical size (in pixels) of the canvas that the picture
 *              will be rendered to.
 * @param field_of_view The angle that describes how much the camera can see.
 *                      When the field of view is small, the view will be
 *                      "zoomed in", magnifying a smaller area of the scene.
 * @return Returns the instance of a new camera.
 */
t_camera	new_camera(float hsize, float vsize, float field_of_view);

/**
 * @brief Computes the ray that passes through the specified pixel on the
 *        camera plane.
 *
 * This function takes a camera and the pixel coordinates on the camera plane
 * as input, and returns a ray with its origin at the camera position and its
 * direction passing through the center of the pixel. To compute the ray, the
 * function first calculates the displacement of the pixel center relative to
 * the canvas edge, and then computes the non-transformed world coordinates of
 * the pixel. Next, using the camera's transformation matrix, the function
 * transforms the canvas point and the origin (0,0,0) to world coordinates.
 * Based on these transformed coordinates, the function computes the direction
 * of the ray from the origin to the pixel point, normalizing the resulting
 * vector to ensure that it has unit length.
 *
 * @param camera Pointer to the camera object.
 * @param px The horizontal coordinate of the pixel on the camera plane.
 * @param py The vertical coordinate of the pixel on the camera plane.
 * @return Returns a ray that passes through the specified pixel on the camera
 *         plane.
 */
t_ray		ray_for_pixel(t_camera *camera, float px, float py);

#endif
