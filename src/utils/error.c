/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:14:11 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/17 15:14:16 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_error(t_cub3d *cub3d, char *error_msg)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putendl_fd(error_msg, STDERR_FILENO);
	if (cub3d)
	{
		free_cub3d(cub3d);
		if (cub3d->mlx)
			mlx_terminate(cub3d->mlx);
	}
	exit(EXIT_FAILURE);
}
