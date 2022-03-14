/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpires-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 00:10:17 by jpires-p          #+#    #+#             */
/*   Updated: 2022/03/14 18:56:25 by jpires-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read_to_str(int fd);

static void	ft_process_lines(int fd, char ***file_strs, char *src);

static void	ft_save_lines(char **strs, char *src, unsigned int num_nl);

static int	ft_check_final_str(char ***fs, int fd, int size_of_strs);

char	*get_next_line(int fd)
{
	char		*temp;
	static char	***final_str;

	if (read(fd, 0, 0) == -1 || fd < 0 || fd > 1024 || BUFFER_SIZE < 1)
		return ((char *) NULL);
	temp = (char *) NULL;
	if (!final_str)
	{
		final_str = (char ***)malloc(sizeof(char **) * (MAX_FD + 1));
		final_str[MAX_FD] = (char **) NULL;
	}
	if (ft_check_final_str(final_str, fd, MAX_FD) == 1)
		return (*final_str[fd]);
	temp = ft_read_to_str(fd);
	if (!temp)
	{
		if (final_str[fd] && *final_str[fd])
			return (*final_str[fd]);
		return (temp);
	}
	ft_process_lines(fd, final_str, temp);
	free(temp);
	if (!*final_str[fd])
		return ((char *) NULL);
	return (*final_str[fd]);
}

static char	*ft_read_to_str(int fd)
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
		if (b_read <= 0 && !temp)
		{
			free(buff);
			return ((char *) NULL);
		}
		if (!temp)
			temp = ft_strjoin("", buff);
		else
			temp = ft_realoc_or_free(temp, buff, (char **) NULL);
		free(buff);
		if (ft_strchr(temp, '\n'))
			return (temp);
	}
	return (temp);
}

static void	ft_process_lines(int fd, char ***file_strs, char *src)
{
	unsigned int	i[2];
	char			*ptr;

	ptr = (char *) NULL;
	if (!file_strs[fd] || (!*file_strs[fd]))
		ptr = ft_strjoin("", src);
	else
		ptr = ft_strjoin(*file_strs[fd], src);
	i[0] = 0;
	i[1] = 0;
	while (ptr[i[0]] != '\0')
	{
		if (ptr[i[0]] == '\n')
			i[1]++;
		i[0]++;
	}
	if (!file_strs[fd])
		file_strs[fd] = (char **)malloc(sizeof(char *) * (i[1] + 2));
	else
	{
		ft_realoc_or_free((char *) NULL, (char *) NULL, file_strs[fd]);
		file_strs[fd] = (char **)malloc(sizeof(char *) * (i[1] + 2));
	}
	ft_save_lines(file_strs[fd], ptr, i[1]);
	free(ptr);
}

static void	ft_save_lines(char **strs, char *src, unsigned int num_nl)
{
	unsigned int	i[4];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	while (i[0] <= (num_nl + 1))
		strs[i[0]++] = (char *) NULL;
	i[0] = num_nl;
	i[0] = 0;
	while (src[i[0]] != '\0')
	{
		if (src[i[0]] == '\n')
		{
			if ((i[0] - i[2]) == 0)
				i[3] = 1;
			else
				i[3] = (i[0] - i[2]) + 1;
			strs[i[1]] = ft_substr(src, i[2], i[3]);
			i[2] = i[0] + 1;
			i[1]++;
		}
		i[0]++;
	}
	if (!strs[i[1]] && (i[0] - i[2]) > 0)
		strs[i[1]] = ft_substr(src, i[2], i[0] - i[2]);
}

static int	ft_check_final_str(char ***fs, int fd, int size_of_strs)
{
	int	i;

	if (!fs[size_of_strs])
	{
		fs[size_of_strs] = (char **)malloc(sizeof(char *));
		while (--size_of_strs >= 0)
			fs[size_of_strs] = (char **) NULL;
	}
	if (!fs[fd])
		return (0);
	if (fs[fd][1] == (char *) NULL)
	{
		fs[fd][0] = (char *) NULL;
		return (0);
	}
	i = 0;
	while (fs[fd][i + 1])
	{
		fs[fd][i] = ft_substr(fs[fd][i + 1], 0, ft_strlen(fs[fd][i + 1]));
		free(fs[fd][++i]);
	}
	fs[fd][i] = (char *) NULL;
	if (!ft_strchr(*fs[fd], '\n'))
		return (0);
	return (1);
}
