/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:05:52 by yde-goes          #+#    #+#             */
/*   Updated: 2023/05/25 14:34:20 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_H
# define MATERIALS_H

# include "lights.h"
# include "patterns.h"

/**
 * @brief A material has a surface color and four attributes
 * from the Phong Reflection Model: ambient, diffuse, specular and shininess.
 * Each one of these attributes accept a non negative floating point number.
 * For ambient, diffuse and specular, the typical values are between 0 and 1.
 * For shininess, values between 10 (very large highlight) and 200 (very small)
 * highlight seem to work best, though there is no actual upper bound.
 *
 * @param color Stores the material's color in RGB values.
 * @param ambient Represents the background lighting or the light reflected from
 * other objects in the enviroment.
 * @param diffuse Represents the light reflected from a matted surface. It
 * 	depends only on the angle between the light source and surface normal.
 * @param specular Represents the reflection of the light source itself and
 * results in the bright sport on a curved surface. It depends on the angle
 * between the reflection vector and the eye vector. Thus, it's also controlled
 * by the parameter shininess.
 * @param shininess Represents the shininess. The higher the shininess, the
 * smaller and tigher the specular highlight.
 * @param pattern Represents the pattern texture of a given material. It can be
 *                a striped or a checkered pattern.
 */
typedef struct s_material
{
	t_color		color;
	t_color		ambient;
	float		diffuse;
	float		specular;
	float		shininess;
	t_pattern	pattern;
}	t_material;

/* ************************************************************************** */
/*                               MATERIALS.C                                  */
/* ************************************************************************** */

/**
 * @brief The struct s_exposure contains the necessary fields to calculate the
 * a scene's lighting. Exposure is a technical term from photography that means
 * exposition to light.
 *
 * @param effective_color Combines the surface colo with light's color/
 * intensity.
 * @param lightv Finds the direction to the light source.
 * @param reflectv Finds the direction to the light reflection.
 * @param light_dot_normal Represents the cosine of the angle between the light
 * 	vector and the normal vector. A negative number means the light is on the
 * other side of the surface.
 * @param reflect_dot_eye Represents the cosine of the angle between the
 * reflection vector and the eye vector. A negative number means the light
 * reflects away from the eye.
 * @param factor Computes the specular contribution.
 */
typedef struct s_exposure
{
	t_color	effective_color;
	t_tuple	lightv;
	t_tuple	reflectv;
	float	light_dot_normal;
	float	reflect_dot_eye;
	float	factor;
}	t_exposure;

/**
 * @brief The function material() instances a new material of struct type
 * t_material with the following default values: color = {1, 1, 1},
 * ambient = 0.1, diffuse = 0.9, specular = 0.9 and shininess = 200.
 *
 * @return (t_material) Returns a default instance of the new material.
 */
t_material	material(void);

#endif
