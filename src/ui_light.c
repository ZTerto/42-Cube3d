/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajodar <ajodar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 10:58:42 by ajodar            #+#    #+#             */
/*   Updated: 2025/07/03 20:15:33 by ajodar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

//20250623 
// Pinta el frame que toca de luz
void	render_light_frame(t_game *game)
{
	int	x = 0;
	int	y = 0;

	if (game->light.img)
		mlx_delete_image(game->mlx, game->light.img);

	game->light.img = mlx_texture_to_image(game->mlx,
		game->light.frames[game->light.current_frame]);
	if (!game->light.img)
	{
		fprintf(stderr, "Error: creating light frame image\n");
		exit(EXIT_FAILURE);
	}
	if (mlx_image_to_window(game->mlx, game->light.img, x, y) == -1)
	{
		fprintf(stderr, "Error: displaying light frame\n");
		exit(EXIT_FAILURE);
	}
}

//20250623 
// Carga tantas texturas como define LIGHT_FRAME_COUNT
static void	load_light_textures(t_game *game)
{
	char	path[128];
	int		i = 0;

	while (i < LIGHT_FRAME_COUNT)
	{
		snprintf(path, sizeof(path), "textures/interface2/light%d.png", i + 1);
		game->light.frames[i] = mlx_load_png(path);
		if (!game->light.frames[i])
		{
			fprintf(stderr, "Error: loading light frame %d\n", i + 1);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

//20250623 
// Actualiza el frame correspondiente que toca pintar a continuación
// Main -> mlx_loop_hook -> light_update
void	light_update(void *param)
{
	t_game *game = (t_game *)param;
	static int	delay = 0;

	if (game->light.finished)
		return;
	delay++;
	if (delay < LIGHT_ANIM_DELAY)
		return;
	delay = 0;
	game->light.current_frame++;
	if (game->light.current_frame >= LIGHT_FRAME_COUNT)
	{
		game->light.current_frame = LIGHT_FRAME_COUNT - 1;
		game->light.finished = true;
	}
	render_light_frame(game);
}

//20250623 
// Inicia la animación la primera vez
static void	init_light_anim_state(t_game *game)
{
	game->light.current_frame = 0;
	game->light.finished = false;
}

//20250623 
// Carga, inicia y pinta el primer frame la primera vez
// main -> init_game_window -> rc_setup -> load_ligth_anim
void	load_light_anim(t_game *game)
{
	load_light_textures(game);
	init_light_anim_state(game);
	render_light_frame(game);
}
