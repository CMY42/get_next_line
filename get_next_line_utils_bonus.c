/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 10:45:27 by cmansey           #+#    #+#             */
/*   Updated: 2022/12/06 12:01:16 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *str, char *buf)
{
	size_t	i;
	size_t	j;
	char	*new_str;

	if (!str)
	{
		str = malloc(sizeof (char));
		str[0] = '\0';
	}
	if (!str || !buf)
		return (NULL);
	new_str = malloc((ft_strlen(str) + ft_strlen(buf)) + 1);
	if (!new_str)
		return (NULL);
	i = -1;
	j = 0;
	if (str)
		while (str[++i])
			new_str[i] = str[i];
	while (buf[j])
		new_str[i++] = buf[j++];
	new_str[i] = '\0';
	free(str);
	return (new_str);
}
