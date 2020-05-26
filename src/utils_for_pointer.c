/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sad-aude <sad-aude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/20 15:56:40 by sad-aude          #+#    #+#             */
/*   Updated: 2020/05/26 19:06:47 by sad-aude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

char	*longprec_for_pointer(char *str, char *hexa, int *point, t_spec *spec)
{
	//penser à modifier comme dans utils for int
	int i;

	i = 2;
	if (point == 0)
	{
		i = 0;
		while (spec->diff++ < (spec->prec - spec->len + 2))
			hexa[i++] = '0';
		if (!(str =ft_strjoin(str, hexa, 3)))
			return (NULL);
		return (str);
	}
	while (spec->diff++ < (spec->prec - spec->len))
		hexa[i++] = '0';
	if (!(str =ft_strjoin(hexa, str, 3)))
			return (NULL);
	return (str);
}

char	*apply_prec_for_pointer(char *str, int *point, t_spec *spec)
{
	char	*hexa;

	if (point != 0)
	{
		if (!(hexa = ft_stringnew(2 + spec->prec - spec->len)))
			return (NULL);
		hexa[0] = '0';
		hexa[1] = 'x';
	}
	else
	{
		if (!(hexa = ft_stringnew(spec->prec - spec->len)))
			return (NULL);
	}
	spec->len = ft_strlen(str);
	if (spec->prec < spec->len)
	{
		if (!(str = ft_strjoin(hexa, str, 3)))
			return (NULL);
		return (str);
	}
	else
		return (longprec_for_pointer(str, hexa, point, spec));
}

void	apply_longwidth_for_pointer(t_spec *spec)
{
	int indic;

	indic = 0;
	if (spec->is_star || spec->is_minus)
	{
		while (indic++ < spec->width - spec->len)
			spec->count += write(1, " ", 1);
	}
	else
	{
		while (indic++ < spec->width - spec->len)
			spec->count += write(1, " ", 1);
	}
}

char	*apply_width_for_pointer(char *str, t_spec *spec)
{
	if (spec->is_space)
		spec->count += write(1, " ", 1);
	spec->count += write(1, "0x", 2);
	while (spec->diff++ < spec->width - spec->len - 2)
		spec->count += write(1, "0", 1);
	return (str);
}

void	check_width_for_pointer(char *str, t_spec *spec)
{
	spec->len = ft_strlen(str);
	if (spec->is_minus)
	{
		if (!spec->is_prec)
		{
			spec->width -= 2;
			spec->count += write(1, "0x", 2);
		}
		spec->count += write(1, str, ft_strlen(str));
	}
	if (spec->is_zero && !spec->is_prec && !spec->is_minus)
		str = apply_width_for_pointer(str, spec);
	else
		apply_longwidth_for_pointer(spec);
	if (!spec->is_minus)
		spec->count += write(1, str, spec->len);
}
