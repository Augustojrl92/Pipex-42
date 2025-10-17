/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_here_doc_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:47:34 by aurodrig          #+#    #+#             */
/*   Updated: 2024/09/24 13:44:58 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

void	ft_create_here_doc_file(t_context *context)
{
	char	*line;
	char	*limiter_nl;

	context->infile_fd = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		limiter_nl = ft_strjoin(context->limiter, "\n");
		if (ft_strncmp(limiter_nl, line, ft_strlen(limiter_nl)) == 0)
		{
			free(limiter_nl);
			break ;
		}
		free(limiter_nl);
		ft_putstr_fd(line, context->infile_fd);
		free(line);
	}
	free(line);
	close(context->infile_fd);
}

void	ft_check_here_doc(int argc, char **argv, t_context *context)
{
	int	i;

	i = -1;
	while (++i < argc - 1)
	{
		if (argv[i] == 0)
			ft_print_error_and_exit("Empty argument");
	}
	if (!ft_strcmp(argv[1], "here_doc") && argc > 5)
	{
		context->is_here_doc = 1;
		context->limiter = ft_strdup(argv[2]);
		context->cmd_count = argc - 4;
		context->first_cmd_index = 3;
		ft_create_here_doc_file(context);
		ft_validate_file(argc, argv);
	}
	else if (argc > 4)
	{
		ft_validate_file(argc, argv);
		context->cmd_count = argc - 3;
		context->first_cmd_index = 2;
	}
}
