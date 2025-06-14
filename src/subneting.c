/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subneting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:58:18 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/06/13 21:20:05 by ide-dieg         ###   ########.fr       */
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
	char			**octets;
	int				octet[4];
	unsigned int	mask_value;
	int				i;
	int				binary;

	if (!mask)
		return (0);
	if(mask[0] == '/')
	{
		if (ft_strlen(mask) > 3 || ft_strlen(mask) < 2
			|| (mask[1] && ft_isdigit(mask[1]) == 0)
			|| (mask[2] && ft_isdigit(mask[2]) == 0))
			return (0);
		if (ft_atoi(mask + 1) < 0 || ft_atoi(mask + 1) > 32)
			return (0);
	}
	else
	{
		if (!check_digits((char *)mask))
		return (0);
		octets = ft_split_ae(mask, '.');
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
		mask_value = octet[3] + (octet[2] * 256) + (octet[1] * 256 * 256) + (octet[0] * 256 * 256 * 256);
		binary = 1;
		i = 0;
		while (i < 32)
		{
			if (mask_value & (1 << (31 - i)))
			{
				if (binary == 0)
					return (0);
			}	
			else
				binary = 0;
			i++;
		}
	}
	return (1);
}

int ft_get_mask_num(const char *mask)
{
	unsigned int mask_value;
	int i;

	if (mask[0] == '/')
		return (ft_atoi(mask + 1));
	char **octets = ft_split_ae(mask, '.');
	int octet[4];
	octet[0] = ft_atoi(octets[0]);
	octet[1] = ft_atoi(octets[1]);
	octet[2] = ft_atoi(octets[2]);
	octet[3] = ft_atoi(octets[3]);
	mask_value = octet[3] + (octet[2] * 256) + (octet[1] * 256 * 256) + (octet[0] * 256 * 256 * 256);
	i = 0;
	while (i < 32 && mask_value > 0)
	{
		if (mask_value & 1)
			i++;
		mask_value >>= 1;
	}
	return (i);
}

void ft_mask_to_octets(int mask, char *mask_str)
{
	unsigned int	mask_value;
	int 			octet[4];

	mask_value = 0xFFFFFFFF << (32 - mask);
	if (mask == 0)
		mask_value = 0x00000000;
	else if (mask < 0 || mask > 32)
	{
		ft_printf(CYAN "Invalid mask value: %d\n" RESET, mask);
		ft_alloc_clear();
		return;
	}
	octet[0] = (mask_value >> 24) & 0xFF;
	octet[1] = (mask_value >> 16) & 0xFF;
	octet[2] = (mask_value >> 8) & 0xFF;
	octet[3] = mask_value & 0xFF;
	ft_sprintf(mask_str, "%d.%d.%d.%d", octet[0], octet[1], octet[2], octet[3]);
}

void ft_print_ip_data(const char *ip, int mask)
{
	char mask_str[17]; 

	ft_mask_to_octets(mask, mask_str);
	ft_printf(GREEN "IP Address: %s   Mask: %s\n" RESET, ip, mask_str);
}

int main(int argc, char **argv)
{
	int	Mask;

	if (argc != 3)
	{
		ft_printf(YELLOW "Usage: %s <IP address> <Mask>\n" RESET, argv[0]);
		return (1);
	}
	if (!ft_is_valid_ip(argv[1]))
	{
		ft_printf(RED "The IP address %s is invalid.\n" RESET, argv[1]);
		ft_alloc_clear();
		return (1);
	}
	if (!ft_is_valid_mask(argv[2]))
	{
		ft_printf(RED "The mask %s is invalid.\n" RESET, argv[2]);
		ft_alloc_clear();
		return (1);
	}
	Mask = ft_get_mask_num(argv[2]);
	ft_print_ip_data(argv[1], Mask);
	ft_alloc_clear();
	return (0);
}
