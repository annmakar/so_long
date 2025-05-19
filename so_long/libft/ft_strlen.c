/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: n <n@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:11:57 by annmakar          #+#    #+#             */
/*   Updated: 2025/05/18 03:08:00 by n                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (*str != '\0')
	{
		count++;
		str++;
	}
	return (count);
}

// int	main(void)
// {
// 	char	*pnt;
// 	char	str[6] = "asdfg";
// 	int	res;

// 	pnt = str;
// 	res = ft_strlen(pnt);
// 	printf("%d", res);
// 	return (0);
// }