/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annmakar <annmakar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:06:14 by annmakar          #+#    #+#             */
/*   Updated: 2025/05/25 17:58:28 by annmakar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <sys/types.h>
# include <sys/uio.h>
# include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2);
char	*get_next_line(int fd);
char	*ft_next(char *buffer);
char	*ft_free(char *buffer, char *buf);
void	*ft_calloc(size_t nmemb, size_t size);
char	*read_file(int fd, char *res);
void	*ft_bzero(void *s, size_t n);
char	*ft_strchr(const char *s, int c);

#endif