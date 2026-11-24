/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:54:29 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/17 10:54:36 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_rows(mlx_image_t *img, uint32_t start, uint32_t end,
		uint32_t color)
{
	uint8_t	*pixel;
	uint8_t	*last;

	if (end > img->height)
		end = img->height;
	if (start >= end)
		return ;
	pixel = img->pixels + (size_t)start * img->width * 4;
	last = img->pixels + (size_t)end * img->width * 4;
	while (pixel < last)
	{
		pixel[0] = (color >> 24) & 0xFF;
		pixel[1] = (color >> 16) & 0xFF;
		pixel[2] = (color >> 8) & 0xFF;
		pixel[3] = color & 0xFF;
		pixel += 4;
	}
}

void	clear_image(mlx_image_t *img)
{
	ft_memset(img->pixels, 0, (size_t)img->width * img->height * 4);
}

void	draw_background(mlx_image_t *img, uint32_t color)
{
	fill_rows(img, 0, img->height, color);
}
