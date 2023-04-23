#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "mlx.h"
#include "canvas.h"

#define MLX_WIDTH 800
#define MLX_HEIGHT 600
#define MLX_TITLE "Background from Chapter 7"

///////////////////////////////////////////////////////////////////////////////
/// Prototypes
void		render(t_canvas *canvas);
void		add_background(t_world *world);
void		add_spheres(t_world *world);
t_matrix	left_wall_transform(void);
t_matrix	right_wall_transform(void);

// Add to the world
void		add_object(t_world *world, t_sphere *object);
void		add_light(t_world *world, t_light *light);

int	main(void)
{
	t_canvas	rt;

	render(&rt);
	mlx_expose_hook(rt.win_ptr, show_window, &rt);
	mlx_hook(rt.win_ptr, DESTROYNOTIFY, NOEVENTMASK, quit, &rt);
	mlx_key_hook(rt.win_ptr, handle_keypress, &rt);
	mlx_loop(rt.mlx_ptr);
}

void	render(t_canvas *canvas)
{
	t_world		world;
	t_camera	camera;

	world.lights = NULL;
	world.objects = NULL;
	add_background(&world);
	add_spheres(&world);
	add_light(&world, point_light(point(-10, 10, -10), new_color(1, 1, 1)));

	camera = new_camera(MLX_WIDTH, MLX_HEIGHT, M_PI/3);
	camera.transform = view_transform(point(0, 1.5, -5), point(0, 1, 0), vector(0, 1, 0));
	render_scene(canvas, &world, &camera);
	put_on_window(canvas, MLX_TITLE);
}

void	add_background(t_world *world)
{
	t_sphere	*floor;
	t_sphere	*left_wall;
	t_sphere	*right_wall;

	floor = new_sphere();
	floor->transform = scaling(10, 0.01, 10);
	floor->material = material();
	floor->material.color = new_color(1, 0.9, 0.9);
	floor->material.specular = 0;

	left_wall = new_sphere();
	left_wall->transform = left_wall_transform();
	left_wall->material = floor->material;

	right_wall = new_sphere();
	right_wall->transform = right_wall_transform();
	right_wall->material = floor->material;

	add_object(world, floor);
	add_object(world, left_wall);
	add_object(world, right_wall);
}

void	add_spheres(t_world *world)
{
	t_sphere	*middle;
	t_sphere	*right;
	t_sphere	*left;

	middle = new_sphere();
	middle->transform = translation(-0.5, 1, 0.5);
	middle->material = material();
	middle->material.color = new_color(0.1, 1, 0.5);
	middle->material.diffuse = 0.7;
	middle->material.specular = 0.2;

	right = new_sphere();
	right->transform = multiply_mx_mx(translation(1.5, 0.5, -0.5), scaling(0.5, 0.5, 0.5));
	right->material = material();
	right->material.color = new_color(0.5, 1, 0.1);
	right->material.diffuse = 0.7;
	right->material.specular = 0.2;

	left = new_sphere();
	left->transform = multiply_mx_mx(translation(-1.5, 0.33, -0.75), scaling(0.33, 0.33, 0.33));
	left->material = material();
	left->material.color = new_color(1, 0.8, 0.1);
	left->material.diffuse = 0.7;
	left->material.specular = 0.3;
	
	add_object(world, middle);
	add_object(world, right);
	add_object(world, left);
}

void	add_object(t_world *world, t_sphere *object)
{
	ft_lstadd_back(&world->objects, ft_lstnew(object));
}

void	add_light(t_world *world, t_light *light)
{
	ft_lstadd_back(&world->lights, ft_lstnew(light));
}

t_matrix	left_wall_transform(void)
{
	return (
	multiply_mx_mx(
		multiply_mx_mx(
			multiply_mx_mx(
				translation(0, 0, 5),
				rotation_y(-M_PI_4)), // NOTE: -PI/4
			rotation_x(M_PI_2)),
		scaling(10, 0.01, 10))
	);
}

t_matrix	right_wall_transform(void)
{
	return (
	multiply_mx_mx(
		multiply_mx_mx(
			multiply_mx_mx(
				translation(0, 0, 5),
				rotation_y(M_PI_4)), // NOTE: +PI/4
			rotation_x(M_PI_2)),
		scaling(10, 0.01, 10))
	);
}
