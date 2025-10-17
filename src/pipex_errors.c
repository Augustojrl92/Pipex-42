/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:53:22 by aurodrig          #+#    #+#             */
/*   Updated: 2024/10/13 15:42:39 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_print_error_and_exit(char *message)
{
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
	exit(EXIT_FAILURE);
}

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	ft_free_resources_exit(char *msg_1, char *msg_2, t_context *context)
{
	ft_putstr_fd(msg_1, 2);
	if (msg_2 != NULL)
	{
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(msg_2, 2);
	}
	ft_putstr_fd("\n", 2);
	ft_free_matrix(context->env_path);
	exit(127);
}
