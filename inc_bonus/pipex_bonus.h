/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:31:32 by aklimchu          #+#    #+#             */
/*   Updated: 2024/09/09 08:21:45 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <sys/types.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_fd
{
	int		pipe[2];
	int		in;
	int		out;
	int		status;
	int		cmd_num;
	char	*delim;
	char	*hd_input;
	int		hd_flag;
	pid_t	*null;
	pid_t	*pid;
}				t_fd;

char	*ft_strjoin_new(char const *s1, char const *s2, char const *s3);
char	*check_path(char *envp[], char **param, t_fd fd);
char	**check_param(char *str, t_fd fd);
int		free_all(char **arr_1, char **arr_2, char *str, pid_t **pid);
void	child_process(char *argv[], char **envp, t_fd fd, int i);
void	last_process(char **argv, char **envp, t_fd fd, int i);
void	printing(char *cmd, char *result, int fd);
void	printing_nop(char *cmd, char *result, int fd);
int		is_directory(char *path, t_fd fd, int fd_pipe, char **param);
void	check_command_access(char **param, t_fd fd);
char	*str_filter(char *str, char *set);
char	**ft_split_new(char const *s, char c, int str_num);
int		count_param(char *str);
int		close_free(int fd1, int fd2, int fd3, pid_t **pid);
int		pipe_and_fork(t_fd *fd, char *argv[], char *envp[], int i);
int		last_fork(t_fd *fd, char *argv[], char *envp[], int i);
int		free_pid(pid_t **pid);
int		here_doc(int argc, char *argv[], t_fd *fd);
size_t	ft_strchr_fix(const char *s, int c);
int		free_str(char *str1, char *str2);

#endif /* PIPEX_BONUS_H */