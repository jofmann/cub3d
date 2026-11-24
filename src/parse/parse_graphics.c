/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_graphics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:24:14 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/17 14:24:24 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_graphics_full(int graphics[])
{
	int	i;

	i = 0;
	while (i < GRAPHICS_LENGTH)
	{
		if (graphics[i] == 0)
			return (false);
		i++;
	}
	return (true);
}

static void	parse_config_line(t_cub3d *cub3d, int *graphics, char *line)
{
	if (line[0] == '\0')
		return ;
	if (load_texture(cub3d, graphics, line))
		return ;
	if (load_rgb(cub3d, graphics, line))
		return ;
	free(line);
	handle_error(cub3d, "Invalid line in config");
}

void	parse_graphics(t_cub3d *cub3d, int fd)
{
	int		i;
	char	*curr_line;
	char	*input_str;
	int		graphics[GRAPHICS_LENGTH];

	ft_memset(graphics, 0, sizeof(int) * GRAPHICS_LENGTH);
	while (!is_graphics_full(graphics))
	{
		curr_line = get_next_line(fd);
		if (!curr_line)
			break ;
		input_str = clean_str(curr_line);
		free(curr_line);
		if (!input_str)
			handle_error(cub3d, "Allocation failed");
		parse_config_line(cub3d, graphics, input_str);
		free(input_str);
	}
	i = 0;
	while (i < GRAPHICS_LENGTH)
	{
		if (graphics[i] != 1)
			handle_error(cub3d, "Wrong config for graphics");
		i++;
	}
}
