/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_funcions.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 22:21:02 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/27 12:57:33 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_FUNCIONS_H
# define SHAPE_FUNCIONS_H

# include "libft.h"

// "Declaração avançada" ou "forward declaration" em inglês, é uma forma de
// informar o compilador sobre a existência de uma estrutura, função,
// ou outro tipo antes de sua definição completa, permitindo que você
// use esse nome em outros lugares no seu código

/*
 * @struct t_shape
 * Represents a geometric shape
 */
typedef struct s_shape			t_shape;
typedef struct s_ray			t_ray;
typedef struct s_intersection	t_intersection;
// typedef struct s_hit	t_hit;

typedef t_bool					(*t_hit_record)(t_intersection **,
								t_shape *, t_ray);
// typedef t_bool			(*t_hit_method)(t_hit **, t_shape *, t_ray);

#endif
