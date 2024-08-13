/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:21:22 by aklimchu          #+#    #+#             */
/*   Updated: 2024/05/22 09:56:41 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The function received a file descriptor for the file to be open.
// Then it calls "read_file" to read the file and puts the result
// to the static variable "stash".
// After that "line" is extracted from "stash" and returned to the user.

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (free_mem(&stash, NULL));
	line = NULL;
	stash = read_file(fd, stash);
	if (stash == NULL)
		return ((void *) 0);
	if (ft_strchr(stash, 10) == NULL)
	{
		line = ft_strdup(stash);
		free(stash);
		stash = NULL;
	}
	else if (ft_strchr(stash, 10))
	{
		line = ft_substr(stash, 0, ft_strlen(stash) - \
				ft_strlen(ft_strchr(stash, 10)) + 1);
		if (line == NULL)
			return (free_mem(&stash, NULL));
		stash = trim_stash(stash);
	}
	return (line);
}

// The function allocates the buffer and reads from the file pointed
// by the file descriptor.
// After that needed amount of memory is allocated to variable "stash"
// using the function add_memory.
// Data from the buffer is copied to "stash" using ft_strncat.

char	*read_file(int fd, char *stash)
{
	char		*buffer;
	int			bytes_read;

	bytes_read = 1;
	while (ft_strchr(stash, 10) == NULL && bytes_read)
	{
		buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (buffer == NULL)
			return (free_mem(&stash, buffer));
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1 || (bytes_read == 0 && stash == NULL))
			return (free_mem(&stash, buffer));
		*(buffer + bytes_read) = '\0';
		stash = add_memory(stash, bytes_read);
		if (stash == NULL)
			return (free_mem(&stash, buffer));
		stash = ft_strncat(stash, buffer, ft_strlen(stash) + \
				ft_strlen(buffer) + 1);
		free(buffer);
	}
	return (stash);
}

// The function frees the memory and sets the pointers to NULL.

char	*free_mem(char **stash, char *buffer)
{
	if (*stash)
		free(*stash);
	*stash = NULL;
	if (buffer)
		free(buffer);
	buffer = NULL;
	return ((void *) 0);
}

// The function frees the old "stash" and allocates new
// memory depending on the number of bytes read in read_file.

char	*add_memory(char *stash, size_t i)
{
	char	*temp;
	size_t	slen;

	if (stash == NULL)
		stash = ft_strdup("");
	if (stash == NULL)
		return (free_mem(&stash, NULL));
	slen = ft_strlen(stash);
	temp = (char *)malloc(slen + i + 1);
	if (temp == NULL)
		return (free_mem(&stash, NULL));
	while (*stash)
	{
		*temp = *stash;
		temp++;
		stash++;
	}
	*temp = '\0';
	free(stash - slen);
	return (temp - slen);
}

// The function frees old "stash" and allocates new memory
// depending on the number of characters left after '\n'
// character.
// These characters are also copied to newly allocated "stash".

char	*trim_stash(char *s)
{
	char	*new_s;
	size_t	slen;
	size_t	newlen;

	slen = ft_strlen(s);
	newlen = ft_strlen(ft_strchr(s, 10)) - 1;
	new_s = (char *)malloc(newlen + 1);
	if (newlen == 0 || new_s == NULL)
		return (free_mem(&new_s, s));
	while (*s != '\n' && *s)
		s++;
	if (*s)
		s++;
	while (*s)
	{
		*new_s = *s;
		new_s++;
		s++;
	}
	*new_s = '\0';
	free (s - slen);
	return (new_s - newlen);
}
