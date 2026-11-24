/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:06:20 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/17 15:06:29 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	grid_len(char **grid)
{
	int	i;

	i = 0;
	while (grid[i])
		i++;
	return (i);
}

static int	extract_color_code(char *str)
{
	int		color_code;
	char	*temp;

	if (!str)
		return (-1);
	temp = str;
	skip_whitespace(&temp);
	if (temp[0] == '\0' || ft_strlen(temp) > 3)
		return (-1);
	if (!is_valid_digit_string(temp))
		return (-1);
	color_code = ft_atoi(temp);
	return (color_code);
}

static bool	parse_rgb(t_rgb *rgb, char *line)
{
	char	**rgb_arr;

	rgb_arr = ft_split(line, ',');
	if (!rgb_arr)
	{
		return (false);
	}
	if (grid_len(rgb_arr) != 3)
	{
		free_grid(rgb_arr);
		return (false);
	}
	rgb->red = extract_color_code(rgb_arr[0]);
	rgb->green = extract_color_code(rgb_arr[1]);
	rgb->blue = extract_color_code(rgb_arr[2]);
	if (!validate_rgb(*rgb) || rgb->red == -1 || rgb->green == -1
		|| rgb->blue == -1)
	{
		free_grid(rgb_arr);
		return (false);
	}
	free_grid(rgb_arr);
	return (true);
}

bool	load_rgb(t_cub3d *cub3d, int *seen_flags, char *str)
{
	t_rgb	*target;
	int		flag;

	if (str[0] == 'F' && is_white_space(str[1]))
	{
		target = &cub3d->graphics.floor;
		flag = F;
	}
	else if (str[0] == 'C' && is_white_space(str[1]))
	{
		target = &cub3d->graphics.ceiling;
		flag = C;
	}
	else
		return (false);
	if (seen_flags[flag] || !parse_rgb(target, str + 1))
	{
		free(str);
		handle_error(cub3d, "Wrong color input");
	}
	seen_flags[flag]++;
	return (true);
}
