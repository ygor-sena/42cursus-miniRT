/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:28:08 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/06/08 21:07:42 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CANVAS_H
# define CANVAS_H

# include "libft.h"
# include "mlx.h"
# include "camera.h"
# include "world.h"

# define SCREEN_WIDTH    800
# define SCREEN_HEIGHT   400

# define K_ESCAPE        0xff1b
# define K_Q             0x0071
# define DESTROYNOTIFY   17
# define NOEVENTMASK     0L

/**
 * ABOUT THE HEADER CANVAS.H
 *
 * This header contains all functions that works directly or indirectly with
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

/**
 * @brief The structure t_scene is how the user sees the ray tracing rendering.
 *        There is a camera from which the world of shapes and point lights are
 *        seen.
 *
 * @param world Stores the world objects to be displayed.
 * @param camera Stores the information about the point of view from which the
 *               world is observed.
 */
typedef struct s_scene
{
	t_world		world;
	t_camera	camera;
}	t_scene;

/* ************************************************************************** */
/*                                  CANVAS.C                                  */
/* ************************************************************************** */

/**
 * @brief This function attempts to start a connection with Xserver using MLX
 *        library.
 *
 * @param canvas A struct of type t_canvas containing the necessary fields for
 *               graphic initialization and window rendering.
 * @return If connection with Xserver is established succesfully, the function
 *         returns nothing. Otherwise, it prints a message to stderr and exits
 *         the program.
 */
void	init_mlx_connection(t_canvas *canvas);

/**
 * @brief This function attempts to start a connection with Xserver using MLX
 *        library. After that, an attempt to create a new image on screen with
 *        the new mlx_ptr, width and height is done. Lastly, the function tries
 *        to write information on the new image with a given bits per pixel,
 *        line length and endianess.
 *
 * @param canvas A struct of type t_canvas containing the necessary fields for
 *               graphic initialization and window rendering.
 * @param width The desired width of the window to be created.
 * @param height The desired height of the window to be created.
 * @return If the function successfully establishes a Xserver connection, create
 *         a new image on screen and write information on it, the function
 *         returns TRUE. Otherwise, if one of the aforementioned steps fail, the
 *         function returns FALSE.
 */
t_bool	new_canvas(t_canvas *canvas, int width, int height);

/**
 * @brief The function tries to create a new window on screen with the
 *        established Xserver connection, width, height and window's title
 *        passed as parameter
 *
 * @param canvas A struct of type t_canvas containing the necessary fields for
 *               graphic initialization and window rendering.
 * @param title The desired title to describe the window to be created. 
 * @return Returns TRUE if new window is created succesfully. Otherwise, it
 *         returns FALSE.
 */
t_bool	put_on_window(t_canvas *canvas, char *title);

/**
 * @brief This function inserts an image to window. To do that, it needs from
 *        the parameter canvas a pointer to an existing Xserver connection, a
 *        pointer an existing window, a pointer to an existing image and the
 *        x and y screen position. The default for x and y is 0.
 *
 * @param canvas A struct of type t_canvas containing the necessary fields for
 *               graphic initialization and window rendering.
 * @return The function successfully exits after image is inserted to window.
 */
int		show_window(t_canvas *canvas);

/* ************************************************************************** */
/*                                 CONTROLS.C                                 */
/* ************************************************************************** */

/**
 * @brief This function is to be used as the second parameter of the MLX library
 *        function mlx_key_hook(), which waits for an user event. If the user
 *        presses ESC or Q's key, the program is cleanly terminated with quit().
 *
 * @param keysym Stores the ID of the key pressed by the user. To see all
 *               possible values of keysym, refer to the header X11/keysymdef.h.
 * @param canvas A struct of type t_canvas containing the necessary fields for
 *               graphic initialization and window rendering.
 * @return If the keysym passed as parameter is equal to ESC or Q's key, the
 *         program successfully exits. Otherwise, the function cleanly exits
 *         with status 0, i.e., EXIT_SUCCESS identifier.
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
 * @return After free routine, the function successfully exits with status 0,
 *         i.e., EXIT_SUCCESS identifier.
 */
int		quit(t_canvas *canvas);

/* ************************************************************************** */
/*                                  RENDER.C                                  */
/* ************************************************************************** */

/**
 * @brief This functions renders a scene of ray casting objects. It attempts to
 *        initialize a connection to the graphic library MLX, if successfilly,
 *        it proceeds to write pixel by pixel to a image that will be rendered
 *        and seen by the user though a MLX's windows.
 *
 * @param scene A struct of type t_scene that stores information about the how
 *              the world will be seen and which objects of a given world will
 *              be observed.
 * @param canvas A struct of type t_canvas containing the necessary fields for
 *               graphic initialization and window rendering.
 * @return Returns TRUE if a scene is rendered successfully. Otherwise, if the
 *         canvas cannot be created, it returns FALSE.
 */
t_bool	render(t_scene *scene, t_canvas *canvas);

/**
 * @brief The function write_pixel() writes a pixel at (x, y) coordinates of the
 *        image, if a given coordinate is within canvas width and height.
 *
 * @param canvas A struct of type t_canvas containing the necessary fields for
 *               graphic initialization and window rendering.
 * @param x The x value of the pixel to be inserted.
 * @param y The y value of the pixel to be inserted.
 * @param color Stores the color of the pixel.
 */
void	write_pixel(const t_canvas *canvas, int x, int y, int color);

#endif
