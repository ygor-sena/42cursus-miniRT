/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:29:58 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/16 22:27:38 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "canvas.h"

t_world	new_world(void);

int	main(void)
{
	t_canvas	rt;
	t_world		w;
	t_camera	c;

	w = new_world();
	c = new_camera(400, 400, M_2_PI);
	c.transform = view_transform(
			point(0, 0, -5),
			point(0, 0, 0),
			vector(0, 1, 0));
	render_scene(&rt, &w, &c);
	put_on_window(&rt, "MiniRT");
	mlx_expose_hook(rt.win_ptr, show_window, &rt);
	mlx_hook(rt.win_ptr, DESTROYNOTIFY, NOEVENTMASK, quit, &rt);
	mlx_key_hook(rt.win_ptr, handle_keypress, &rt);
	mlx_loop(rt.mlx_ptr);
	return (EXIT_SUCCESS);
}

t_world	new_world(void)
{
	t_world	w;
	t_shape	s1;

	w.xs = NULL;
	w.lights = ft_calloc(sizeof(t_light), 1);
	w.objects = ft_calloc(sizeof(t_shape), 2);
	w.object_count = 1;
	/* s1 = new_cylinder();
	s1.cylinder.maximum = 0.5;
	s1.cylinder.minimum = -0.5;
	s1.cylinder.closed = TRUE; */
	s1 = new_cone();
	s1.cone.maximum = 0.5;
	s1.cone.minimum = -0.5;
	s1.cone.closed = TRUE;
	s1.material.color = new_color(0.8, 1.0, 0.6);
	s1.material.diffuse = 0.7;
	s1.material.specular = 0.2;
	//s1.sphere.radius = 0.5;
	w.objects[0] = s1;
	w.lights[0] = point_light(point(-10, 10, -10), new_color(1, 1, 1));
	return (w);
}
