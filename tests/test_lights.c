/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lights.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:46:27 by yde-goes          #+#    #+#             */
/*   Updated: 2023/05/09 12:38:25 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/** 
 *	ABOUT THIS MODULE TEST_LIGHTS.C
 * 	
 *	The light algorithm implemented on this project is called The Phong
 *	Reflection Model, named by its creator Bui Tuong Phong. It simulates
 *	the interaction between three light sources. They are: ambient reflection,
 *	diffuse reflection and specular reflection. In other words, respectively,
 *	background light, the light reflected from a matte surface and the
 *	reflection of the source light itself. The last one, depends only on the
 *	angle between the reflection vector and the eye vector and is controlled
 *	by a parameter that's called shininess. The higher the shininess, the
 *	smaller and tighter the specular highlight is.
 */

/*	Checks if a point light has the position and intensity given as parameter */
Test(lights, create_point_light)
{
	t_light	light;
	t_color	intensity;
	t_tuple	position;

	intensity = new_color(1, 1, 1);
	position = point(0, 0, 0);
	light = point_light(position, intensity);

	cr_assert(eq(flt, light.position.x, position.x));
	cr_assert(eq(flt, light.position.y, position.y));
	cr_assert(eq(flt, light.position.z, position.z));
	cr_assert(eq(flt, light.position.w, position.w));
	cr_assert(eq(flt, light.intensity.red, intensity.red));
	cr_assert(eq(flt, light.intensity.green, intensity.green));
	cr_assert(eq(flt, light.intensity.blue, intensity.blue));
}
