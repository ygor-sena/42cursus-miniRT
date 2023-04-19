/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:29:11 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/18 16:20:06 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "tuples.h"
# include "matrices.h"

typedef struct s_camera
{
	int			hsize;
	int			vsize;
	float		field_of_view;
	t_matrix	transform;
}	t_camera;

t_matrix	view_transform(t_tuple from, t_tuple to, t_tuple up);
t_camera	new_camera(int hsize, int vsize, float field_of_view);

#endif
