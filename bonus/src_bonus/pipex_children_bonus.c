/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_children_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:55:21 by aurodrig          #+#    #+#             */
/*   Updated: 2024/10/13 15:04:30 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

void	ft_first_child_process(t_context *context, char **argv, char **env)
{
	ft_get_env_paths(env, context);
	if (context->is_here_doc == 1)
		context->infile_fd = open(".tmp", O_RDONLY);
	else if (context->is_here_doc == 0)
		context->infile_fd = open(argv[1], O_RDONLY);
	if (dup2(context->pipe_fds[0][1], STDOUT_FILENO) < 0)
		ft_free_exit("dup error 0", NULL, 1, context);
	if (dup2(context->infile_fd, STDIN_FILENO) < 0)
		ft_free_exit("invalid input file\n", NULL, 1, context);
	close(context->infile_fd);
	ft_fd_close(context, context->cmd_count - 1);
	execute_command(context, argv[context->first_cmd_index], env);
}

void	midchild_process(int i, t_context *context, char **argv, char **env)
{
	ft_get_env_paths(env, context);
	if (dup2(context->pipe_fds[i - 1][0], STDIN_FILENO) < 0)
		ft_free_exit("dup error 2", NULL, 1, context);
	if (dup2(context->pipe_fds[i][1], STDOUT_FILENO) < 0)
		ft_free_exit("dup error 3", NULL, 1, context);
	ft_fd_close(context, context->cmd_count - 1);
	execute_command(context, argv[i + 2], env);
}

void	lastchild_process(int i, t_context *context, char **argv, char **env)
{
	ft_get_env_paths(env, context);
	if (context->is_here_doc == 1)
		context->outfile_fd = open(argv[context->arg_count - 1],
				O_APPEND | O_WRONLY | O_CREAT, 0644);
	else
		context->outfile_fd = open(argv[context->arg_count - 1],
				O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (context->outfile_fd < 0)
		ft_free_exit("Failed to open outfile", NULL, 1, context);
	if (dup2(context->pipe_fds[i - 1][0], STDIN_FILENO) < 0)
		ft_free_exit("dup error 4 for stdin", NULL, 1, context);
	close(context->pipe_fds[i - 1][0]);
	if (dup2(context->outfile_fd, STDOUT_FILENO) < 0)
		ft_free_exit("dup error 4 for stdout", NULL, 1, context);
	close(context->outfile_fd);
	ft_fd_close(context, i);
	execute_command(context, argv[context->arg_count - 2], env);
}
