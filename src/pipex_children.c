/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_children.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:14:37 by aurodrig          #+#    #+#             */
/*   Updated: 2024/10/13 14:46:00 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_open_input_file(t_context *context, char **argv)
{
	int	input_fd;

	input_fd = open(argv[1], O_RDONLY);
	if (input_fd < 0)
	{
		perror("Error opening input file");
		close(context->pipe_fds[0]);
		close(context->pipe_fds[1]);
		exit(EXIT_FAILURE);
	}
	if (dup2(input_fd, STDIN_FILENO) < 0)
	{
		perror("dup2 input_fd error");
		close(input_fd);
		close(context->pipe_fds[0]);
		close(context->pipe_fds[1]);
		exit(EXIT_FAILURE);
	}
	close(input_fd);
}

void	ft_open_output_file(t_context *context, char **argv)
{
	int	output_fd;

	output_fd = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (output_fd < 0)
	{
		perror("Error opening output file");
		close(context->pipe_fds[0]);
		close(context->pipe_fds[1]);
		exit(1);
	}
	if (dup2(output_fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 output_fd error");
		close(output_fd);
		close(context->pipe_fds[0]);
		close(context->pipe_fds[1]);
		exit(EXIT_FAILURE);
	}
	close(output_fd);
}

void	ft_handle_pipe_dup(int pipe_fd[2], int std_fd)
{
	if (std_fd == 0)
	{
		if (dup2(pipe_fd[0], STDIN_FILENO) < 0)
		{
			perror("dup2 pipe_fds[0] to STDIN error");
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
		{
			perror("dup2 pipe_fds[1] to STDOUT error");
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			exit(EXIT_FAILURE);
		}
	}
}

void	ft_first_child_process(t_context *context, char **argv, char **env)
{
	ft_get_env_paths(env, context);
	ft_open_input_file(context, argv);
	ft_handle_pipe_dup(context->pipe_fds, 1);
	close(context->pipe_fds[0]);
	close(context->pipe_fds[1]);
	execute_command(context, argv[2], env);
}

void	ft_second_child_process(t_context *context, char **argv, char **env)
{
	ft_get_env_paths(env, context);
	ft_handle_pipe_dup(context->pipe_fds, 0);
	ft_open_output_file(context, argv);
	close(context->pipe_fds[0]);
	close(context->pipe_fds[1]);
	execute_command(context, argv[3], env);
}
