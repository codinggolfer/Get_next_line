/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:24:35 by eagbomei          #+#    #+#             */
/*   Updated: 2023/12/12 15:36:55 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	ft_strlen(char *str)
{
	ssize_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*nstr;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (s1 == 0 || s2 == 0)
		return (0);
	nstr = ft_calloc(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 1);
	if (nstr == NULL)
		return (NULL);
	while ((char)s1[i] != '\0')
	{
		nstr[i] = s1[i];
		i++;
	}
	while ((char)s2[j] != '\0')
	{
		nstr[i] = s2[j];
		i++;
		j++;
	}
	return (nstr);
}

char	*ft_strchr(char *s, int c)
{
	unsigned char		a;
	size_t				len;

	a = c;
	len = ft_strlen(s) + 1;
	while (len--)
	{
		if (*s == a)
		{
			return ((char *)s);
		}
		s++;
	}
	return (0);
}

static void	ft_bzero(void *str, size_t z)
{
	unsigned char	*dest;
	int				i;

	dest = str;
	i = 0;
	while (z > 0)
	{
		dest[i] = '\0';
		i++;
		z--;
	}
}

void	*ft_calloc(size_t blocks, size_t bsize)
{
	void	*ptr;
	size_t	max;

	max = 0 - 1;
	if (blocks != 0)
		if (max / blocks < bsize)
			return (0);
	ptr = malloc(blocks * bsize);
	if (ptr == 0)
		return (0);
	ft_bzero(ptr, blocks * bsize);
	return (ptr);
}
