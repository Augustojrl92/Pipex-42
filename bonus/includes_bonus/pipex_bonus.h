/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:41:00 by aurodrig          #+#    #+#             */
/*   Updated: 2024/10/12 23:05:41 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_context
{
	char	**env_path;
	int		infile_fd;
	int		outfile_fd;
	int		first_cmd_index;
	int		arg_count;
	int		cmd_count;
	int		is_here_doc;
	int		**pipe_fds;
	pid_t	*pids;
	int		command_founnd;
	char	*limiter;
	int		code;
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
char	*ft_strdup(const char *str);
int		ft_strcmp(char *s1, char *s2);
char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);

void	ft_print_error_and_exit(char *message);
void	ft_free_matrix(char **matrix);
void	ft_free_exit(char *msg_1, char *msg_2, int code, t_context *context);
void	ft_validate_file(int argc, char **argv);
void	ft_get_env_paths(char **env, t_context *context);
void	execute_command(t_context *context, char *command, char **env);
void	ft_first_child_process(t_context *context, char **argv, char **env);
void	ft_father_pipex(t_context *context, char **argv, char **env);
void	ft_fd_close(t_context *context, int j);
void	ft_fd_free(t_context *context);
void	ft_check_here_doc(int argc, char **argv, t_context *context);
void	ft_allocte_pipes(t_context *context);
void	midchild_process(int i, t_context *context, char **argv, char **env);
void	lastchild_process(int i, t_context *context, char **argv, char **env);
void	ft_allocte_pids(t_context *context);
void	ft_get_path_comand(t_context *context, char *command, char **env);
char	*find_command_path(t_context *context, char *command);

#endif