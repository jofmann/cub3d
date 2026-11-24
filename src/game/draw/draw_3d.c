/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:54:51 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/19 15:01:09 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling(t_cub3d *cub3d)
{
	mlx_image_t	*img;

	img = cub3d->view_img;
	fill_rows(img, 0, img->height / 2,
		convert_t_rgb_to_rgb_code(cub3d->graphics.ceiling));
}

void	draw_floor(t_cub3d *cub3d)
{
	mlx_image_t	*img;

	img = cub3d->view_img;
	fill_rows(img, img->height / 2, img->height,
		convert_t_rgb_to_rgb_code(cub3d->graphics.floor));
}

void	draw_wall_slice(t_cub3d *cub3d, t_wall wall, int screen_column,
		int texture_offset_x)
{
	double		y_ratio;
	uint32_t	wall_color;
	int			tex_y;
	uint32_t	*pixels;
	int			y;

	y = wall.top_pixel;
	if (y < 0)
		y = 0;
	pixels = (uint32_t *)wall.texture->pixels;
	if (wall.bottom_pixel > (int)cub3d->view_img->height)
		wall.bottom_pixel = cub3d->view_img->height;
	while (y < wall.bottom_pixel)
	{
		y_ratio = (double)(y - wall.top_pixel) / wall.height;
		tex_y = y_ratio * wall.texture->height;
		wall_color = pixels[tex_y * wall.texture->width + texture_offset_x];
		if (is_inside_image(cub3d->view_img, screen_column, y))
			mlx_put_pixel(cub3d->view_img, screen_column, y,
				convert_abgr_to_rgba(wall_color));
		y++;
	}
}
