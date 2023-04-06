/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:17:15 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/06 10:32:27 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYS_H
# define RAYS_H

# include "tuples.h"
# include "matrices.h"

typedef struct s_ray
{
	t_point		origin;
	t_vector	direction;
}	t_ray;

t_ray	new_ray(t_point origin, t_vector direction);
t_point	position(t_ray ray, float distance);
t_ray	transform(t_ray ray, t_matrix matrix);

#endif
