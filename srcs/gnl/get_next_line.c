/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 23:25:39 by ltouret           #+#    #+#             */
/*   Updated: 2021/09/07 18:57:33 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

#define BU 10

static int	find_nl(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char	*ft_substr(char *str, int start, int len)
{
	char	*outstr;
	int		i;

	if (str == NULL || start < 0 || len < 0 || ft_strlen(str) < start)
		return (NULL);
	outstr = malloc(sizeof(char) * (len + 1));
	if (outstr != NULL)
	{
		i = 0;
		while (str[start] && i < len)
		{
			outstr[i] = str[start];
			i++;
			start++;
		}
		outstr[i] = '\0';
	}
	return (outstr);
}

static char	*after_nl(char *line, int nl)
{
	char	*tmp;
	int		len;

	len = ft_strlen(line);
	if (nl == -1)
		len = 0;
	tmp = ft_substr(line, nl + 1, len);
	free(line);
	return (tmp);
}

// add outstr = ft_substr(*line, 0, nl + 1); if u want nl included
// line 93

static char	*read_file(char **line, int fd, char *buf)
{
	char		*outstr;
	int			nl;
	int			eof;

	nl = -1;
	eof = BU;
	outstr = NULL;
	while (eof == BU && nl == -1)
	{
		eof = read(fd, buf, BU);
		*line = ft_strjoin(*line, buf);
		if (eof != BU && ft_strlen(*line) == 0)
		{
			free(*line);
			return (NULL);
		}
		nl = find_nl(*line);
	}
	outstr = ft_substr(*line, 0, nl);
	*line = after_nl(*line, nl);
	return (outstr);
}

char	*get_next_line(int fd)
{
	static char	*line = NULL;
	char		*outstr;
	char		buf[BU + 1];
	int			i;

	outstr = NULL;
	i = -1;
	while (++i < BU + 1)
		buf[i] = '\0';
	if (BU <= 0)
		return (NULL);
	if (line == NULL)
	{
		line = malloc(sizeof(char) * (1));
		if (line == NULL)
			return (NULL);
		line[0] = '\0';
	}
	outstr = read_file(&line, fd, buf);
	return (outstr);
}
