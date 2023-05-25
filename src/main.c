/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:29:58 by mdias-ma          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2023/05/25 14:27:05 by yde-goes         ###   ########.fr       */
=======
/*   Updated: 2023/05/22 18:24:49 by yde-goes         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_scene	new_scene(void);
void	setup_world(t_scene *scene);
void	deallocate_world(t_scene *scene);

int	main(int argc, char **argv)
{
<<<<<<< Updated upstream
	t_scene		scene;
	t_canvas	canvas;

	scene = new_scene();
	if (argc != 2)
		return (EXIT_FAILURE);
	if (!parse(argv[argc - 1], &scene))
	{
		deallocate_world(&scene);
		exit(EXIT_FAILURE);
	}
	setup_world(&scene);
	render(&scene, &canvas);
	put_on_window(&canvas, "MiniRT");
	mlx_expose_hook(canvas.win_ptr, show_window, &canvas);
	mlx_hook(canvas.win_ptr, DESTROYNOTIFY, NOEVENTMASK, quit, &canvas);
	mlx_key_hook(canvas.win_ptr, handle_keypress, &canvas);
	deallocate_world(&scene);
	mlx_loop(canvas.mlx_ptr);
=======
	t_canvas	rt;
	t_world		w;
	t_camera	c;

	w = new_world();
	c = new_camera(10, 10, M_2_PI);
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
>>>>>>> Stashed changes
	return (EXIT_SUCCESS);
}

t_scene	new_scene(void)
{
	t_scene		scene;

	scene.world.xs = NULL;
	scene.world.objects = NULL;
	scene.world.object_count = 0;
	scene.world.lights = NULL;
	scene.world.light_count = 0;
	scene.world.ambient = new_color(0.1, 0.1, 0.1);
	return (scene);
}

void	setup_world(t_scene *scene)
{
	int		index;
	t_color	lighting;

	lighting = scene->world.ambient;
	index = scene->world.object_count;
	while (index--)
		scene->world.objects[index].material.ambient = lighting;
}

void	deallocate_world(t_scene *scene)
{
<<<<<<< Updated upstream
	free(scene->world.objects);
	free(scene->world.lights);
=======
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
	//s1.cone.origin = point(0, 0, 0.25);
	/* s1.cone.maximum = 1.0;
	s1.cone.minimum = -1.0;
	s1.cone.closed = FALSE; */
	//s1.cone.radius = 1.0;
	s1.material.color = new_color(0.8, 1.0, 0.6);
	s1.material.diffuse = 1;
	s1.material.specular = 1;
	//s1.sphere.radius = 0.5;
	w.objects[0] = s1;
	w.lights[0] = point_light(point(10, 0, -10), new_color(1, 1, 1));
	return (w);
>>>>>>> Stashed changes
}
