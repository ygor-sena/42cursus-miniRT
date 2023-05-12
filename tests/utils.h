/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:31:28 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/11 12:53:31 by mdias-ma         ###   ########.fr       */
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
# include "parser.h"

# define EPSILON 0.00001

t_bool		compare_spheres(t_sphere *a, t_sphere *b);
t_world		world_stub(void);
t_world		default_world(void);
t_sphere	*sphere_stub(void);
t_bool		compare_spheres(t_sphere *a, t_sphere *b);
t_bool		compare_tuples(t_tuple a, t_tuple b);
void		assert_matrix_equal(t_matrix a, t_matrix b);

#endif
