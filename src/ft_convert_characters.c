/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_characters.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sad-aude <sad-aude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 19:36:09 by sad-aude          #+#    #+#             */
/*   Updated: 2020/04/17 19:36:17 by sad-aude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

char   *apply_prec_for_str(char *str, t_spec *spec)
{
    return (ft_substr(str, 0, spec->prec));
}

void    apply_width_for_str(char *str, t_spec *spec)
{
    if (spec->width < 0)
        {
             spec->is_minus = 1;
             spec->width *= -1;
        }
        spec->len = ft_strlen(str);
        if (spec->width > spec->len)
        {
            if (spec->is_minus)
                ft_putstr_fd(str, 1);
            if (spec->is_zero && !spec->is_minus)
                 while (spec->diff++ < spec->width - spec->len)
                    write(1, "0", 1);
            // if (!spec->is_zero || (spec->is_minus && spec->is_zero))
            else
                while (spec->diff++ < spec->width - spec->len)
                    write(1, " ", 1);
            if (!spec->is_minus)
                ft_putstr_fd(str, 1);
        }
        else
            ft_putstr_fd(str, 1);
}

void            ft_convert_str(va_list elem, t_spec *spec)
{
    char *str;

    if (!(str = va_arg(elem, char*)))
        str = "(null)";
    if (spec->is_prec)
        str = apply_prec_for_str(str, spec);
    if (spec->width)
        apply_width_for_str(str, spec);
    else
        ft_putstr_fd(str, 1);
}

void            ft_convert_char(va_list elem, t_spec *spec)
{
    char c;

    c = va_arg(elem, int);
    if (spec->width)
    {
         if (spec->width < 0)
        {
             spec->is_minus = 1;
             spec->width *= -1;
        }
        if (spec->is_minus)
        {
            //dprintf(1, "hello\n");
            ft_putchar_fd(c, 1);
            while (++spec->len < spec->width)
                write(1, " ", 1);
        }
        if (!spec->is_minus)
        {
            while (++spec->len < spec->width)
                write(1, " ", 1);
            ft_putchar_fd(c, 1);
        }
    }
    else
        ft_putchar_fd(c, 1);
}