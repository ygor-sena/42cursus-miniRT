/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:09:16 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/06 10:18:20 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUPLES_H
# define TUPLES_H

# include <math.h>

typedef struct s_tuple
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_tuple;

typedef t_tuple	t_point;
typedef t_tuple	t_vector;

typedef struct s_color
{
	float	red;
	float	green;
	float	blue;
}	t_color;

t_tuple	tuple(float x, float y, float z, float w);
t_tuple	point(float x, float y, float z);
t_tuple	vector(float x, float y, float z);

t_tuple	add(t_tuple a, t_tuple b);
t_tuple	subtract(t_tuple a, t_tuple b);
t_tuple	negate(t_tuple a);
t_tuple	multiply(t_tuple a, float scalar);
t_tuple	divide(t_tuple a, float scalar);

/* Get the length of a vector. */
float	magnitude(t_tuple vector);

/* Scale a vector to length 1. */
t_tuple	normalize(t_tuple vector);

/* Get the value that indicates the relationship between 2 vectors,
 * in terms of direction. */
float	dot(t_tuple a, t_tuple b);

/* Get a new vector perpendicular to both of the original vectors. */
t_tuple	cross(t_tuple a, t_tuple b);

t_color	new_color(float red, float green, float blue);
t_color	add_color(t_color a, t_color b);
t_color	subtract_color(t_color a, t_color b);
t_color	multiply_color(t_color color, float scalar);
t_color	hadamard_product(t_color a, t_color b);

#endif
