/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:11:42 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/25 19:59:27 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_bool	parse_sphere(t_scanner *scanner, t_scene *scene)
{
	t_shape		shape;
	t_matrix	scale;
	t_matrix	transform;
	t_point		origin;
	double		radius;

	shape = new_sphere();
	if (!parse_position(scanner, &origin))
		return (FALSE);
	if (!parse_dimension(scanner, &radius))
		return (FALSE);
	if (!parse_color(scanner, &shape.material.color))
		return (FALSE);
	if (!scan_newline(scanner))
		return (FALSE);
	radius /= 2;
	scale = scaling(radius, radius, radius);
	transform = translation(origin.x, origin.y, origin.z);
	set_transform(&shape, multiply_mx_mx(transform, scale));
	add_object_to_world(&shape, &scene->world);
	return (TRUE);
}

void calculate_rotation_angles(t_vector vector, double *x_angle, double *z_angle);

t_matrix rotation_matrix(t_vector vector)
{
	double		x_angle;
	double		z_angle;
	t_matrix	rotate_z;
	t_matrix	rotate_x;
	t_matrix	full_rotation;

	calculate_rotation_angles(vector, &x_angle, &z_angle);
	rotate_z = rotation_z(z_angle);
	rotate_x = rotation_x(x_angle);
	full_rotation = multiply_mx_mx(rotate_z, rotate_x);
	return (full_rotation);
}

// encontrar a magnitude do vetor projetado no plano XY
// necessária para determinar o ângulo de rotação em torno do eixo Z
void calculate_rotation_angles(t_vector vector, double *x_angle, double *z_angle)
{
	double	ratio;

	ratio = sqrt((vector.x * vector.x) + (vector.y * vector.y));
	if (0.0 ==  ratio)
		*z_angle = M_PI_2; // 90 graus
	else
		*z_angle = acos(vector.y / ratio); // normalizar o y do vetor
	*x_angle = acos(ratio);
}

t_bool	parse_plane(t_scanner *scanner, t_scene *scene)
{
	t_shape		shape;
	t_vector	direction;
	t_point		origin;
	t_matrix	translate;
	t_matrix	rotate;

	shape = new_plane();
	if (!parse_position(scanner, &origin))
		return (FALSE);
	if (!parse_direction(scanner, &direction))
		return (FALSE);
	if (!parse_color(scanner, &shape.material.color))
		return (FALSE);
	if (!scan_newline(scanner))
		return (FALSE);
	translate = translation(origin.x, origin.y, origin.z);
	rotate = rotation_matrix(direction);
	set_transform(&shape, multiply_mx_mx(translate, rotate));
	add_object_to_world(&shape, &scene->world);
	return (TRUE);
}

t_bool	parse_cylinder(t_scanner *scanner, t_scene *scene)
{
	t_point		origin;
	t_vector	direction;
	double		diameter;
	double		height;
	t_matrix	translate;
	t_matrix	rotate;
	t_matrix	scale;
	t_shape		shape;

	shape = new_cylinder();
	if (!parse_position(scanner, &origin))
		return (FALSE);
	if (!parse_direction(scanner, &direction))
		return (FALSE);
	if (!parse_dimension(scanner, &diameter))
		return (FALSE);
	if (!parse_dimension(scanner, &height))
		return (FALSE);
	if (!parse_color(scanner, &shape.material.color))
		return (FALSE);
	if (!scan_newline(scanner))
		return (FALSE);
	shape.cylinder.maximum = height / 2;
	shape.cylinder.minimum = -height / 2;
	shape.cylinder.closed = TRUE;
	translate = translation(origin.x, origin.y, origin.z);
	shape.cylinder.radius = diameter / 2.0;
	scale = scaling(diameter / 2.0, 1, diameter / 2.0);
	rotate = rotation_matrix(direction);
	set_transform(&shape, multiply_mx_mx(rotate, multiply_mx_mx(translate, scale)));
	add_object_to_world(&shape, &scene->world);
	return (TRUE);
}
