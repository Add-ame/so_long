/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddame <maddame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 19:54:57 by maddame           #+#    #+#             */
/*   Updated: 2025/01/21 09:52:08 by maddame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*ft_strdup_itoa(char *buf, int i, int sign)
{
	char	*p;
	int		j;
	int		len;

	if (sign)
		len = i + 1;
	else
		len = i;
	p = malloc(len + 1);
	if (p == NULL)
		return (NULL);
	j = 0;
	if (sign)
		p[j++] = '-';
	while (i--)
		p[j++] = buf[i];
	p[j] = '\0';
	return (p);
}

char	*ft_itoa(int n)
{
	char	buf[11];
	char	*pt;
	long	nb;
	int		i;
	int		sign;

	i = 0;
	sign = 0;
	nb = n;
	if (n < 0)
	{
		sign = 1;
		nb *= -1;
	}
	else if (n == 0)
		buf[i++] = '0';
	while (nb)
	{
		buf[i++] = nb % 10 + 48;
		nb /= 10;
	}
	buf[i] = '\0';
	pt = ft_strdup_itoa(buf, i, sign);
	return (pt);
}

int	close_win(t_data *d)
{
	(write(1, MAG, 5), write(2, "Windows Closed\n", 15), write(1, RESET, 4));
	cleaning(d);
	exit(0);
}

int	ft_strchr_1(const char *s, int c)
{
	while (*s)
	{
		if ((char)c == *s)
			return (1);
		s++;
	}
	return (0);
}
