/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 16:15:33 by marvin            #+#    #+#             */
/*   Updated: 2019/02/07 16:17:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex *create_complex(double real, double i)
{
    t_complex *complex;

    complex = (t_complex*)ft_memalloc(sizeof(complex));
    complex->real = real;
    complex->i = i;
    return (complex);
}