/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bumpmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:48:24 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/06/08 20:40:53 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns.h"

static int		clamp(int x, int min, int max);
static t_color	convert_color(int color);
static t_color	pixel_at(t_uv_image *bumpmap, int x, int y);

t_color	bumped_at(t_pattern pattern, t_point point)
{
	size_t		x;
	size_t		y;
	t_checker	uv;

	uv = pattern.texture_map.uv_map(point);
	uv.height = 1 - uv.height;
	x = floor(uv.width * (pattern.texture_map.canvas->width - 1));
	y = floor(uv.height * (pattern.texture_map.canvas->height - 1));
	return (pixel_at(pattern.texture_map.canvas, x, y));
}

// t_color	bumped_at(t_pattern pattern, t_point point)
// {
// 	size_t		x;
// 	size_t		y;
// 	t_checker	uv;
//
// 	uv = pattern.texture_map.uv_map(point);
// 	uv.height = 1 - uv.height;
// 	x = floor(uv.width * (pattern.canvas.width - 1));
// 	y = floor(uv.height * (pattern.canvas.height - 1));
// 	return (pixel_at(&pattern.canvas, x, y));
// }

static t_color	pixel_at(t_uv_image *bumpmap, int x, int y)
{
	char	*pixel;

	x = clamp(x, 0, (bumpmap->width - 1));
	y = clamp(y, 0, (bumpmap->height - 1));
	pixel = bumpmap->addr + (y * bumpmap->line_len + x * (bumpmap->bpp / 8));
	return (convert_color(*(int *)pixel));
}

static int	clamp(int x, int min, int max)
{
	if (x > max)
		return (max);
	if (x < min)
		return (min);
	return (x);
}

static t_color	convert_color(int color)
{
	return ((t_color){
		.red = (0xFF & color >> 16) / 255.0,
		.green = (0xFF & color >> 8) / 255.0,
		.blue = (0xFF & color) / 255.0,
	});
}
