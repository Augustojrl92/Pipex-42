/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:55:05 by aurodrig          #+#    #+#             */
/*   Updated: 2024/10/12 20:48:51 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_context
{
	char	**env_path;
	int		infile_fd;
	int		outfile_fd;
	int		pipe_fds[2];
	int		command_founnd;
}	t_context;

void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char	*dest, const char *src, size_t dstsize);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
void	*ft_memset(void *ptr, int c, size_t n);
void	ft_bzero(void *s, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);

void	ft_print_error_and_exit(char *message);
void	ft_free_matrix(char **matrix);
void	ft_free_resources_exit(char *msg_1, char *msg_2, t_context *context);
void	ft_validate_file(int argc, char **argv);
void	ft_get_env_paths(char **env, t_context *context);
void	ft_get_path_comand(t_context *context, char *command, char **env);
void	ft_first_child_process(t_context *context, char **argv, char **env);
void	ft_second_child_process(t_context *context, char **argv, char **env);
void	ft_father_pipex(t_context *context, char **argv, char **env);
void	ft_handle_pipe_dup(int pipe_fd[2], int std_fd);
void	ft_open_output_file(t_context *context, char **argv);
void	ft_open_input_file(t_context *context, char **argv);
void	execute_command(t_context *context, char *command, char **env);

#endif