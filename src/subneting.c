/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subneting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:58:18 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/06/01 23:50:21 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../42_Libft/libft.h"

int check_digits(char *ip)
{
	int points;

	points = 0;
	while (*ip)
	{
		if (!ft_isdigit(*ip) && *ip != '.')
			return (0);
		if (*ip == '.')
			points++;
		ip++;
	}
	if (points != 3)
		return (0);
	return (1);
}

int ft_is_valid_ip(const char *ip)
{
	char	**octets;

	if (!ip)
		return (0);
	if (!check_digits((char *)ip))
		return (0);
	octets = ft_split_ae(ip, '.');
	if (ft_splitlen(octets) != 4)
		return (0);
	if(ft_atoi(octets[0]) < 0 || ft_atoi(octets[0]) > 255 ||
	   ft_atoi(octets[1]) < 0 || ft_atoi(octets[1]) > 255 ||
	   ft_atoi(octets[2]) < 0 || ft_atoi(octets[2]) > 255 ||
	   ft_atoi(octets[3]) < 0 || ft_atoi(octets[3]) > 255)
	{
		return (0);
	}
	return (1);
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		write(1, "Usage: ./subneting <IP>\n", 24);
		return (1);
	}
	if (ft_is_valid_ip(argv[1]))
		ft_printf("The IP address %s is valid.\n", argv[1]);
	else
	{
		ft_printf("The IP address %s is invalid.\n", argv[1]);
		ft_alloc_clear();
		return (1);
	}
	ft_alloc_clear();
	return (0);
}
