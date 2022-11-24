/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:57:06 by cmansey           #+#    #+#             */
/*   Updated: 2022/11/24 16:07:29 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*fin;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	fin = (char *)malloc((ft_strlen (s1) + ft_strlen (s2) +1));
	if (!fin)
		return (NULL);
	while (*s1)
	{
		fin[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		fin[i] = *s2;
		s2++;
		i++;
	}
	fin[i] = '\0';
	return (fin);
}

char	*ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
			s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	if (c == 0)
		return ((char *)s);
	return (NULL);
}

char	*ft_select(char *buf, char ret)
{
	int		i;
	char	*dest;

	i = 0;
	while (buf && buf[i] && buf[i] != '\n')
		i++;
	dest = malloc(i + 1);
	if (!dest)
		return (NULL);
	if (ft_strchr(buf, '\n') != 0)
		ret = 1;
	i = 0;
	while (buf && buf[i] && buf[i] != '\n')
	{
		dest [i] = buf[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

char	*ft_select2(char *buf)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	while (buf && buf[i] && buf[i] != '\n')
		i++;
		dest = malloc(ft_strlen(buf) - i + 1);
	if (!dest)
		return (NULL);
	j = 0;
	while (buf && buf[i])
		dest[j++] = buf[++i];
	dest[j] = 0;
	return (dest);
}

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	char		*ret;
	static char	*str;
	char		*tmp;
	char		*line;

	ret = BUFFER_SIZE;
	line = NULL;
	if (fd < 0 || fd > 1023 || !line || BUFFER_SIZE <= 0)
		return (NULL);
	while (*ret > 0)
	{
		*ret = read(fd, buf, BUFFER_SIZE);
		if (*ret < 0)
			return (NULL);
		buf[*ret] = 0;
		tmp = str;
		str = ft_strjoin(tmp, buf);
		free(tmp);
		if (ft_strchr(str, '\n'))
			break ;
	}
	line = ft_select(str, *ret);
	tmp = str;
	str = ft_select2(tmp);
	free(tmp);
	if (*ret == 0 && (*str) == 0)
	{
		free(str);
		str = NULL;
	}
	return (&*ret);
}

/*LIRE LE FICHIER
ssize_t	read(int fildes, void *buf, size_t nbyte);
{

}

//METTRE DE COTE CE QUI EST LU DANS LE BUFFER DE READ
void	stock_line(void)
{
	char	*buf;

	buf = malloc(BUFFER_SIZE +1);
	if (buf == NULL)
		return (NULL);
	while (new_line())
	{

	}
}

SI RETOUR A LA LIGNE APPARAIT DANS NOTRE STASH ON EXTRAIT

CARACTERE ET RETOUR A LA LIGNE DANS LINE

ENSUITE ON NETTOYE CE QUI SE TROUVE DANS LA STASH

ON VEUT GARDER CE QUON A DEJA LU DONC STATIC
*/
int	main()
{
	int		fd;
	char	*line;

	fd = open("test1", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		printf("%s", line);
		free(line);
	}
}
