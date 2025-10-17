/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:58:05 by aurodrig          #+#    #+#             */
/*   Updated: 2024/10/13 15:42:05 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_father_pipex(t_context *context, char **argv, char **env)
{
	pid_t	pid[2];
	int		status;

	status = 0;
	if (pipe(context->pipe_fds) == -1)
		ft_free_resources_exit("Pipe error", NULL, context);
	pid[0] = fork();
	if (pid[0] == 0)
		ft_first_child_process(context, argv, env);
	else if (pid[0] < 0)
		ft_free_resources_exit("Fork error", NULL, context);
	pid[1] = fork();
	if (pid[1] == 0)
		ft_second_child_process(context, argv, env);
	else if (pid[1] < 0)
		ft_free_resources_exit("Fork error", NULL, context);
	close(context->pipe_fds[0]);
	close(context->pipe_fds[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], &status, 0);
	exit (WEXITSTATUS(status));
}

int	main(int argc, char **argv, char **env)
{
	t_context	context;
	int			i;

	i = 0;
	if (argc != 5)
		ft_print_error_and_exit("Invalid number of arguments");
	while (i < argc)
		if (!argv[i++][0])
			ft_print_error_and_exit("Invalid arguments");
	ft_validate_file(argc, argv);
	ft_bzero(&context, sizeof(t_context));
	ft_father_pipex(&context, argv, env);
	return (0);
}
