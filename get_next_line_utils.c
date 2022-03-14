/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpires-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 00:09:07 by jpires-p          #+#    #+#             */
/*   Updated: 2022/03/14 18:46:36 by jpires-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i[2];
	char	*dst;

	if (!s)
		return ((char *) NULL);
	if (start > ft_strlen(s))
	{
		start = ft_strlen(s);
		len = 0;
	}
	if (len >= ft_strlen(s))
	{
		len = ft_strlen(s) - start;
	}
	dst = (char *)malloc(((len + 1) * sizeof(char)));
	if (!dst)
		return ((char *) NULL);
	i[0] = 0;
	i[1] = start;
	while (i[0] < len && s[i[1]] != '\0')
		dst[i[0]++] = s[i[1]++];
	dst[i[0]] = '\0';
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i[2];
	size_t	len[2];
	char	*dst;

	if (!s1 || !s2)
		return ((char *) NULL);
	len[0] = ft_strlen(s1);
	len[1] = ft_strlen(s2);
	dst = (char *)malloc(((len[0] + len[1] + 1) * sizeof(char)));
	if (!dst)
		return ((char *) NULL);
	i[0] = -1;
	i[1] = 0;
	while (++i[0] < (len[0] + len[1]))
	{
		if (i[0] < len[0])
			dst[i[0]] = s1[i[0]];
		else
		{
			dst[i[0]] = s2[i[1]];
			i[1]++;
		}
	}
	dst[i[0]] = '\0';
	return (dst);
}

char	*ft_realoc_or_free(char *tmp, char *src, char **strs)
{
	char			*dst;
	unsigned int	i;

	if (strs && !src && !tmp)
	{
		i = 0;
		while (strs[i])
		{
			free(strs[i]);
			i++;
		}
		free(strs);
		return ((char *) NULL);
	}
	if (!src || !tmp)
		return ((char *) NULL);
	dst = ft_strjoin(tmp, src);
	free(tmp);
	return (dst);
}

char	*ft_strchr(const char *s, int c)
{
	char	to_find;

	to_find = (char)c;
	while (*s != '\0' && *s != to_find)
		s++;
	if (*s != to_find)
		return ((char *) NULL);
	return ((char *)s);
}
