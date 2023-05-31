/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:21:56 by yde-goes          #+#    #+#             */
/*   Updated: 2023/05/30 16:41:53 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATTERNS_H
# define PATTERNS_H

# include "matrices.h"

typedef struct s_pattern	t_pattern;

/**
 * @brief t_pttr_at is a function-type that receives the function's name of a
 *        pattern to be applied. For example, to apply a checkered pattern, the
 *        t_pttr_at is "checkered_at", which is the function that computes a
 *        checkered pattern on a given shape. To apply a striped pattern, use
 *        stripe_at instead.
 */
typedef t_color				(*t_pttr_at)(t_pattern pattern,
												t_point world_point);

/**
 * @brief The type t_pattern contatins all the necessary information to apply a
 *        texture on a given shape's surface.
 * @param has_pattern Stores TRUE if shape has a pattern or FALSE, if not.
 * @param pattern_at Receives a pattern function to apply the corresponding
 *                   pattern. For more information, see t_pttr_at description.
 * @param a Receives the first color of a given pattern to be applied.
 * @param b Receives the second color of a given pattern to be applied.
 * @param transform Stores matrix transformation so that pattern be manipulated.
 */
typedef struct s_pattern
{
	t_bool		has_pattern;
	t_pttr_at	pattern_at;
	t_color		a;
	t_color		b;
	t_matrix	transform;
	t_matrix	inverse;
	t_matrix	transpose;
}	t_pattern;

/**
 * @brief This function creates a new default pattern with the following
 *        properties: it has a stripe pattern and it receives the color passed
 *        as parameter to the function.
 * 
 * @param a Receives the first color of a given pattern to be applied.
 * @param b Receives the second color of a given pattern to be applied.
 * @return This function successfully returns a new pattern structure.
 */
t_pattern	new_pattern(t_color a, t_color b);

/**
 * @brief This function applies a stripe pattern on shape's surface located at
 *        a given world point. It checks which pattern color should or not be
 *        applied at a specific point of the world.
 * 
 * @param pattern Stores the pattern to be applied.
 * @param world_point Contains the world's point to be evaluated.
 * @return The function returns the first pattern color a if condition is met.
 *         Otherwise, it returns the second pattern b.
 */
t_color		stripe_at(t_pattern pattern, t_point world_point);

/**
 * @brief This function applies a checkered pattern on shape's surface located
 *        at a given world point. It checks which pattern color should or not be
 *        applied at a specific point of the world.
 * 
 * @param pattern Stores the pattern to be applied.
 * @param world_point Contains the world's point to be evaluated.
 * @return The function returns the first pattern color a if condition is met.
 *         Otherwise, it returns the second pattern b.
 */
t_color		checkered_at(t_pattern pattern, t_point world_point);

/**
 * @brief This function assigns a transformation matrix to a pattern, which is
 *        used to manipulate the way the pattern is rendered.
 * 
 * @param pattern Receives the pattern structure to alter transform's field.
 * @param transform Receives the matrix transformation to be assigned.
 */
void		set_pattern_transform(t_pattern *pattern, t_matrix transform);

#endif
