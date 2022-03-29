/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpires-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 20:00:06 by jpires-p          #+#    #+#             */
/*   Updated: 2022/03/29 21:04:29 by jpires-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FD
#  define MAX_FD 1025
# endif

/* ***************GNL************ */
char	*get_next_line(int fd);
char	*ft_read_to_str(int fd);
char	*ft_process_line(const char *str);
char	*ft_get_buff_after_nl(char *str_to_trim, unsigned int size_to_trim);
int		ft_check_null_and_free(char *p, char **p2p, int fd);

/* ***************UTILS************ */
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_realloc_strjoin(char *tmp, char *src);

#endif