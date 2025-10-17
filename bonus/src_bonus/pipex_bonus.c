/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:55:51 by aurodrig          #+#    #+#             */
/*   Updated: 2024/10/13 15:37:52 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

void	ft_waitpids(t_context *context)
{
	int		i;
	int		status;

	i = ((status = 0), 0);
	while (i < context->cmd_count)
	{
		waitpid(context->pids[i], &status, 0);
		i++;
	}
	exit(WEXITSTATUS(status));
}

void	ft_allocte_pids(t_context *context)
{
	context->pids = malloc(sizeof(pid_t) * (context->cmd_count));
	if (!context->pids)
		ft_free_exit("Memory allocation for pids failed", NULL, 1, context);
}

void	ft_allocte_pipes(t_context *context)
{
	int	i;

	i = 0;
	context->pipe_fds = malloc(sizeof(int *) * (context->cmd_count - 1));
	if (!context->pipe_fds)
		ft_free_exit("Memory allocation for pipes failed", NULL, 1, context);
	while (i < context->cmd_count -1)
	{
		context->pipe_fds[i] = malloc(sizeof(int) * 2);
		if (!context->pipe_fds[i] || pipe(context->pipe_fds[i]) == -1)
			ft_free_exit("Pipe allocation failed", NULL, 1, context);
		i++;
	}
}

void	ft_father_pipex(t_context *context, char **argv, char **env)
{
	int		i;

	i = 0;
	while (i < context->cmd_count)
	{
		context->pids[i] = fork();
		if (context->pids[i] == -1)
			ft_free_exit("Fork error", NULL, 1, context);
		if (context->pids[i] == 0)
		{
			if (i == 0)
				ft_first_child_process(context, argv, env);
			else if (i == context->cmd_count - 1)
				lastchild_process(i, context, argv, env);
			else
				midchild_process(i, context, argv, env);
		}
		i++;
	}
	ft_fd_close(context, i);
	if (context->is_here_doc == 1)
		free(context->limiter);
	(ft_fd_free(context), unlink(".tmp"));
	ft_waitpids(context);
}

int	main(int argc, char **argv, char **env)
{
	t_context	context;
	int			i;

	i = 0;
	ft_bzero(&context, sizeof(t_context));
	context.arg_count = argc;
	if (argc < 5)
		ft_print_error_and_exit("Invalid number of arguments");
	while (i < argc)
		if (!argv[i++][0])
			ft_print_error_and_exit("Invalid arguments");
	ft_validate_file(argc, argv);
	ft_check_here_doc(argc, argv, &context);
	ft_allocte_pipes(&context);
	ft_allocte_pids(&context);
	ft_father_pipex(&context, argv, env);
	return (0);
}
