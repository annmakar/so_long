/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annmakar <annmakar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:11:57 by annmakar          #+#    #+#             */
/*   Updated: 2025/05/25 22:01:43 by annmakar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	count;

	if (!str)
		return (0);
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