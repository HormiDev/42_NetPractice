/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subneting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:58:18 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/06/12 13:53:20 by ide-dieg         ###   ########.fr       */
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
	int		octet[4];

	if (!ip)
		return (0);
	if (!check_digits((char *)ip))
		return (0);
	octets = ft_split_ae(ip, '.');
	if (ft_splitlen(octets) != 4)
		return (0);
	octet[0] = ft_atoi(octets[0]);
	octet[1] = ft_atoi(octets[1]);
	octet[2] = ft_atoi(octets[2]);
	octet[3] = ft_atoi(octets[3]);
	if(octet[0] < 0 || octet[0] > 255
		|| octet[1] < 0 || octet[1] > 255
		|| octet[2] < 0 || octet[2] > 255
		|| octet[3] < 0 || octet[3] > 255)
		return (0);
	return (1);
}

int ft_is_valid_mask(const char *mask)
{
	if(mask[0] == '/')
	{
		if (ft_strlen(mask) > 3 || ft_strlen(mask) < 2
			|| (mask[1] && ft_isdigit(mask[1]) == 0) || (mask[2] && ft_isdigit(mask[2]) == 0))
			return (0);
		if (ft_atoi(mask + 1) < 0 || ft_atoi(mask + 1) > 32)
			return (0);
	}
	return (1);
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_printf("Usage: %s <IP address> <Mask>\n", argv[0]);
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
	if (ft_is_valid_mask(argv[2]))
		ft_printf("The mask %s is valid.\n", argv[2]);
	else
	{
		ft_printf("The mask %s is invalid.\n", argv[2]);
		ft_alloc_clear();
		return (1);
	}
	ft_alloc_clear();
	return (0);
}
