/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:12:52 by mzelouan          #+#    #+#             */
/*   Updated: 2024/04/25 09:59:48 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

char	*ft_strdup(char *s)
{
	size_t	slen;
	size_t	i;
	char	*p;

	i = 0;
	slen = ft_strlen(s);
	p = (char *)malloc((slen + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	while (i < slen)
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}