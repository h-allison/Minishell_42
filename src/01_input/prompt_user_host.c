/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_user_host.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:11:26 by cbotel            #+#    #+#             */
/*   Updated: 2025/06/25 20:38:28 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"
#include <fcntl.h>

char	*prompt_user(t_shell *shell)
{
	char	*user;
	char	*str;
	size_t	len;

	user = getenv("USER");
	if (!user)
		user = "unknown";
	len = ft_strlen(user);
	str = gc_malloc(shell, len + 2, &shell->input_mem);
	ft_strcpy(str, user);
	str[len] = '@';
	str[len + 1] = '\0';
	return (str);
}

char	*prompt_host(t_shell *shell)
{
	char	*host;
	char	*dot;
	char	*str;
	size_t	len;

	host = getenv("HOSTNAME");
	if (!host || !*host)
		host = prompt_read_hostname_file(shell, "/etc/hostname");
	if (!host || !*host)
		host = "host";
	dot = ft_strchr(host, '.');
	if (dot)
		len = dot - host;
	else
		len = ft_strlen(host);
	str = gc_malloc(shell, len + 2, &shell->input_mem);
	ft_strlcpy(str, host, len + 1);
	str[len] = ' ';
	str[len + 1] = '\0';
	return (str);
}

char	*prompt_read_hostname_file(t_shell *shell, const char *path)
{
	int		fd;
	char	buf[256];
	size_t	n;
	char	*newline;
	char	*host;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	n = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	if (n <= 0)
		return (NULL);
	buf[n] = '\0';
	newline = ft_strchr(buf, '\n');
	if (newline)
		*newline = '\0';
	host = gc_malloc(shell, ft_strlen(buf) + 1, &shell->input_mem);
	ft_strlcpy(host, buf, ft_strlen(buf) + 1);
	return (host);
}

char	*prompt_append(t_shell *shell, char *buffer, \
							char *module, t_gc_mem *mem)
{
	int		len_buf;
	char	*new;

	len_buf = ft_strlen(buffer);
	new = gc_malloc(shell, len_buf + ft_strlen(module) + 1, mem);
	ft_strcpy(new, buffer);
	ft_strcpy(new + len_buf, module);
	gc_free(buffer, mem);
	gc_free(module, mem);
	return (new);
}

void	prompt_update(t_shell *shell)
{
	char	*buffer;
	char	*module;

	buffer = gc_malloc(shell, 1, &shell->input_mem);
	buffer[0] = '\0';
	module = prompt_user(shell);
	module = prompt_colorize(shell, GREEN, module);
	buffer = prompt_append(shell, buffer, module, &shell->input_mem);
	module = prompt_host(shell);
	buffer = prompt_append(shell, buffer, module, &shell->input_mem);
	module = prompt_cwd(shell);
	module = prompt_colorize(shell, BLUE, module);
	buffer = prompt_append(shell, buffer, module, &shell->input_mem);
	module = prompt_name(shell);
	module = prompt_colorize(shell, MAGENTA, module);
	buffer = prompt_append(shell, buffer, module, &shell->input_mem);
	shell->prompt = buffer;
}
