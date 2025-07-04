/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajodar <ajodar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:02:17 by ajodar            #+#    #+#             */
/*   Updated: 2025/07/05 10:49:27 by ajodar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

//20250608
// Cierra el juego al presionar scape y libera la memoria
// main -> mlx_key_hook -> handle_key -> handle_scape
static void	handle_escape(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		cleanup_game(game);
		exit(EXIT_SUCCESS);
	}
}

//20250608
// Gestiona la salida del programa con scape, el movimiento, rotación y animación de la interfaz
// main -> mlx_key_hook -> handle_key
void	handle_key(mlx_key_data_t keydata, void *param)
{
	t_game *game = (t_game *)param;
	double		move_speed;

	move_speed = MOVE_SPEED;
	handle_escape(keydata, game);
	if (keydata.action != MLX_PRESS && keydata.action != MLX_REPEAT)
		return;
	handle_movement(game, keydata, move_speed);
	handle_rotation(game, keydata);
	handle_lateral(game, keydata, move_speed);
	if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
		wall_collision(game);
	if (keydata.key == MLX_KEY_2 && keydata.action == MLX_PRESS)
		restart_light_anim(game);
}
