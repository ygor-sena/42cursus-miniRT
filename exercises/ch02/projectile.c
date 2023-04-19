#include <stdio.h>
#include <stdlib.h>

#include "mlx.h"
#include "tuples.h"
#include "canvas.h"

typedef t_tuple	t_vector;
typedef t_tuple	t_point;

typedef struct s_projectile
{
	t_point		position;
	t_vector	velocity;
}	t_projectile;

typedef struct s_environment
{
	t_vector	gravity;
	t_vector	wind;
}	t_environment;

t_projectile		tick(t_environment env, t_projectile proj);
t_projectile		projectile(t_point position, t_vector velocity);
t_environment		environment(t_vector gravity, t_vector wind);

static void			write_dot(const t_canvas *canvas, int x, int y, int color);
static void			write_pixel(const t_canvas *canvas, int x, int y, int color);
static int			rgb(t_color color);

static int			render_scene(t_canvas *canvas);
static void			render_background(t_canvas *canvas);
static void			render_projectile_motion(t_canvas *canvas);
static void			display_position(t_projectile p);

int	main(void)
{
	t_canvas	rt;

	if (!new_canvas(&rt, 900, 550))
		return (EXIT_FAILURE);
	mlx_expose_hook(rt.win_ptr, render_scene, &rt);
	mlx_hook(rt.win_ptr, DESTROYNOTIFY, NOEVENTMASK, quit, &rt);
	mlx_key_hook(rt.win_ptr, handle_keypress, &rt);
	mlx_loop(rt.mlx_ptr);
}

t_projectile	tick(t_environment env, t_projectile proj)
{
	t_point		position;
	t_vector	velocity;

	position = add(proj.position, proj.velocity);
	velocity = add(add(proj.velocity, env.gravity), env.wind);
	return (projectile(position, velocity));
}

t_projectile	projectile(t_point position, t_vector velocity)
{
	return ((t_projectile){position, velocity});
}

t_environment	environment(t_vector gravity, t_vector wind)
{
	return ((t_environment){gravity, wind});
}

static int	render_scene(t_canvas *canvas)
{
	render_background(canvas);
	render_projectile_motion(canvas);
	mlx_put_image_to_window(canvas->mlx_ptr, canvas->win_ptr,
		canvas->img_ptr, 0, 0);
	return (EXIT_SUCCESS);
}

static void	render_projectile_motion(t_canvas *canvas)
{
	int				color;
	t_projectile	p;
	t_environment	e;
	t_vector		gravity;
	t_vector		wind;
	t_point			position;
	t_vector		velocity;

	position = point(0, 0, 0);  // projectile
	velocity = multiply(normalize(vector(1, 1.8, 0)), 11.25); // projectile
	gravity = vector(0, -0.1, 0); // environment
	wind = vector(-0.01, 0, 0);   // environment

	color = rgb(new_color(1, 1, 1));
	p = projectile(position, velocity);
	e = environment(gravity, wind);
	display_position(p);
	while (p.position.y >= 0)
	{
		p = tick(e, p);
		write_dot(canvas, p.position.x, canvas->height - p.position.y, color);
		display_position(p);
	}
}

static void	render_background(t_canvas *canvas)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	color = rgb(new_color(0.6, 0, 0.2));
	while (y < canvas->height)
	{
		x = 0;
		while (x < canvas->width)
			write_pixel(canvas, x++, y, color);
		y++;
	}
}

static void	write_dot(const t_canvas *canvas, int x, int y, int color)
{
	write_pixel(canvas, x, y, color);
	write_pixel(canvas, x - 1, y, color);
	write_pixel(canvas, x + 1, y, color);
	write_pixel(canvas, x, y + 1, color);
	write_pixel(canvas, x, y - 1, color);
}

static void	display_position(t_projectile p)
{
	printf("x: %d - y: %d\n", (int)p.position.x, (int)p.position.y);
}

static void	write_pixel(const t_canvas *canvas, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= canvas->width || y < 0 || y >= canvas->height)
		return ;
	pixel = canvas->addr + (y * canvas->line_len + x * (canvas->bpp / 8));
	*(int *)pixel = color;
}

static int	rgb(t_color color)
{
	return (
		(int)(color.red * 255 + 0.5) << 16 |
		(int)(color.green * 255 + 0.5) << 8 |
		(int)(color.blue * 255 + 0.5)
	);
}
