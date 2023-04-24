/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 11:13:43 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/23 11:14:27 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "canvas.h"

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
