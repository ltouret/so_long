#include "so_long.h"

void	panic(t_error err_code)
// TODO change printf here!
// putstr?
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
	else if (err_code == ERR_MAP_EXIT)
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
	else
		printf("Unknown Error... exiting\n");
	exit(ERR);
}
