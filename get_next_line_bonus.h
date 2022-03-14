/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpires-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 00:10:29 by jpires-p          #+#    #+#             */
/*   Updated: 2022/03/11 20:59:27 by jpires-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

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
void	ft_process_lines(int fd, char ***file_strs, char *src);
void	ft_save_lines(char **strs, char *src, unsigned int num_nl);
int		ft_check_final_str(char ***file_strs, int fd, int size_of_strs);

/* ***************UTILS************ */
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_realoc_or_free(char *tmp, char *src, char **strs);

#endif