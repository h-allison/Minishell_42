/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:21:09 by hallison          #+#    #+#             */
/*   Updated: 2025/03/24 17:16:18 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

	File descriptors are an index into a file descriptor table stored
	by the kernel. The kernel creates a fd in response to an 'open()' call

		int fd = open(something);

	... and associates the file descriptor with some abstraction of an
	underlying file-like object.

	0 = Standard input (input from the keyboard) = STDIN_FILENO
	1 = Standard output (output to the console) = STDOUT_FILENO
	2 = Standard error (error output to the console) = STDERR_FILENO

	Every program starts with these 3 files already opened.

	READ()
	--------
	read() returns an integer
	ssize_t	read(int fd, void *buf, size_t count);

	read() attempts to read up to count bytes from the fd
	into the buffer starting at buf.

	On success, the number of bytes read is returned (0 = end of file)
	and the file position is advanced by this number.
	It is not an error if this number is smaller than the number of
	bytes requested.

	On error, -1 is returned.

*/

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);

static char	*gnl_realloc(char *ptr, size_t size)
{
	char	*new_ptr;
	size_t	i;

	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	i = 0;
	while (i < size && ptr[i] != '\0')
	{
		new_ptr[i] = ptr[i];
		i++;
	}
	new_ptr[i] = '\0';
	free(ptr);
	ptr = NULL;
	return (new_ptr);
}

static char	*add_to_tb(char *tb, char *just_read, int bytes_read, int fd)
{
	while (!ft_strchr(tb, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, just_read, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(tb);
			free(just_read);
			return (NULL);
		}
		just_read[bytes_read] = '\0';
		tb = gnl_realloc(tb, ft_strlen(tb) + BUFFER_SIZE + 1);
		if (!tb)
		{
			free(tb);
			free(just_read);
			return (NULL);
		}
		ft_strlcat(tb, just_read, ft_strlen(tb) + BUFFER_SIZE + 1);
	}
	free (just_read);
	return (tb);
}

static char	*fill_temp_buff(char *tb, int fd)
{
	char	*just_read;
	int		bytes_read;

	just_read = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!just_read)
		return (NULL);
	bytes_read = 1;
	if (!tb)
		return (NULL);
	if (tb[0] == '\0')
	{
		bytes_read = read(fd, tb, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(tb);
			free(just_read);
			return (NULL);
		}
		if (bytes_read < BUFFER_SIZE)
			tb[bytes_read] = '\0';
		else
			tb[BUFFER_SIZE] = '\0';
	}
	tb = add_to_tb(tb, just_read, bytes_read, fd);
	return (tb);
}

static char	*trim_temp_buff(char *temp_buff)
{
	char		*finalstring;
	size_t		i;
	size_t		leftlen;

	if (!temp_buff)
		return (NULL);
	i = 0;
	while (temp_buff[i] != '\n' && temp_buff[i] != '\0')
		i++;
	if (temp_buff[i] == '\0')
		i--;
	finalstring = malloc((i + 2) * sizeof(char));
	if (!finalstring)
		return (NULL);
	finalstring = ft_memcpy(finalstring, temp_buff, i + 1);
	finalstring[i + 1] = '\0';
	leftlen = ft_strlen(temp_buff) - i;
	temp_buff = ft_memcpy(temp_buff, temp_buff + i + 1, leftlen);
	temp_buff[leftlen] = '\0';
	return (finalstring);
}

char	*get_next_line(int fd)
{
	static char	*temp_buff;
	char		*final_string;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (temp_buff == NULL)
	{
		temp_buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!temp_buff)
			return (NULL);
		temp_buff[0] = '\0';
	}
	temp_buff = fill_temp_buff(temp_buff, fd);
	if (!temp_buff)
	{
		free (temp_buff);
		return (NULL);
	}
	final_string = trim_temp_buff(temp_buff);
	if (final_string == NULL)
	{
		free(temp_buff);
		temp_buff = NULL;
	}
	return (final_string);
}
/*
int	main(void)
{
	int	fd;
	int	loopcount;
	char	*returnstring;

	loopcount = 0;
	// TEST: fd is stdin.
	// fd = 0;
	// TEST: fd is the index of a text file.
	 fd = open("test_0.txt", O_RDONLY);


	while (loopcount < 5)
	{
		printf("L00P #%d\n", loopcount);
		printf("-----------------------\n");
		returnstring = get_next_line(fd);
		printf("Output = %s", returnstring);
		free(returnstring);
		loopcount ++;
	}
//	free(returnstring);
	return (0);
}
*/
