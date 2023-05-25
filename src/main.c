/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:29:58 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/25 14:27:05 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_scene	new_scene(void);
void	setup_world(t_scene *scene);
void	deallocate_world(t_scene *scene);

int	main(int argc, char **argv)
{
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
	free(scene->world.objects);
	free(scene->world.lights);
}
