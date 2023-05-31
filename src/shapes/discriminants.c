/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   discriminants.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:23:47 by yde-goes          #+#    #+#             */
/*   Updated: 2023/05/26 12:34:25 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

t_pythagoras	sphere_discriminant(t_sphere *sphere, t_ray ray)
{
	double		a;
	double		b;
	double		c;
	double		delta;
	t_vector	sphere_to_ray;

	sphere_to_ray = subtract(ray.origin, sphere->origin);
	a = dot(ray.direction, ray.direction);
	b = 2.0 * dot(ray.direction, sphere_to_ray);
	c = dot(sphere_to_ray, sphere_to_ray) - 1.0;
	delta = (b * b) - 4.0 * a * c;
	return ((t_pythagoras){
		.a = a,
		.b = b,
		.c = c,
		.t1 = (-b - sqrt(delta)) / (2.0 * a),
		.t2 = (-b + sqrt(delta)) / (2.0 * a),
		.discriminant = delta,
	});
}

t_pythagoras	cylinder_discriminant(t_ray ray)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;

	a = pow(ray.direction.x, 2) + pow(ray.direction.z, 2);
	b = (2.0 * ray.origin.x * ray.direction.x)
		+ (2.0 * ray.origin.z * ray.direction.z);
	c = pow(ray.origin.x, 2) + pow(ray.origin.z, 2) - 1.0;
	discriminant = pow(b, 2) - 4.0 * a * c;
	return ((t_pythagoras){
		.a = a,
		.b = b,
		.c = c,
		.t1 = (-b - sqrt(discriminant)) / (2.0 * a),
		.t2 = (-b + sqrt(discriminant)) / (2.0 * a),
		.discriminant = discriminant,
	});
}

t_pythagoras	cone_discriminant(t_ray ray)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;

	a = (pow(ray.direction.x, 2) - pow(ray.direction.y, 2)
			+ pow(ray.direction.z, 2));
	b = (2.0 * ray.origin.x * ray.direction.x)
		- (2.0 * ray.origin.y * ray.direction.y)
		+ (2.0 * ray.origin.z * ray.direction.z);
	c = pow(ray.origin.x, 2) - pow(ray.origin.y, 2)
		+ pow(ray.origin.z, 2);
	discriminant = pow(b, 2) - 4.0 * a * c;
	return ((t_pythagoras){
		.a = a,
		.b = b,
		.c = c,
		.t1 = (-b - sqrt(discriminant)) / (2.0 * a),
		.t2 = (-b + sqrt(discriminant)) / (2.0 * a),
		.discriminant = discriminant,
	});
}
