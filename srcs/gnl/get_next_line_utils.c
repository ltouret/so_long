/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 11:45:28 by ltouret           #+#    #+#             */
/*   Updated: 2021/09/07 11:53:01 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*outstr;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	outstr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (outstr == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		outstr[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		outstr[i] = s2[j];
		i++;
		j++;
	}
	outstr[i] = '\0';
	free(s1);
	return (outstr);
}
