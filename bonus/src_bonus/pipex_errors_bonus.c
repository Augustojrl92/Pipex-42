/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:26:01 by aurodrig          #+#    #+#             */
/*   Updated: 2024/10/12 23:36:00 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

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

void	ft_fd_free(t_context *context)
{
	int	i;

	i = 0;
	while (i < context->cmd_count -1)
	{
		free(context ->pipe_fds[i]);
		i++;
	}
	free(context->pipe_fds);
}

void	ft_free_exit(char *msg_1, char *msg_2, int code, t_context *context)
{
	ft_putstr_fd(msg_1, 2);
	ft_putstr_fd(msg_2, 2);
	ft_putstr_fd("\n", 2);
	ft_free_matrix(context->env_path);
	ft_fd_free(context);
	exit(code);
}

void	ft_fd_close(t_context *context, int j)
{
	int	i;

	i = 0;
	while (i <= j && i < context->cmd_count - 1)
	{
		close(context->pipe_fds[i][0]);
		close(context->pipe_fds[i][1]);
		i++;
	}
}
