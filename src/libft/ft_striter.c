/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 18:14:24 by tkuhar            #+#    #+#             */
/*   Updated: 2018/03/24 18:14:26 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striter(char *s, void (*f)(char *))
{
	int i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		f(&s[i]);
		i++;
	}
}
