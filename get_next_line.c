/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:57:06 by cmansey           #+#    #+#             */
/*   Updated: 2022/12/08 13:44:08 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//METTRE DE COTE CE QUI EST LU DANS LE BUFFER DE READ
//QUAND UN RETOUR A LA LIGNE APPARAIT ON STOCK DANS STATIC
//PROBLEME LE CURSEUR DE READ PEUT SE TROUVER APRES LE \N
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

//SI RETOUR A LA LIGNE APPARAIT DANS NOTRE STR ON EXTRAIT
//JUSQUE AU RETOUR A LA LIGNE DANS LINE
char	*ft_get_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!*str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

//ON VA STOCKER CE QUI SE TROUVE APRES LE \N
//DANS STATIC
//POUR LA PROCHAINE FOIS OU ON APPEL GNL
char	*ft_str_next_time(char *str)
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
	new_str = malloc(ft_strlen(str) - i);
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

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = ft_read_str(fd, str);
	if (!str)
		return (NULL);
	line = ft_get_line(str);
	str = ft_str_next_time(str);
	return (line);
	free(str);
}

/*int	main(void)
{
	int		fd;

	fd = open("test.fd", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%d", BUFFER_SIZE);
}*/
