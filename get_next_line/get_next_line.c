/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: n <n@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:01:19 by annmakar          #+#    #+#             */
/*   Updated: 2025/05/18 03:03:45 by n                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	if (!temp)
		return (buffer);
	free(buffer);
	return (temp);
}

char	*ft_next(char *buffer)
{
	int		i;
	int		j;
	char	*l;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	l = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	if (!l)
	{
		free(buffer);
		return (NULL);
	}
	i++;
	while (buffer[i])
		l[j++] = buffer[i++];
	l[j] = '\0';
	free(buffer);
	return (l);
}

char	*ft_line(char *buffer)
{
	char	*l;
	int		i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	l = ft_calloc(i + 1, sizeof(char));
	if (!l)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		l[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		l[i++] = '\n';
	l[i] = '\0';
	return (l);
}

char	*read_file(int fd, char *res)
{
	char	*buffer;
	int		br;

	if (!res)
		res = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (free(res), NULL);
	br = 1;
	while (br > 0)
	{
		br = read(fd, buffer, BUFFER_SIZE);
		if (br == -1)
		{
			free(buffer);
			free(res);
			return (NULL);
		}
		buffer[br] = '\0';
		res = ft_free(res, buffer);
		if (br == 0 || ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*l;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	l = ft_line(buffer);
	if (!l)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = ft_next(buffer);
	if (!l[0])
	{
		free(l);
		l = NULL;
	}
	return (l);
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main()
// {
// 	int	fd = open("a.txt", O_RDONLY);
// 	printf("Line: %d\n", fd);
// 	char *line;

// 	if (fd < 0)
// 	{
// 		printf("error");
// 		return (1);
// 	}

// 	line = get_next_line(fd);
// 	printf("Line: %s\n", line);
// 	while (line != NULL)
// 	{
// 		printf("Line: %s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	return (0);
// }