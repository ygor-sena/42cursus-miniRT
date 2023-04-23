/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:28:08 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/23 11:14:39 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CANVAS_H
# define CANVAS_H

# include "libft.h"
# include "mlx.h"
# include "camera.h"
# include "world.h"

# define K_ESCAPE        0xff1b
# define DESTROYNOTIFY   17
# define NOEVENTMASK     0L
# define K_Q             0x0071

typedef struct s_canvas
{
	void	*img_ptr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
	char	*addr;
	void	*mlx_ptr;
	void	*win_ptr;
}	t_canvas;

void	init_mlx_connection(t_canvas *canvas);
t_bool	new_canvas(t_canvas *canvas, int width, int height);
t_bool	put_on_window(t_canvas *canvas, char *title);
int		show_window(t_canvas *canvas);

int		handle_keypress(int keysym, t_canvas *canvas);
int		quit(t_canvas *canvas);

t_bool	render_scene(t_canvas *canvas, t_world *world, t_camera *camera);
int		rgb(t_color color);
void	write_pixel(const t_canvas *canvas, int x, int y, int color);
int		pixel_at(t_canvas *image, int x, int y);

#endif
