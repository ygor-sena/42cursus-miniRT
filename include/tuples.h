/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:09:16 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/14 15:39:16 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUPLES_H
# define TUPLES_H

# include <math.h>
# include <stdlib.h>

/**
 * @brief Tuple means a list of ordered things. The struct t_tuple stores
 *	coordinates for a left-handed coordinate system, i.e, the thumb of your left
 *	hand points to x in the right direction, the fingers point to y and curling
 *	the fingers towards the palm point to z.
 *	
 * @param x Represents the value of the x-axis coordinate.
 * @param y Represents the value of the y-axis coordinate.
 * @param z Represents the value of the z-axis coordinate.
 * @param w Distinguishes the t_tuple between a vector or a point. If w = 0,
 *	then the tuple is a vector. Otherwise, if w = 1, the tuple is a point.
 */
typedef struct s_tuple
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_tuple;

/**
 * @brief The type t_point is a syntatic sugar for any structure t_tuple whose
 *	w's field equals to 1, i.e., the tuple is a point.
 */
typedef t_tuple	t_point;

/**
 * @brief The type t_point is a syntatic sugar for any structure t_tuple whose
 *	w's field equals to 0, i.e., the tuple is a vector.
 */
typedef t_tuple	t_vector;

/**
 * @brief The struct s_color stores the color values of ray tracing. It contains
 *	a field for red, green and blue values. If all components are 1, the final
 *	color is white. Otherwise, if all of them are 0, the resulting color is
 *	black. Therefore, each field has a range between 0 and 1.
 *
 * @param red Represents the red value of the RGB scale.
 * @param green Represents the green value of the RGB scale.
 * @param blue Represents the blue value of the RGB scale.
 */
typedef struct s_color
{
	float	red;
	float	green;
	float	blue;
}	t_color;

/* ************************************************************************** */
/*                                 MODELS.C                                   */
/* ************************************************************************** */

/**
 * @brief The function tuple() instances a new material of struct type t_tuple
 *	with the given values passed as parameter.
 * 
 * @param x Receives a value for x-axis coordinate.
 * @param y Receives a value for y-axis coordinate.
 * @param z Receives a value for z-axis coordinate.
 * @param w Receives 1 if the tuple is point or 0 if the tuple is a vector.
 * @return (t_tuple) Returns an instance of a tuple with the values passed
 *	as parameter.
 */
t_tuple	tuple(float x, float y, float z, float w);

/**
 * @brief This function is a simplification of the function tuple(). It will
 *	create a point with the given coordinates passed as parameter and set the
 *	field w to 1.
 * 
 * @param x Receives a value for x-axis coordinate.
 * @param y Receives a value for y-axis coordinate.
 * @param z Receives a value for z-axis coordinate. 
 * @return (t_tuple) Returns an instance of a point with the given coordinates
 *	passed as parameter and w set to 1. 
 */
t_tuple	point(float x, float y, float z);

/**
 * @brief This function is a simplification of the function tuple(). It will
 *	create a point with the given coordinates passed as parameter and set the
 *	field w to 0.
 * 
 * @param x Receives a value for x-axis coordinate.
 * @param y Receives a value for y-axis coordinate.
 * @param z Receives a value for z-axis coordinate. 
 * @return (t_tuple) Returns an instance of a point with the given coordinates
 *	passed as parameter and w set to 0. 
 */
t_tuple	vector(float x, float y, float z);

/* ************************************************************************** */
/*                               BASIC_MATH.C                                 */
/* ************************************************************************** */

/**
 * @brief The add() function sums two tuples. A vector plus a point results in a
 *	point (w values: 1 + 0 = 1). A point plus a point results in a point (w
 *	values: 0 + 0 = 0). A tuple plus a tuple results in neither a vector or a
 *	point (w values: 1 + 1 = 2).
 * 
 * @param a Receives the first tuple to sum.
 * @param b Receives the second tuple to sum.
 * @return (t_tuple) Returns a new tuple by adding the corresponding components
 *	of each of the operands.
 */
t_tuple	add(t_tuple a, t_tuple b);

/**
 * @brief The subtract() function subtract two tuples. A vector minus a point
 *	results in a point (w values: 1 - 0 = 1). A point minus a point results in a
 *	point (w values: 0 - 0 = 0). A tuple minus a tuple results in a tuple with a
 *	w of 0, which is another vector representing the change in direction between
 *	the two vectors. A point minus a vector results in a w of -1 (0 - 1 = 1),
 *	which is neither a point or a vector. When this case happens, it's necessary
 *	to use counterpart function negate().
 * 
 * @param a Receives the first tuple to subtract.
 * @param b Receives the second tuple to subtract.
 * @return (t_tuple) Returns a new tuple by subtracting the corresponding
 *	components of each of the operands.
 */
t_tuple	subtract(t_tuple a, t_tuple b);

/**
 * @brief The function negate() returns the opposite vector of a given vector
 *	passed as parameter. If a vector poins from a surface toward a light source,
 *	the opposite vector points from the light source back to the surface.
 * 
 * @param a Receives the vector to be negated.
 * @return (t_tuple) Returns the negated vector of the vector passed as
 *	parameter by doing vector a minus a vector with zero values. 
 */
t_tuple	negate(t_tuple a);

/**
 * @brief The function multiply() multiplies a vector by a scalar value, i.e.,
 *	it changes the vector length uniformly.
 * 
 * @param a Receives the t_tuple vector to be scaled by multiplication.
 * @param scalar Receives a float value to stretch out the vector.
 * @return (t_tuple) Returns a new vector with each component of the given tuple
 *	multiplied by the given scalar passed as parameter.
 */
t_tuple	multiply(t_tuple a, float scalar);

