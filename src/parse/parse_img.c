/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:24:34 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/17 15:05:57 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_texture_identifier(char *line, char *identifier)
{
	int	len;

	len = ft_strlen(identifier);
	if (ft_strncmp(identifier, line, len) != 0)
		return (false);
	if (line[len] == '\0')
		return (false);
	if (!is_white_space(line[len]))
		return (false);
	return (true);
}

static void	parse_img(t_cub3d *cub3d, t_img *img, mlx_t *mlx, char *path)
{
	skip_whitespace(&path);
	init_img(cub3d, img, mlx, path);
}

static bool	try_texture(t_cub3d *cub3d, t_img *img, char *str, char *id)
{
	if (!is_texture_identifier(str, id))
		return (false);
	if (img->img)
	{
		free(str);
		handle_error(cub3d, "Duplicate texture identifier");
	}
	parse_img(cub3d, img, cub3d->mlx, str + 2);
	return (true);
}

bool	load_texture(t_cub3d *cub3d, int *seen_flags, char *str)
{
	if (try_texture(cub3d, &cub3d->graphics.north, str, "NO"))
		seen_flags[NO]++;
	else if (try_texture(cub3d, &cub3d->graphics.west, str, "WE"))
		seen_flags[WE]++;
	else if (try_texture(cub3d, &cub3d->graphics.east, str, "EA"))
		seen_flags[EA]++;
	else if (try_texture(cub3d, &cub3d->graphics.south, str, "SO"))
		seen_flags[SO]++;
	else
		return (false);
	return (true);
}
