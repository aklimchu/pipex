/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:31:32 by aklimchu          #+#    #+#             */
/*   Updated: 2024/08/29 12:58:16 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <sys/types.h>
# include <fcntl.h>
# include <stdio.h>	//perror
# include <sys/wait.h> // waitpid
# include <errno.h> // do we need?

typedef struct s_fd
{
	int		pipe[1024][2];
	int		in;
	int		out;
	int		status;
}				t_fd;

char	*ft_strjoin_new(char const *s1, char const *s2, char const *s3);
char	*check_path(char *envp[], char **param);
char	**check_param(char *str);
void	free_all(char **arr_1, char **arr_2, char *str);
void	child_process(char *argv[], char **envp, t_fd fd, int i);
int		last_process(char **argv, char **envp, int pipe[2], int i);
void	printing(char *cmd, char *result, int fd);
void	printing_nop(char *cmd, char *result, int fd);
int		is_directory(char *path);
char	*str_filter(char *str, char *set);
char	**ft_split_new(char const *s, char c, int str_num);
int		count_param(char *str);
void	close_fds(int fd1, int fd2, int fd3);

#endif /* PIPEX_H */