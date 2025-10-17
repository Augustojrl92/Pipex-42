/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:07:09 by aurodrig          #+#    #+#             */
/*   Updated: 2024/10/13 15:22:53 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_validate_file(int argc, char **argv)
{
	int	output_file;

	output_file = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (output_file < 0)
	{
		perror("Invalid output_file");
		exit(EXIT_FAILURE);
	}
	close(output_file);
}

void	ft_get_env_paths(char **env, t_context *context)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			context->env_path = ft_split(env[i] + 5, ':');
			if (!context->env_path)
				ft_free_resources_exit("Memory failed", NULL, context);
			break ;
		}
		i++;
	}
	if (!context->env_path)
		context->command_founnd = 2;
}

void	execute_command(t_context *context, char *command, char **env)
{
	char	**command_flags;

	command_flags = ft_split(command, ' ');
	if (!command_flags || command_flags[0] == NULL)
	{
		if (command_flags)
			ft_free_matrix(command_flags);
		ft_free_resources_exit("Memory allocation failed", NULL, context);
	}
	if ((access(command_flags[0], F_OK | X_OK) == 0)
		&& (ft_strnstr(command_flags[0], "./", 2)
			|| command_flags[0][0] == '/'))
	{
		execve(command_flags[0], command_flags, env);
		ft_free_matrix(command_flags);
		ft_free_resources_exit("Execution failed command: ", command, context);
	}
	else if (ft_strchr(command_flags[0], '/') != NULL)
	{
		ft_free_matrix(command_flags);
		ft_free_resources_exit("Invalid command: ", command, context);
	}
	else
		ft_get_path_comand(context, command, env);
	ft_free_matrix(command_flags);
}

char	*find_command_path(t_context *context, char *command)
{
	int		i;
	char	*full_path;
	char	*temp_path;

	i = 0;
	while (context->env_path && context->env_path[i])
	{
		temp_path = ft_strjoin(context->env_path[i], "/");
		full_path = ft_strjoin(temp_path, command);
		free(temp_path);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

void	ft_get_path_comand(t_context *context, char *command, char **env)
{
	char	**command_flags;
	char	*full_path;

	command_flags = ft_split(command, ' ');
	if (!command_flags || command_flags[0] == NULL)
	{
		if (command_flags)
			ft_free_matrix(command_flags);
		ft_free_resources_exit("Memory failed in get path", NULL, context);
	}
	full_path = find_command_path(context, command_flags[0]);
	if (full_path != NULL)
	{
		execve(full_path, command_flags, env);
		free(full_path);
		ft_free_matrix(command_flags);
		ft_free_resources_exit("Failed for command: ", command, context);
	}
	ft_free_matrix(command_flags);
	ft_free_resources_exit("Command not found: ", command, context);
}
