/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_setup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajodar <ajodar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:40:13 by ajodar            #+#    #+#             */
/*   Updated: 2025/07/05 12:04:39 by ajodar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

//20250705
// Cargamos las texturas de las puertas
// main -> init_game_window -> rc_setup -> load_door_textures
static void	load_door_textures(t_game *game)
{
	char	path[64];
	int		i;

	for (i = 0; i < 4; i++)
	{
		snprintf(path, sizeof(path), "./textures/door%d.png", i);
		game->door[i] = mlx_load_png(path);
		if (!game->door[i])
		{
			fprintf(stderr, "Error: Failed loading door texture %d from %s\n", i, path);
			exit(EXIT_FAILURE);
		}
	}
}

//20250608 
// cargamos las texturas en mlx
// main -> init_game_window -> rc_setup -> load_wall_textures
static void	load_wall_textures(t_game *game)
{
	game->tex_no = mlx_load_png(game->map.texture_no);
	game->tex_so = mlx_load_png(game->map.texture_so);
	game->tex_we = mlx_load_png(game->map.texture_we);
	game->tex_ea = mlx_load_png(game->map.texture_ea);
	if (!game->tex_no || !game->tex_so || !game->tex_we || !game->tex_ea)
	{
		fprintf(stderr, "Error: loading textures\n");
		exit(EXIT_FAILURE);
	}
}

//20250608 
// Inicialización de texturas en mlx, la interfaz y limpia todo para pintar el fondo
// main -> init_game_window -> rc_setup
void	rc_setup(t_game *game)
{
	load_wall_textures(game);
	load_door_textures(game);
	load_ui_frames(game);
	load_light_anim(game);
	init_background(game);
	game->solid_walls = true;
}
