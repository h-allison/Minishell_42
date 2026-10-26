/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:23:49 by hallison          #+#    #+#             */
/*   Updated: 2025/06/17 18:25:39 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_exec.h"

/*
	stat() returns

           struct stat 
               dev_t     st_dev;         ID of device containing file
               ino_t     st_ino;         Inode number
               mode_t    st_mode;        File type and mode
               nlink_t   st_nlink;       Number of hard links
               uid_t     st_uid;         User ID of owner
               gid_t     st_gid;         Group ID of owner
               dev_t     st_rdev;        Device ID (if special file)
               off_t     st_size;        Total size, in bytes
               blksize_t st_blksize;     Block size for filesystem I/O
               blkcnt_t  st_blocks;      Number of 512B blocks allocated

	S_ISDIR takes a mode value and returns
	a non-zero value if the file is a directory
*/

int	is_directory(char *pathname)
{
	struct stat	path_stat;

	if (stat(pathname, &path_stat) == -1)
	{
		perror("call to stat failed\n");
		return (-1);
	}
	return (S_ISDIR(path_stat.st_mode));
}

/*
	get_var_len extracts the length of "HOME=" (5)
	from the full_string "HOME=/home/hallison"
	This is useful for other functions that find envp index by variable,
	or extract other strings from envp list.

	It is ONLY for use with variables that are assigned with a =
*/

int	get_var_len(char *full_var_string)
{
	int	var_len;
	int	i;

	i = 0;
	while (full_var_string[i] != '=' && full_var_string[i] != '\0')
		i++;
	var_len = i + 1;
	return (var_len);
}

int	find_export_i(char *var, char **list)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (list[i] != NULL)
	{
		if (list[i][j] == var[j])
		{
			while ((list[i][j] == var[j]) && (list[i][j] != '\0')
				&& (var[j] != '\0'))
				j++;
			if (list[i][j] == '\0' && (var[j] == '=' || var[j] == '\0'))
				return (i);
		}
		i++;
	}
	return (-42);
}
