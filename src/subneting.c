/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subneting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:58:18 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/06/15 10:29:43 by ide-dieg         ###   ########.fr       */
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

unsigned int ft_change_binary_digit(unsigned int num, int pos , int value)
{
	if (value == 1)
		return (num | (1 << (32 - pos - 1)));
	else if (value == 0)
		return (num & ~(1 << (32 - pos - 1)));
	return (num);
}

unsigned int ft_net_ip_calculate(unsigned int ip_value, int mask)
{
	int	i = 0;

	while (i < 32)
	{
		if (i >= mask)
			ip_value = ft_change_binary_digit(ip_value, i, 0);
		i++;
	}
	return (ip_value);
}

unsigned int ft_broadcast_ip_calculate(unsigned int ip_value, int mask)
{
	int	i = 0;

	while (i < 32)
	{
		if (i >= mask)
			ip_value = ft_change_binary_digit(ip_value, i, 1);
		i++;
	}
	return (ip_value);
}

void ft_print_ip_data(const char *ip, int mask)
{
	char			mask_str[17];
	unsigned int	ip_value;
	char			**ip_split;
	int				octets[4];
	unsigned int	net_value;
	unsigned int	broadcast_value;
	unsigned int	range;

	ft_mask_to_octets(mask, mask_str);
	ft_printf(CYAN "IP Address: %s%s%s   Mask: %s%s%s --> %s/%d\n" RESET, 
		RESET, ip, CYAN, RESET, mask_str, CYAN, RESET, mask);
	ip_split = ft_split_ae(ip, '.');
	octets[0] = ft_atoi(ip_split[0]);
	octets[1] = ft_atoi(ip_split[1]);
	octets[2] = ft_atoi(ip_split[2]);
	octets[3] = ft_atoi(ip_split[3]);
	ip_value = octets[3] + (octets[2] * 256) + (octets[1] * 256 * 256) + (octets[0] * 256 * 256 * 256);
	net_value = ft_net_ip_calculate(ip_value, mask);
	ft_printf(GREEN "Network Address: %s%d.%d.%d.%d\n" RESET, RESET,
		(net_value >> 24) & 0xFF, (net_value >> 16) & 0xFF,
		(net_value >> 8) & 0xFF, net_value & 0xFF);
	broadcast_value = ft_broadcast_ip_calculate(ip_value, mask);
	range = 0;
	if (broadcast_value > net_value)
		range = (broadcast_value - net_value) - 1;
	if (range > 0)
		ft_printf(GREEN "Usable IP Range: (%s%d.%d.%d.%d%s - %s%d.%d.%d.%d%s) " RESET,
			RESET, ((net_value >> 24) & 0xFF), ((net_value >> 16) & 0xFF),
			((net_value >> 8) & 0xFF), (net_value & 0xFF) + 1, GREEN, RESET,
			((broadcast_value >> 24) & 0xFF), ((broadcast_value >> 16) & 0xFF),
			((broadcast_value >> 8) & 0xFF), (broadcast_value & 0xFF) - 1, GREEN);
	ft_dprintf(1, GREEN "Total Usable IPs: %ld\n" RESET, range);
	ft_printf(GREEN "Broadcast Address: %s%d.%d.%d.%d\n" RESET, RESET,
		(broadcast_value >> 24) & 0xFF, (broadcast_value >> 16) & 0xFF,
		(broadcast_value >> 8) & 0xFF, broadcast_value & 0xFF);
	
}

int ft_check_subnets(char *subnets, int mask)
{
	char	*tmp = subnets;
	int		num_subnets;
	int		i = 1;

	while (*tmp)
	{
		if (!ft_isdigit(*tmp))
		{
			ft_dprintf(2, RED "%s is not a valid number of subnets.\n" RESET, subnets);
			return (0);
		}
		tmp++;
	}
	num_subnets = ft_atoi(subnets);
	while (mask < 32)
	{
		i *= 2;
		if (i >= num_subnets)
			return (1);
		mask++;
	}
	ft_dprintf(2, RED "The number of subnets %d is too high for the given mask /%d.\n" RESET, num_subnets, mask);
	return (0);
}

