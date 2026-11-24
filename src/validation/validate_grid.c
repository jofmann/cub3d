/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_grid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:19:37 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/17 15:20:43 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	visit(t_fill *fill, int x, int y)
{
	char	c;

	if (x < 0 || x >= fill->width || y < 0 || y >= fill->height)
		return (false);
	c = fill->grid[y][x];
	if (c == '1' || c == 'X')
		return (true);
	if (is_white_space(c))
		return (false);
	fill->grid[y][x] = 'X';
	fill->stack[fill->size] = (t_point_int){x, y};
	fill->size++;
	return (true);
}

static bool	flood_fill(t_fill *fill, int start_x, int start_y)
{
	t_point_int	p;

	if (!visit(fill, start_x, start_y))
		return (false);
	while (fill->size > 0)
	{
		fill->size--;
		p = fill->stack[fill->size];
		if (!visit(fill, p.x + 1, p.y) || !visit(fill, p.x - 1, p.y)
			|| !visit(fill, p.x, p.y + 1) || !visit(fill, p.x, p.y - 1))
			return (false);
	}
	return (true);
}

static void	validate_chars(t_cub3d *cub3d, char **grid)
{
	int	i;
	int	j;

	i = 0;
	while (grid[i] != NULL)
	{
		j = 0;
		while (grid[i][j] != '\0')
		{
			if (!ft_strchr("01NSEW\t\n\v\f\r ", grid[i][j]))
				handle_error(cub3d, "Wrong chars in grid");
			j++;
		}
		i++;
	}
}

void	validate_grid(t_cub3d *cub3d)
{
	t_fill	fill;
	bool	is_closed;

	validate_chars(cub3d, cub3d->map.grid);
	fill.width = cub3d->map.grid_width;
	fill.height = cub3d->map.grid_height;
	fill.size = 0;
	fill.grid = copy_grid(cub3d, cub3d->map);
	fill.stack = malloc(sizeof(t_point_int) * fill.width * fill.height);
	if (!fill.stack)
	{
		free_grid(fill.grid);
		handle_error(cub3d, "Allocation failed");
	}
	is_closed = flood_fill(&fill, cub3d->map.player_index.x,
			cub3d->map.player_index.y);
	free(fill.stack);
	free_grid(fill.grid);
	if (!is_closed)
		handle_error(cub3d, "Map is not enclosed by walls");
}