/**
 * @brief The function divide() divides a vector by a scalar value, i.e., it
 *	changes the vector length uniformly.
 * 
 * @param a Receives the t_tuple vector to be scaled by division.
 * @param scalar Receives a float value to shrink the vector.
 * @return (t_tuple) Returns a new vector with each component of the given tuple
 *	divided by the given scalar passed as parameter.
 */
t_tuple	divide(t_tuple a, float scalar);

/* ************************************************************************** */
/*                              VECTOR_MATH.C                                 */
/* ************************************************************************** */

/**
 * @brief The function magnitude() gets the magnitude or length of a given
 *	vector passed as parameter. Vectors with magnitudes of 1 are called unit
 *	vectors or direction vectors.
 * 
 * @param vector Receives the vector to its magnitude value.
 * @return (float) Returns the magnitude value of the length.
 */
float	magnitude(t_tuple vector);

/**
 * @brief The function normalize() takes an arbitrary vector and converts it
 *	into a unit vector. It keeps the calculations anchored relative to a common
 *	scale, i.e., keeps all vectors speaking the same language.
 * 
 * @param vector Receives the vector to be normalized to a unit vector.
 * @return (t_tuple) Returns a new vector that was normalized. 
 */
t_tuple	normalize(t_tuple vector);

/* Get the value that indicates the relationship between 2 vectors,
 * in terms of direction. */

/**
 * @brief The function dot() computes the sum of the products of the
 *	corresponding components of each vector. The smaller the dot product,
 *	the larger the angle between the vectors. A dot product of 1 means the
 *	vectors are identical and a dot product of -1 means they point in
 *	opposite directions. Thus, if the two vectors are unit vectors, the dot
 *	product is the cosine of them.
 *
 * @param a Receives the first vector for the dot product.
 * @param b Receives the second vector for the dot product.
 * @return (float) Returns a value which is the dot product that states the
 *	relationship between two vectors in terms of direction.
 */
float	dot(t_tuple a, t_tuple b);

/**
 * @brief The function cross() multiplies vectors, instead of tuples. After all,
 *	the ray traces only needs a three-dimensional value anyway. The order
 *	of the operands matters and the result is a vector perpendicular to both of
 *	the original vectors. Changes to the operand order changes the direction of
 *	the resulting perpendicular vector.
 * 
 * @param a Receives the first vector to be multiplied.
 * @param b Receives the second vector to be multiplied.
 * @return (t_tuple) Returns a new vector which is perpendicular to both vectors
 *	passed as parameter to the function.
 */
t_tuple	cross(t_tuple a, t_tuple b);

/**
 * @brief This function returns the result of reflecting the in vector
 *	around the normal vector.
 * 
 * @param in A struct of type t_tuple containing the vector to be reflected.
 * @param normal A struct of type t_tuple storing the normal vector to be
 *	used as reference for the reflection of the in vector.
 * @return (t_tuple) Returns the reflected vector from in and out as
 *	reference orientation. 
 */
t_tuple	reflect(t_tuple in, t_tuple normal);

/* ************************************************************************** */
/*                                COLORS.C                                    */
/* ************************************************************************** */
 
/**
 * @brief The function new_color() instances a new color of struct type s_color
 *	with the given values passed as parameter.
 * 
 * @param red Receives a red color value for the RGB scale.
 * @param green Receives a green color value for the RGB scale.
 * @param blue Receives a blue color value for the RGB scale.
 * @return (t_color) Returns an instance of a color with the values passed
 *	as parameter.
 */
t_color	new_color(float red, float green, float blue);

/**
 * @brief The function add_color() combines the intensity of each RGB color
 *	component of a and b. Adding (1, 0, 0) to (0, 1, 0) results in (1, 1, 0),
 *	i.e., adding red to green results in yellow.
 * 
 * @param a Receives the first color to sum.
 * @param b Receives the second color to sum.
 * @return (t_color) Returns a new color with combined intensity resultant of
 *	the sum of each RGB color component of a and b.
 */
t_color	add_color(t_color a, t_color b);

/**
 * @brief The function subtract_color() decreases the intensity of each RGB
 *	color component of a and b. Subtracting (1, 0, 0) to (0, 1, 0) results in
 *	(1, 0, 0), i.e., subtracting red from green results in red.
 * 
 * @param a Receives the first color to decrease.
 * @param b Receives the second color to decrease.
 * @return (t_color) Returns a new color with decreased intensity resultant of
 *	the subtraction of each RGB color component of a and b.
 */
t_color	subtract_color(t_color a, t_color b);

/**
 * @brief The function multiply_color() scales the intensities of each RGB color
 *	component of the parameter color by a constant parameter scalar. For example,
 *	multiply (1, 0, 0) by 0.5 or 1.5 result in (0.5, 0, 0) or (1.5, 0, 0). In
 *	other words, the red components were halved or doubled.
 * 
 * @param color Receives the color to be scaled.
 * @param scalar Receives the scale factor to be applied for each color value.
 * @return (t_color) Returns a new color with halved or intensified RGB color
 *	values resulting from the scalar multiplication.
 */
t_color	multiply_color(t_color color, float scalar);

/**
 * @brief The function hadamard_product() blends two color together by
 *	multipling corresponding components of each color. This process is known as
 *	Hadamard product or Schur product. For example, to view a yellow-green
 *	surface under reddish-purple light would result in a red-like because the
 *	red component would be highest among the RGB values.
 * 
 * @param a Receives the first color to be blended.
 * @param b Receives the second color to be blended.
 * @return (t_color) Returns a new blended color from Schur product of a and b.
 */
t_color	hadamard_product(t_color a, t_color b);

#endif
