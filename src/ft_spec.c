/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sad-aude <sad-aude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 19:50:00 by sad-aude          #+#    #+#             */
/*   Updated: 2020/05/23 02:44:21 by sad-aude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static	void	flags_parser(t_spec *spec)
{
	if (ft_strchr(spec->conv, '.'))
		spec->is_prec = 1;
	if (ft_strchr(spec->conv, '*'))
		spec->is_star = 1;
	if (ft_strchr(spec->conv, '-'))
		spec->is_minus = 1;
	if (ft_strchr(spec->conv, '+'))
		spec->is_plus = 1;
	if (ft_strchr(spec->conv, ' '))
		spec->is_space = 1;
	if (ft_strchr(spec->conv, '#'))
		spec->is_sharp = 1;
	while (spec->conv[spec->parser] && !ft_isdigit(spec->conv[spec->parser]))
		spec->parser++;
	if (spec->conv[spec->parser] && spec->conv[spec->parser] == '0'
		&& spec->conv[spec->parser - 1] != '.'
		&& spec->conv[spec->parser + 1] != '#')
	{
		spec->is_zero = 1;
		spec->parser++;
	}
	if (spec->conv[spec->parser] && ft_isdigit(spec->conv[spec->parser])
		&& spec->conv[spec->parser] != '0' && spec->conv[spec->parser - 1]
		!= '.' && spec->conv[spec->parser + 1] != '#')
		spec->is_width = 1;
}

static	int		convert_spec(va_list elem, t_spec *spec)
{
	spec->type = spec->conv[ft_strlen(spec->conv) - 1];
	flags_parser(spec);
	spec->width = get_width(elem, spec);
	spec->prec = get_prec(elem, spec);
	return (1);
}

static	void	types_parser(va_list elem, const char *format, int *i,
t_spec *spec)
{
	if (ft_strchr(TYPES, format[*i]))
	{
		if (format[*i] == 'c')
			ft_convert_char(elem, spec);
		if (format[*i] == 's')
			ft_convert_str(elem, spec);
		if (format[*i] == 'i' || format[*i] == 'd')
			ft_convert_dec(elem, spec);
		if (format[*i] == 'u')
			ft_convert_unsigned(elem, spec);
		if (format[*i] == '%')
			ft_convert_percent(spec);
		if (format[*i] == 'x')
			ft_convert_hexa(elem, spec);
		if (format[*i] == 'X')
		{
			spec->is_majhexa = 1;
			ft_convert_hexa(elem, spec);
		}
		if (format[*i] == 'p')
			ft_convert_pointer(elem, spec);
	}
}

int				read_spec(va_list elem, const char *format, int *i)
{
	t_spec	spec;
	int		start;

	ft_bzero(&spec, sizeof(spec));
	start = ++(*i);
	while (!ft_strchr(TYPES, format[*i]))
		(*i)++;
	if (!(spec.conv = ft_substr(format, start, *i - start)) ||
			!convert_spec(elem, &spec))
		return (0);
	types_parser(elem, format, i, &spec);
	free(spec.conv);
	return (spec.count);
}
