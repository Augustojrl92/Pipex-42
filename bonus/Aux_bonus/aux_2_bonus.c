/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:03:39 by aurodrig          #+#    #+#             */
/*   Updated: 2024/10/12 23:03:10 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

static int	ft_count(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s[0] && s[0] != c)
	{
		count++;
		i++;
	}
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else if (i != 0 && s[i] != c && s[i - 1] == c)
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}

static char	**ft_freeall(char **tab, int k)
{
	while (k >= 0)
	{
		free(tab[k]);
		k--;
	}
	free(tab);
	return (NULL);
}

static char	**ft_strings(char **tab, char *s, char c)
{
	int	i;
	int	start;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (i == 0 && s[i] != c)
			start = 0;
		if (i == 0 && s[i] == c)
			i++;
		if (i && s[i - 1] == c && s[i] != c)
			start = i;
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			tab[j] = ft_substr(s, start, i - start + 1);
			if (!tab[j])
				return (ft_freeall(tab, j - 1));
			j++;
		}
		i++;
	}
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	int		count;
	char	**tab;

	if (!s)
		return (NULL);
	count = ft_count((char *)s, c);
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	tab[count] = 0;
	return (ft_strings(tab, (char *)s, c));
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}
