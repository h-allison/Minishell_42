/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:29:04 by hallison          #+#    #+#             */
/*   Updated: 2024/06/17 14:31:14 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stddef.h>
# include <unistd.h>

int		ft_printf(const char *format, ...);
int		ft_print_c(char arg);
int		ft_print_s(char *arg);
int		ft_print_p(void	*arg);
int		ft_print_d(int arg);
int		ft_flexitoa(size_t nbr, int base, const char *radix);
int		ft_print_b(size_t nbr, int base, const char *radix);
size_t	ft_strlen(const char *s);

#endif
