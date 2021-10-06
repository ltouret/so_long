/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 02:37:12 by ltouret           #+#    #+#             */
/*   Updated: 2021/10/06 18:05:22 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	panic2(t_error err_code)
{
	if (err_code == ERR_MAP_EXIT)
		printf("Error : no exit in map... exiting\n");
	else if (err_code == ERR_MAP_WCHAR)
		printf("Error : no valid char in map... exiting\n");
	else if (err_code == ERR_MAP_EMPTY)
		printf("Error : map is empty... exiting\n");
	else if (err_code == ERR_ARG)
		printf("Error : no valid argument received... exiting\n");
	else if (err_code == ERR_ARG_BER)
		printf("Error : map doesnt end with '.ber'... exiting\n");
	else if (err_code == ERR_TEXT)
		printf("Error : textures are missing... exiting\n");
	else if (err_code == ERR_MLX)
		printf("Error : mlx failed... exiting\n");
	else
		printf("Unknown Error... exiting\n");
}

void	panic(t_error err_code)
{
	if (err_code == ERR_MALLOC)
		printf("Error : out of memory (Malloc)... exiting\n");
	else if (err_code == ERR_MAP_READ)
		printf("Error : cannot read map file... exiting\n");
	else if (err_code == ERR_MAP_OPEN)
		printf("Error : map is not closed... exiting\n");
	else if (err_code == ERR_MAP_RECT)
		printf("Error : map is not rectangle... exiting\n");
	else if (err_code == ERR_MAP_NO_PLAY)
		printf("Error : no player in map... exiting\n");
	else if (err_code == ERR_MAP_MANY_PLAY)
		printf("Error : too many players in map... exiting\n");
	else if (err_code == ERR_MAP_COLL)
		printf("Error : no collectible in map... exiting\n");
	else
		panic2(err_code);
	exit(ERR);
}
