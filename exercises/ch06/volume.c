#include <stdio.h>
#include <stdlib.h>

#include "mlx.h"
#include "tuples.h"
#include "matrices.h"
#include "canvas.h"
#include "shapes.h"
#include "materials.h"
#include "rays.h"

# define MLX_WIDTH 500
# define MLX_HEIGHT 500
# define MLX_TITLE "Rendering a whole roundy sphere from chapter 6!"

/*
	This structure is world's wall to render the projections on it.
	Moving the ray origin closer to the sphere will make the sphere in the
	drawing larger. Moving it farther away will make the sphere smaller.
	Moving the wall will do similarly.
*/
typedef struct s_wall
{
	float	world_x;
	float	world_y;
	float	wall_z;
	float	wall_size;
}	t_wall;

t_sphere	sphere_stub(void)
{
	return ((t_sphere){
		.origin = point(0, 0, 0),
		.radius = 1.0,
		.transform = get_identity_matrix(),
		.material = material()
	});
}

static void	build_world(t_canvas *canvas)
{
	// World's colors
	int				bkg_color;
	int				color;

	// World's setup
	t_point			ray_origin;
	t_wall			wall;
	float			pixel_size;
	float			half;

	// World's objects
	t_sphere		shape;
	t_tuple			pos;
	t_ray			r;
	t_intersection	*xs;
	t_intersection	*i;
	t_light			*light;

	bkg_color = rgb(new_color(0.0, 0.25, 0.35));

	// Start the ray at z = -5
	ray_origin = point(0, 0, -5);

	// Put the wall at z = 10
	wall = (t_wall){0, 0, 10, 7};

	// Get the size of a single pixel (in world space units)
	pixel_size = wall.wall_size / MLX_HEIGHT;

	// Assume we're looking at the center of the sphere, half of the wall will
	// be to left and the other half, to the right
	half = wall.wall_size / 2;

	// We have the canvas and wall size, ray's origin. Now we can compute,
	// cast and intersect rays
	color = rgb(new_color(1, 0, 0));
	shape = sphere_stub();

	// To render the shading, we need to assign a material color for our sphere
	shape.material.color = new_color(1, 0.2, 1);

	// Add the light source to get contrast and shading visuals
	light = point_light(point(-10, 10, -10), new_color(1, 1, 1));

	// For each row of pixels in the canvas...
	for (int y = 0; y <= MLX_HEIGHT - 1; y++)
	{
		// Compute the world_y coordinate (top = +half, bottom = -half)
		wall.world_y = half - pixel_size * y;

		// For each pixel in the row...
		for (int x = 0; x <= MLX_HEIGHT - 1; x++)
		{
			// 1) Compute the world x coordinate (left = -half, right = half)
			wall.world_x = -half + pixel_size * x;

			// 2) Describe the point on the wall that the ray will target
			pos = point(wall.world_x, wall.world_y, wall.wall_z);
			r = new_ray(ray_origin, normalize(subtract(pos, ray_origin)));
			xs = intersect(&shape, r);

			i = hit(xs);

			// If the ray passed though the sphere, render the sphere and its
			// shading, as well as the material color, else render the background
			if (i)
			{
				t_tuple	p;
				t_sight	eye;
				t_color	final;

				// Normalizing the ray is fundamental to find the normal vector
				// at the hit (the closest intersection) and calculate the eye vector
				p = position(r, i->t);
				eye.normalv = normal_at(*i->object.sphere, p);
				eye.eyev = negate(r.direction);

				// Calculate the final color with lighting() functior
				final = lighting(i->object.sphere->material, *light, p, eye);
				color = rgb(final);
				write_pixel(canvas, x, y, color);
			}
			else
				write_pixel(canvas, x, y, bkg_color);
			erase_intersections(&xs);
		}
	}
	free(light);
}

int main(void)
{
	t_canvas	rt;

	if (!new_canvas(&rt, MLX_WIDTH, MLX_HEIGHT))
		return (EXIT_FAILURE);
	build_world(&rt);
	put_on_window(&rt, MLX_TITLE);
	mlx_expose_hook(rt.win_ptr, show_window, &rt);
	mlx_hook(rt.win_ptr, DESTROYNOTIFY, NOEVENTMASK, quit, &rt);
	mlx_key_hook(rt.win_ptr, handle_keypress, &rt);
	mlx_loop(rt.mlx_ptr);
	return (0);
}
