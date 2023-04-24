/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:16:18 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/23 12:51:00 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "canvas.h"

t_bool	render_scene(t_canvas *canvas, t_world *world, t_camera *camera)
{
	float		x;
	float		y;
	t_ray		ray;
	t_color		color;

	if (!new_canvas(canvas, camera->hsize, camera->vsize))
		return (FALSE);
	y = 0;
	while (y < camera->vsize - 1)
	{
		x = 0;
		while (x < camera->hsize - 1)
		{
			ray = ray_for_pixel(camera, x, y);
			color = color_at(*world, ray);
			write_pixel(canvas, x, y, rgb(color));
			x++;
		}
		y++;
	}
	return (TRUE);
}

int	rgb(t_color color)
{
	return (
		(int)(color.red * 255 + 0.5) << 16 |
		(int)(color.green * 255 + 0.5) << 8 |
		(int)(color.blue * 255 + 0.5)
	);
}

int	pixel_at(t_canvas *canvas, int x, int y)
{
	char	*pixel;

	pixel = canvas->addr + (y * canvas->line_len + x * (canvas->bpp / 8));
	return (*(int *)pixel);
}

void	write_pixel(const t_canvas *canvas, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= canvas->width || y < 0 || y >= canvas->height)
		return ;
	pixel = canvas->addr + (y * canvas->line_len + x * (canvas->bpp / 8));
	*(int *)pixel = color;
}
