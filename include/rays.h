/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:17:15 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/06/16 13:40:17 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// @file rays.h
#ifndef RAYS_H
# define RAYS_H

# include "matrices.h"

/**
 * @brief The struct of type t_ray represents a ray, which is the foundation for
 *        ray casting. Ray casting is the process of creating a ray, or line,
 *        and finding the intersections of that ray with the objects in a scene.
 *
 * @param origin Stores the starting point of a ray.
 * @param direction Stores the vector which says where a ray points to.
 */
typedef struct s_ray
{
	t_point		origin;
	t_vector	direction;
}	t_ray;

/* ************************************************************************** */
/*                                   RAYS.C                                   */
/* ************************************************************************** */

/**
 * @brief The function new_ray() creates and queries a ray with the given origin
 *        and direction passed as parameter.
 *
 * @param origin Receives a point tuple, which is starting point of the ray.
 * @param direction Receives a vector tuple, which is the direction where the
 *                  ray points to.
 * @return Sucessfully returns a new ray with the given origin and direction
 *         passed as parameter to the function.
 */
t_ray	new_ray(t_point origin, t_vector direction);

/**
 * @brief The function position() finds the position of a given ray and a given
 *        time or distance. To find a ray's position, it's necessary to multiply
 *        the ray direction by time or distance to find the total distance
 *        traveled and add the result to the ray's origin.
 *
 * @param ray Receives a ray as reference.
 * @param distance Receives a float value which is the time or distance that the
 *                 ray must travel.
 * @return Returns the ray's coordinates after it traveled for a given time or
 *         after it gone through a given distance.
 */
t_point	position(t_ray ray, float distance);

/**
 * @brief The function transform() multiplies a given ray by a given matrix,
 *        which results in an unnormalized ray. In other words, whatever wanted
 *        transformation to be applied to a world's object is applied instead in
 *        the ray by the inverse of the operation intended on a world's object.
 *        For more information, refer to the book TRTC on page 66.
 *
 * @param ray Receives a ray to the transformed.
 * @param matrix Reveives the matrix transformation to be applied in the ray.
 * @return Successfully returns a new unnormalized and transformed ray.
 */
t_ray	transform(t_ray ray, t_matrix matrix);

#endif
