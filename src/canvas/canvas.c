/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:42:43 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/03/24 17:26:58 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "canvas.h"

static t_bool	init_window(t_canvas *canvas, char *title);
static t_bool	init_canvas(t_canvas *canvas);

t_bool	new_canvas(t_canvas *canvas, int width, int height)
{
	canvas->width = width;
	canvas->height = height;
	if (!init_window(canvas, "MiniRT"))
		return (FALSE);
	if (!init_canvas(canvas))
		return (FALSE);
	return (TRUE);
}

int	quit(t_canvas *canvas)
{
	mlx_destroy_image(canvas->mlx_ptr, canvas->img_ptr);
	mlx_destroy_window(canvas->mlx_ptr, canvas->win_ptr);
	mlx_destroy_display(canvas->mlx_ptr);
	free(canvas->mlx_ptr);
	exit(EXIT_SUCCESS);
}

int	handle_keypress(int keysym, t_canvas *canvas)
{
	if (keysym == K_ESCAPE || keysym == K_Q)
		quit(canvas);
	return (EXIT_SUCCESS);
}

static t_bool	init_window(t_canvas *canvas, char *title)
{
	canvas->mlx_ptr = mlx_init();
	if (!canvas->mlx_ptr)
		return (FALSE);
	canvas->win_ptr = mlx_new_window(canvas->mlx_ptr,
			canvas->width, canvas->height, title);
	if (!canvas->win_ptr)
	{
		free(canvas->win_ptr);
		return (FALSE);
	}
	return (TRUE);
}

static t_bool	init_canvas(t_canvas *canvas)
{
	canvas->img_ptr = mlx_new_image(canvas->mlx_ptr,
			canvas->width, canvas->height);
	if (!canvas->img_ptr)
		return (FALSE);
	canvas->addr = mlx_get_data_addr(canvas->img_ptr, &canvas->bpp,
			&canvas->line_len, &canvas->endian);
	if (!canvas->addr)
		return (FALSE);
	return (TRUE);
}
