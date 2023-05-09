///////////////////////////////////////////////////////////////////////////////
/// Putting It Together: Chapter 9 - Planes

#include "canvas.h"

t_world	new_world(void);
void	add_spheres(t_world *world);
void	add_planes(t_world *world);

int	main(void)
{
	t_canvas	rt;
	t_world		w;
	t_camera	c;

	w = new_world();
	c = new_camera(800, 400, M_PI/3);
	c.transform = view_transform(
			point(0, 1.5, -5),
			point(0, 1, 0),
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

	w.xs = NULL;
	w.lights = ft_calloc(sizeof(t_light), 1);
	w.objects = ft_calloc(sizeof(t_shape), 4);
	w.object_count = 4;
	add_planes(&w);
	add_spheres(&w);
	w.lights[0] = point_light(point(-10, 10, -10), new_color(1, 1, 1));
	return (w);
}

void	add_planes(t_world *world)
{
	t_shape	floor;

	floor = new_plane();
	floor.material.color = new_color(1, 0.9, 0.9);
	floor.material.specular = 0;
	world->objects[0] = floor;
}

void	add_spheres(t_world *world)
{
	t_shape	middle;
	t_shape	right;
	t_shape	left;

	middle = new_sphere();
	middle.transform = translation(-0.5, 1, 0.5);
	middle.material.color = new_color(0.1, 1, 0.5);
	middle.material.diffuse = 0.7;
	middle.material.specular = 0.2;

	right = new_sphere();
	right.transform = multiply_mx_mx(translation(1.5, 0.5, -0.5), scaling(0.5, 0.5, 0.5));
	right.material.color = new_color(0.5, 1, 0.1);
	right.material.diffuse = 0.7;
	right.material.specular = 0.2;

	left = new_sphere();
	left.transform = multiply_mx_mx(translation(-1.5, 0.33, -0.75), scaling(0.33, 0.33, 0.33));
	left.material.color = new_color(1, 0.8, 0.1);
	left.material.diffuse = 0.7;
	left.material.specular = 0.3;

	world->objects[1] = middle;
	world->objects[2] = right;
	world->objects[3] = left;
}
