#include "so_long.h"

void	ft_bzero(void *s, size_t n)
{
	// TODO maybe add more than one p[i]
	// so it bzeros faster!
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = '\0';
		i++;
	}
}

t_data	*get_data(void)
{
	// add bool inside data so that first time dis func is called bzero for init?
	// do get_data() with static data, and create init data with memset all to 0
	static t_data	data;
	//if (data.map == NULL)
	//	ft_bzero(&data, sizeof(t_data));

	return (&data);
}

//deprecated erase after being done
void	show_map(void)
{
	int		i;
	char	**map;

	i = 0;
	map = get_data()->map;
	while (map != NULL && map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

void	*mymalloc(size_t size)
{
	void *out;

	out = malloc(size);
	if (out == NULL)
		panic(ERR_MALLOC);
	ft_bzero(out, size);
	return (out);
}

char	*ft_strdup(char *str)
{
	char	*outstr;
	int		i;

	if (str == NULL)
		return (NULL);
	outstr = mymalloc(sizeof(char) * (ft_strlen(str) + 1));
	i = 0;
	while (str[i])
	{
		outstr[i] = str[i];
		i++;
	}
	outstr[i] = '\0';
	return (outstr);
}
