/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:29:58 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/18 16:39:33 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "canvas.h"
#include "tuples.h"

int		rgb(t_color color);
void	write_pixel(const t_canvas *canvas, int x, int y, int color);
int		render(t_canvas *canvas);
int		render_background(t_canvas *canvas);

int	main(void)
{
	t_canvas	rt;

	if (!new_canvas(&rt, 800, 600, "MiniRT"))
		return (EXIT_FAILURE);
	mlx_expose_hook(rt.win_ptr, render, &rt);
	mlx_hook(rt.win_ptr, DESTROYNOTIFY, NOEVENTMASK, quit, &rt);
	mlx_key_hook(rt.win_ptr, handle_keypress, &rt);
	mlx_loop(rt.mlx_ptr);
	return (EXIT_SUCCESS);
}

int	render(t_canvas *canvas)
{
	render_background(canvas);
	mlx_put_image_to_window(canvas->mlx_ptr, canvas->win_ptr,
		canvas->img_ptr, 0, 0);
	return (EXIT_SUCCESS);
}

int	render_background(t_canvas *canvas)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	color = rgb(new_color(0.6, 0, 1));
	while (y < canvas->height)
	{
		x = 0;
		while (x < canvas->width)
			write_pixel(canvas, x++, y, color);
		y++;
	}
	return (EXIT_SUCCESS);
}

int	rgb(t_color color)
{
	return (
		(int)(color.red * 255 + 0.5) << 16 |
		(int)(color.green * 255 + 0.5) << 8 |
		(int)(color.blue * 255 + 0.5)
	);
}

void	write_pixel(const t_canvas *canvas, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= canvas->width || y < 0 || y >= canvas->height)
		return ;
	pixel = canvas->addr + (y * canvas->line_len + x * (canvas->bpp / 8));
	*(int *)pixel = color;
}
