/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:28:08 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/03/24 15:38:44 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CANVAS_H
# define CANVAS_H

# include "libft.h"
# include "mlx.h"

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

t_bool	new_canvas(t_canvas *canvas, int width, int height);
int		handle_keypress(int keysym, t_canvas *canvas);
int		quit(t_canvas *canvas);

#endif
