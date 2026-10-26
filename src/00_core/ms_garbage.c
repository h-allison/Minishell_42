/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_garbage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:51:35 by cbotel            #+#    #+#             */
/*   Updated: 2025/06/25 19:11:14 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_core.h"
#include "ms_parsing.h"
#include "ms_exec.h"

// Assumes gc_init() is always called before first gc_malloc()
// Ensures mem->tail is kept in sync with mem->next
void	*gc_malloc(t_shell *shell, size_t size, t_gc_mem *mem)
{
	void		*ptr;
	t_gc_mem	*new_node;

	ptr = malloc(size);
	new_node = malloc(sizeof(*new_node));
	if (!ptr || !new_node)
	{
		if (ptr)
			free(ptr);
		ms_error_msg(shell, 1, "gc_malloc", ERR_MALLOC_FAIL);
		ms_clean_exit(shell, 1, true);
	}
	new_node->ptr_to_mem = ptr;
	new_node->size = size;
	new_node->next = NULL;
	if (!mem->next)
		mem->next = new_node;
	else
		mem->tail->next = new_node;
	mem->tail = new_node;
	return (ptr);
}

void	gc_free(void *ptr, t_gc_mem *mem)
{
	t_gc_mem	*prev;
	t_gc_mem	*curr;

	if (!ptr || !mem || !mem->next)
		return ;
	prev = NULL;
	curr = mem->next;
	while (curr)
	{
		if (curr->ptr_to_mem == ptr)
		{
			if (prev)
				prev->next = curr->next;
			else
				mem->next = curr->next;
			if (mem->tail == curr)
				mem->tail = prev;
			free(curr->ptr_to_mem);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	gc_cleanup(t_gc_mem *mem)
{
	t_gc_mem	*curr;
	t_gc_mem	*next;

	if (!mem)
		return ;
	curr = mem->next;
	while (curr)
	{
		next = curr->next;
		free(curr->ptr_to_mem);
		free(curr);
		curr = next;
	}
	mem->next = NULL;
	mem->tail = NULL;
}

void	gc_cleanup_shell(t_shell *shell)
{
	if (!shell)
		return ;
	gc_cleanup(&shell->input_mem);
	gc_cleanup(&shell->parser_mem);
	heredoc_unlink_all(shell->ast);
	gc_cleanup(&shell->exec_mem);
	free_envp(shell->envp);
	free_envp(shell->export_list);
	return ;
}

void	gc_init(t_gc_mem *arena)
{
	if (!arena)
		return ;
	arena->next = NULL;
	arena->tail = NULL;
}
