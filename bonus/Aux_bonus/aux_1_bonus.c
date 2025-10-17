/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_1_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:34:31 by aurodrig          #+#    #+#             */
/*   Updated: 2024/10/12 13:37:20 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	write(fd, &s[i], ft_strlen(s));
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	*ft_memset(void *ptr, int c, size_t n)
{
	unsigned char	*s;
	size_t			i;

	s = ptr;
	i = 0;
	while (i < n)
	{
		s[i] = (unsigned char) c;
		i++;
	}
	return (s);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

char	*get_next_line(int fd)
{
	char	c;
	char	*str;
	char	*tmp;
	char	*aux;

	str = malloc(1 * sizeof(char));
	str[0] = 0;
	while (read(fd, &c, 1) > 0)
	{
		aux = str;
		tmp = malloc(2 * sizeof(char));
		tmp[0] = c;
		tmp[1] = 0;
		str = ft_strjoin(str, tmp);
		free(tmp);
		free(aux);
		if (c == '\n')
			break ;
	}
	return (str);
}
