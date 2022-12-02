/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:57:06 by cmansey           #+#    #+#             */
/*   Updated: 2022/12/02 17:09:15 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//METTRE DE COTE CE QUI EST LU DANS LE BUFFER DE READ
//TANT QUE PAS DE RETOUR A LA LIGNE
//GARDER CE QU ON A LU ET METTRE DANS STATIC
char	*ft_read_str(int fd, char *str)
{
	char		*buf;
	int			i;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	i = 1;
	while (!ft_strchr(str, '\n') && i > 0)
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i == -1)
		{
			free(str);
			free(buf);
			return (NULL);
		}
		buf[i] = '\0';
		str = ft_strjoin(str, buf);
	}
	free(buf);
	return (str);
}

//SI RETOUR A LA LIGNE APPARAIT DANS NOTRE STASH ON EXTRAIT
//RETOUR A LA LIGNE DANS LINE
char	*ft_get_line(char *str)
{
	int		i;
	char	*new_str;

	i = 0;
	if (!*str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	new_str = malloc(i + 2);
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		new_str[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_select_str(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	new_str = malloc(ft_strlen(str) - i + 1);
	if (!new_str)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	str = ft_read_str(fd, str);
	if (!str)
		return (NULL);
	line = ft_get_line(str);
	str = ft_select_str(str);
	return (line);
}

/*SI RETOUR A LA LIGNE APPARAIT DANS NOTRE STASH ON EXTRAIT

CARACTERE ET RETOUR A LA LIGNE DANS LINE

ENSUITE ON NETTOYE CE QUI SE TROUVE DANS LA STASH

ON VEUT GARDER CE QUON A DEJA LU DONC STATIC

int	main()
{
	int		fd;

	fd = open("test.fd", O_RDONLY);
	printf("%ret", get_next_line(fd));
}*/
