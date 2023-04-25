/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:29:58 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/24 21:29:56 by mdias-ma         ###   ########.fr       */
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
	c = new_camera(800, 600, M_2_PI);
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
	t_world		w;
	t_sphere	*s1;
	t_light		*light;

	w.xs = NULL;
	w.lights = NULL;
	w.objects = ft_calloc(sizeof(t_shape), 2);
	w.object_count = 1;
	s1 = new_sphere();
	s1->material.color = new_color(0.8, 1.0, 0.6);
	s1->material.diffuse = 0.7;
	s1->material.specular = 0.2;
	s1->radius = 0.5;
	light = point_light(point(-10, 10, -10), new_color(1, 1, 1));
	ft_lstadd_back(&w.lights, ft_lstnew(light));
	w.objects[0].sphere = *s1;
	return (w);
}
