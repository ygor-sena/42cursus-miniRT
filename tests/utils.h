/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:31:28 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/12 10:38:05 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

# include <stdio.h>

# include "world.h"
# include "shapes.h"
# include "helpers.h"
# include "camera.h"
# include "canvas.h"

# define EPSILON 0.00001

t_bool		compare_spheres(t_sphere *a, t_sphere *b);
t_world		world_stub(void);
t_world		default_world(void);
void		add_shape_to_world(t_world *world, t_shape shape);
t_sphere	*sphere_stub(void);
t_bool		compare_spheres(t_sphere *a, t_sphere *b);
t_bool		compare_tuples(t_tuple a, t_tuple b);
void		assert_matrix_equal(t_matrix a, t_matrix b);

#endif