void ft_print_subnets(const char *ip, int mask, int num_subnets)
{
	char			mask_str[17];
	unsigned int	ip_value;
	char			**ip_split;
	int				octets[4];
	unsigned int	subnet_value;
	int				i;
	unsigned int 	jump;
	unsigned int	broadcast_value;
	unsigned int	range;
	char 			header[77];

	ip_split = ft_split_ae(ip, '.');
	octets[0] = ft_atoi(ip_split[0]);
	octets[1] = ft_atoi(ip_split[1]);
	octets[2] = ft_atoi(ip_split[2]);
	octets[3] = ft_atoi(ip_split[3]);
	ip_value = octets[3] + (octets[2] * 256) + (octets[1] * 256 * 256) + (octets[0] * 256 * 256 * 256);
	subnet_value = ft_net_ip_calculate(ip_value, mask);
	i = 1;
	while (i < num_subnets)
	{
		mask++;
		i *= 2;
	}
	ft_mask_to_octets(mask, mask_str);
	jump = ft_change_binary_digit(0, mask - 1, 1);
	i = 0;
	while (i < num_subnets)
	{
		ft_snprintf(header, 77, "----------------------------------SUBNET-%d---------------------------------------------------", i + 1);
		ft_printf(MAGENTA "%s\n" RESET, header);
		ft_printf(GREEN "Subnet Address: %s%d.%d.%d.%d%s   Mask: %s%s%s --> %s/%d\n" RESET,
			RESET, (subnet_value >> 24) & 0xFF, (subnet_value >> 16) & 0xFF,
			(subnet_value >> 8) & 0xFF, subnet_value & 0xFF, GREEN, RESET, mask_str, GREEN, RESET, mask);
		broadcast_value = ft_broadcast_ip_calculate(subnet_value, mask);
		range = 0;
		if (broadcast_value > subnet_value)
			range = (broadcast_value - subnet_value) - 1;
		if (range > 0)
			ft_printf(GREEN "Usable IP Range: (%s%d.%d.%d.%d%s - %s%d.%d.%d.%d%s) " RESET,
				RESET, ((subnet_value >> 24) & 0xFF), ((subnet_value >> 16) & 0xFF),
				((subnet_value >> 8) & 0xFF), (subnet_value & 0xFF) + 1,
				GREEN, RESET, ((broadcast_value >> 24) & 0xFF), ((broadcast_value >> 16) & 0xFF),
				((broadcast_value >> 8) & 0xFF), (broadcast_value & 0xFF) - 1, GREEN);
		ft_dprintf(1, GREEN "Total Usable IPs: %s%ld\n" RESET, RESET, range);
		ft_printf(GREEN "Broadcast Address: %s%d.%d.%d.%d\n" RESET, RESET,
			(broadcast_value >> 24) & 0xFF, (broadcast_value >> 16) & 0xFF,
			(broadcast_value >> 8) & 0xFF, broadcast_value & 0xFF);
		ft_printf(MAGENTA "----------------------------------------------------------------------------\n\n" RESET);
		subnet_value += jump;
		i++;
	}
}

int main(int argc, char **argv)
{
	int	Mask;

	if (argc < 3 || argc > 4)
	{
		ft_dprintf(2, YELLOW "Usage: %s <IP address> <Mask> [Number of subnets]\n" RESET, argv[0]);
		return (1);
	}
	if (!ft_is_valid_ip(argv[1]))
	{
		ft_dprintf(2, RED "The IP address %s is invalid.\n" RESET, argv[1]);
		ft_alloc_clear();
		return (1);
	}
	if (!ft_is_valid_mask(argv[2]))
	{
		ft_dprintf(2, RED "The mask %s is invalid.\n" RESET, argv[2]);
		ft_alloc_clear();
		return (1);
	}
	Mask = ft_get_mask_num(argv[2]);
	if (argc == 4 && !ft_check_subnets(argv[3], Mask))
	{
		ft_alloc_clear();
		return (1);
	}
	ft_printf(YELLOW "----------------------------------NET-INFO----------------------------------\n" RESET);
	ft_print_ip_data(argv[1], Mask);
	ft_printf(YELLOW "----------------------------------------------------------------------------\n\n" RESET);
	ft_alloc_clear();
	if (argc == 4)
	{
		ft_print_subnets(argv[1], Mask, ft_atoi(argv[3]));
	}
	return (0);
}
