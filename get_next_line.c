/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpires-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 20:00:08 by jpires-p          #+#    #+#             */
/*   Updated: 2022/03/29 21:05:47 by jpires-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char		**buffer;
	char			*str_w_nl;
	unsigned int	i;

	if (read(fd, 0, 0) == -1 || fd < 0 || BUFFER_SIZE < 1)
		return ((char *) NULL);
	if (buffer == (char **) NULL)
	{
		buffer = (char **)malloc(sizeof(char *) * (MAX_FD + 1));
		i = -1;
		while (++i <= MAX_FD)
			buffer[i] = (char *) NULL;
	}
	buffer[fd] = ft_realloc_strjoin(buffer[fd], ft_read_to_str(fd));
	str_w_nl = ft_process_line(buffer[fd]);
	if (ft_check_null_and_free(str_w_nl, buffer, fd) == 0)
	{
		free(buffer);
		buffer = (char **) NULL;
		return ((char *) NULL);
	}
	buffer[fd] = ft_get_buff_after_nl(buffer[fd], ft_strlen(str_w_nl));
	return (str_w_nl);
}

char	*ft_read_to_str(int fd)
{
	ssize_t	b_read;
	char	*temp;
	char	*buff;

	temp = (char *) NULL;
	b_read = 1;
	while (b_read > 0)
	{
		buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		b_read = read(fd, buff, BUFFER_SIZE);
		buff[b_read] = '\0';
		if (b_read <= 0 && temp == (char *) NULL)
		{
			free(buff);
			return ((char *) NULL);
		}
		temp = ft_realloc_strjoin(temp, buff);
		if (ft_strchr(temp, '\n'))
			return (temp);
	}
	return (temp);
}

char	*ft_process_line(const char *str)
{
	char			*dst;
	unsigned int	i;

	if (str == (char *) NULL || *str == '\0')
		return ((char *) NULL);
	dst = (char *) NULL;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
		{
			dst = ft_substr(str, 0, i + 1);
			return (dst);
		}
		i++;
	}
	dst = ft_substr(str, 0, i);
	return (dst);
}

char	*ft_get_buff_after_nl(char *str_to_trim, unsigned int size_to_trim)
{
	char			*str;
	unsigned int	size_of_str;

	if (str_to_trim == (char *) NULL || *str_to_trim == '\0'
		|| size_to_trim < 1)
	{
		if (str_to_trim != (char *) NULL)
			free(str_to_trim);
		return ((char *) NULL);
	}
	str = (char *) NULL;
	size_of_str = ft_strlen(str_to_trim);
	str = ft_substr(str_to_trim, size_to_trim, (size_of_str - size_to_trim));
	free(str_to_trim);
	str_to_trim = (char *) NULL;
	return (str);
}

int	ft_check_null_and_free(char *p, char **p2p, int fd)
{
	unsigned int	i;

	if (p == (char *) NULL || *p2p[fd] == '\0')
	{
		free(p);
		p = (char *) NULL;
		i = 0;
		while (i <= MAX_FD)
		{
			if (p2p[i] != (char *) NULL)
			{
				free(p2p[i]);
				p2p[i] = (char *) NULL;
			}
			i++;
		}
		return (0);
	}
	return (1);
}
