/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annmakar <annmakar@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:19:50 by annmakar          #+#    #+#             */
/*   Updated: 2024/11/30 15:46:03 by annmakar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	ft_putnbr(long nb)
{
	long	num;
	int		len;

	len = 0;
	if (nb < 0)
	{
		write(1, "-", 1);
		len++;
		nb = -nb;
	}
	if (nb > 9)
	{
		len += ft_putnbr(nb / 10);
	}
	num = (nb % 10) + '0';
	write(1, &num, 1);
	len++;
	return (len);
}

int	ft_putnbr_hexa(unsigned long nbr, char up)
{
	int		len;
	char	*base;
	int		aux;

	len = 0;
	if (up == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (nbr > 15)
	{
		aux = ft_putnbr_hexa(nbr / 16, up);
		if (aux == -1)
			return (-1);
		len += aux;
	}
	if (write(1, &base[nbr % 16], 1) == -1)
		return (-1);
	return (len + 1);
}

int	ft_putptr(void *ptr)
{
	int	len;
	int	aux;

	len = 0;
	aux = 0;
	if (!ptr)
	{
		if (write (1, "(nil)", 5) == -1)
			return (-1);
		return (5);
	}
	if (ft_putstr("0x") == -1)
		return (-1);
	len += 2;
	aux = ft_putnbr_hexa((unsigned long)ptr, 'x');
	if (aux == -1)
		return (-1);
	len += aux;
	return (len);
}

int	ft_putstr(char *str)
{
	int	len;

	if (!str)
	{
		if (write (1, "(null)", 6) == -1)
			return (-1);
		return (6);
	}
	len = 0;
	while (*str != '\0')
	{
		if (write(1, str, 1) == -1)
			return (-1);
		len++;
		str++;
	}
	return (len);
}

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}
