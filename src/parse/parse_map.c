/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:24:57 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/17 14:44:54 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	append_line(t_buffer *buf, char *line)
{
	size_t	len;
	char	*new_data;

	len = ft_strlen(line);
	if (buf->len + len + 1 > buf->cap)
	{
		while (buf->len + len + 1 > buf->cap)
			buf->cap *= 2;
		new_data = malloc(buf->cap);
		if (!new_data)
			return (free(line), false);
		ft_memcpy(new_data, buf->data, buf->len + 1);
		free(buf->data);
		buf->data = new_data;
	}
	ft_memcpy(buf->data + buf->len, line, len + 1);
	buf->len += len;
	free(line);
	return (true);
}

static char	*read_all_lines(t_cub3d *cub3d, int fd)
{
	t_buffer	buf;
	char		*curr_line;

	buf.cap = 1024;
	buf.len = 0;
	buf.data = malloc(buf.cap);
	if (!buf.data)
		handle_error(cub3d, "Malloc failed in func: read_all_lines");
	buf.data[0] = '\0';
	curr_line = get_next_line(fd);
	if (!curr_line)
	{
		free(buf.data);
		handle_error(cub3d, "Config must be over map");
	}
	while (curr_line != NULL)
	{
		if (!append_line(&buf, curr_line))
		{
			free(buf.data);
			handle_error(cub3d, "Malloc failed in func: read_all_lines");
		}
		curr_line = get_next_line(fd);
	}
	return (buf.data);
}

static void	parse_grid(t_cub3d *cub3d, t_map *map, int fd)
{
	char	*combined_lines;

	combined_lines = read_all_lines(cub3d, fd);
	if (!combined_lines || combined_lines[0] == '\0')
		handle_error(cub3d, "Failed read_all_lines in func create_grid");
	if (!no_double_newline(combined_lines))
	{
		free(combined_lines);
		handle_error(cub3d, "Invalid map");
	}
	map->grid = ft_split(combined_lines, '\n');
	if (!map->grid || !map->grid[0])
	{
		free(combined_lines);
		handle_error(cub3d, "Wrong location of map");
	}
	if (!fill_with_spaces(map->grid))
	{
		free(combined_lines);
		handle_error(cub3d, "Allocation failed");
	}
	free(combined_lines);
}

static void	parse_grid_size(t_map *map)
{
	int	height;
	int	width;

	height = 0;
	width = 0;
	while (map->grid[height] != NULL)
		height++;
	while (map->grid[0][width] != '\0')
		width++;
	map->grid_height = height;
	map->grid_width = width;
}

void	parse_map(t_cub3d *cub3d, t_map *map, int fd)
{
	parse_grid(cub3d, map, fd);
	parse_grid_size(map);
	parse_player_index(map);
}
