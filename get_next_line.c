/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:24:16 by eagbomei          #+#    #+#             */
/*   Updated: 2023/12/12 16:14:19 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*next_plz(char *lines)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	while (lines[i] != '\0' && lines[i] != '\n')
		i++;
	if (!lines[i])
	{
		free(lines);
		return (NULL);
	}
	line = ft_calloc(ft_strlen(lines) - i, sizeof(char));
	if (line == NULL)
		return (NULL);
	i++;
	while (lines[i])
		line[j++] = lines[i++];
	free (lines);
	return (line);
}

static char	*append_line(char *lines, char *ret)
{
	char	*temp;

	temp = ft_strjoin(lines, ret);
	free(lines);
	return (temp);
}

static char	*find_line(char *lines)
{
	char	*retline;
	int		i;

	i = 0;
	if (!lines[i])
		return (NULL);
	while (lines[i] != '\0' && lines[i] != '\n')
		i++;
	if (lines[i] == '\n')
		i++;
	retline = ft_calloc(sizeof(char), i + 1);
	if (retline == NULL)
	{
		free(lines);
		return (NULL);
	}
	i = 0;
	while (lines[i] != '\0' && lines[i] != '\n')
	{
		retline[i] = lines[i];
		i++;
	}
	if (lines[i] != '\0' && lines[i] == '\n')
		retline[i++] = '\n';
	return (retline);
}

static char	*readfile(int fd, char *lines)
{
	ssize_t		bytes;
	char		*ret;

	if (!lines)
		lines = ft_calloc(1, 1);
	if (lines == NULL)
		return (NULL);
	ret = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (ret == NULL)
		return (free(lines), NULL);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, ret, BUFFER_SIZE);
		if (bytes == -1)
			return (free(lines), NULL);
		ret[bytes] = '\0';
		lines = append_line(lines, ret);
		if (lines == NULL || ft_strchr(ret, '\n'))
			break ;
	}
	free(ret);
	return (lines);
}

char	*get_next_line(int fd)
{
	static char	*lines;
	char		*retstr;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		free(lines);
		lines = NULL;
		return (NULL);
	}
	lines = readfile(fd, lines);
	if (lines == NULL)
		return (NULL);
	retstr = find_line(lines);
	lines = next_plz(lines);
	return (retstr);
}

/*int	main(void)
{
	char *lines;
	
	int		i = 0;
	int		fd;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("doesn't work\n");
		close (fd);
		return (0);
	}
	while (1)
	{
		lines = get_next_line(fd);
		if (lines == NULL)
			break ;
		i++;
		printf("[%d] :%s", i, lines);
		free(lines);
		lines = NULL;
	}
	printf("%s", lines);
	close (fd);
}*/