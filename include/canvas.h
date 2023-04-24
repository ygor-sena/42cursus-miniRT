/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:28:08 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/24 09:22:11 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CANVAS_H
# define CANVAS_H

# include "libft.h"
# include "mlx.h"
# include "camera.h"
# include "world.h"

# define K_ESCAPE        0xff1b
# define K_Q             0x0071
# define DESTROYNOTIFY   17
# define NOEVENTMASK     0L

/**
 * ABOUT THE HEADER CANVAS.H
 *
 * This header contains all funtions that works directly or indirectly with
 * graphic information and MLX's library manipulation.
 */

/**
 * @brief The struct of type t_canvas contains the necessary fields for graphic
 *        initialization and window rendering.
 *
 * @param mlx_ptr Contains the pointer to a connection with the Xserver.
 * @param win_ptr Contains the pointer to a window created with MLX.
 * @param img_ptr Contains the pointer to a image created with MLX.
 * @param addr Stores information about how to write data on pixels from an
 *             instance of a MLX's windows and image.
 * @param bpp Contains the bits per pixel value from MLX.
 * @param line_len Contains the line length value from MLX.
 * @param endian Stores the most significant endianess order from MLX.
 * @param width Stores the width of the window and the image created with MLX.
 * @param height Stores the height of the window and the image created with MLX.
 */
typedef struct s_canvas
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_canvas;

/* ************************************************************************** */
/*                                  CANVAS.C                                  */
/* ************************************************************************** */

/**
 * @brief This function attempts to start a connection with Xserver using MLX
 *        library. After that, it tries to create a new window on screen with
 *        the established Xserver connection, width, height and window's title
 *        passed as parameter. Hereafter, an attempt to create a new image on
 *        screen with the new window, width and height is done. Lastly, the
 *        function tries to write information on the new image with a given bits
 *        per pixel, line length and endianess.
 *
 * @param canvas A struct of type t_canvas containing the necessary fields for
 *               graphic initialization and window rendering.
 * @param width The desired width of the window to be created.
 * @param height The desired height of the window to be created.
 * @param title The desired title to describe the window to be created.
 * @return (t_bool) If the function successfully establishes a Xserver
 *         connection, init a window, create a new image on screen and write
 *         information on it, the function returns TRUE. Otherwise, if one of
 *         the four aforementioned steps fail, the function returns FALSE.
 */
t_bool	new_canvas(t_canvas *canvas, int width, int height, char *title);

/**
 * @brief This function is to be used as the second parameter of the MLX library
 *        function mlx_key_hook(), which waits for an user event. If the user
 *        presses ESC or Q's key, the program is cleanly terminated with quit().
 *
 * @param keysym Stores the ID of the key pressed by the user. To see all
 *               possible values of keysym, refer to the header X11/keysymdef.h.
 * @param canvas A struct of type t_canvas containing the necessary fields for
 *               graphic initialization and window rendering.
 * @return (int) If the keysym passed as parameter is equal to ESC or Q's key,
 *               the program successfully exits. Otherwise, the function cleanly
 *               exits with status 0, i.e., EXIT_SUCCESS identifier.
 */
int		handle_keypress(int keysym, t_canvas *canvas);

/**
 * @brief quit() frees every data regarding graphic initialization and window
 *        rendering. It destroys the created image and window as well as the
 *        pointer to an established Xserver's connection, whose variable must be
 *        freed thereafter.
 *
 * @param canvas A struct of type t_canvas containing the necessary fields for
 *               graphic initialization and window rendering.
 * @return (int) After free routine, the function successfully exits with status
 *               0, i.e., EXIT_SUCCESS identifier.
 */
int		quit(t_canvas *canvas);

void	init_mlx_connection(t_canvas *canvas);
t_bool	put_on_window(t_canvas *canvas, char *title);
int		show_window(t_canvas *canvas);
t_bool	render_scene(t_canvas *canvas, t_world *world, t_camera *camera);
int		rgb(t_color color);
void	write_pixel(const t_canvas *canvas, int x, int y, int color);
int		pixel_at(t_canvas *image, int x, int y);

#endif
