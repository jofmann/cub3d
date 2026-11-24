/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:54:15 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/18 14:39:18 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_tile(t_map *map, int start_x, int start_y, uint32_t color)
{
	int	pixel_x;
	int	pixel_y;
	int	x;
	int	y;

	y = 0;
	while (y < TILE_SIZE - 1)
	{
		x = 0;
		while (x < TILE_SIZE - 1)
		{
			pixel_x = x + start_x;
			pixel_y = y + start_y;
			if (is_inside_image(map->img, pixel_x, pixel_y))
				mlx_put_pixel(map->img, pixel_x, pixel_y, color);
			x++;
		}
		y++;
	}
}

static t_point_int	pixel_to_tile(t_map *map, int px, int py)
{
	t_point_int	tile;

	tile.x = px / TILE_SIZE;
	tile.y = py / TILE_SIZE;
	if (tile.x < 0)
		tile.x = 0;
	if (tile.y < 0)
		tile.y = 0;
	if (tile.x >= map->grid_width)
		tile.x = map->grid_width - 1;
	if (tile.y >= map->grid_height)
		tile.y = map->grid_height - 1;
	return (tile);
}

static void	draw_visible_tiles(t_map *map, t_point_int offset,
		t_point_int first, t_point_int last)
{
	t_point_int	p;
	uint32_t	color;

	p.y = first.y;
	while (p.y <= last.y)
	{
		p.x = first.x;
		while (p.x <= last.x)
		{
			color = WHITE_COLOR;
			if (map->grid[p.y][p.x] == '1')
				color = GREY_COLOR;
			fill_tile(map, p.x * TILE_SIZE - offset.x,
				p.y * TILE_SIZE - offset.y, color);
			p.x++;
		}
		p.y++;
	}
}

void	draw_minimap(t_cub3d *cub3d)
{
	t_point_int	offset;
	t_point_int	first;
	t_point_int	last;

	draw_background(cub3d->map.img, BLACK_COLOR);
	offset.x = (int)cub3d->player.pos.x - (cub3d->minimap_img_width / 2);
	offset.y = (int)cub3d->player.pos.y - (cub3d->minimap_img_height / 2);
	first = pixel_to_tile(&cub3d->map, offset.x, offset.y);
	last = pixel_to_tile(&cub3d->map, offset.x + cub3d->minimap_img_width,
			offset.y + cub3d->minimap_img_height);
	draw_visible_tiles(&cub3d->map, offset, first, last);
	draw_player(cub3d);
}

void	draw_ray(t_cub3d *cub3d, t_ray ray)
{
	t_point	start;
	t_point	end;
	double	max_len;
	double	scale;

	start = (t_point){cub3d->minimap_img_width / 2,
		cub3d->minimap_img_height / 2};
	end = convert_world_coord_to_minimap_coord(cub3d, ray.hit_pos.x,
			ray.hit_pos.y);
	max_len = sqrt(start.x * start.x + start.y * start.y) + 1;
	if (ray.distance > max_len)
	{
		scale = max_len / ray.distance;
		end.x = start.x + (end.x - start.x) * scale;
		end.y = start.y + (end.y - start.y) * scale;
	}
	draw_line(cub3d->ray_caster.img, start, end, YELLOW_COLOR);
}
