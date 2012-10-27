#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>

#include "gpio.h"

#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

volatile unsigned* __gpio_ptr;

void gpio_setup(void)
{
	int	mem_fd;
	char*	gpio_mem;
	char*	gpio_map;
	char*	spi0_mem;
	char*	spi0_map;

	if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0)
	{
		perror("open");
		exit(-1);
	}

	if ((gpio_mem = malloc(BLOCK_SIZE + (PAGE_SIZE-1))) == NULL)
	{
		perror("malloc");
		exit(-1);
	}

	if ((unsigned long)gpio_mem % PAGE_SIZE)
	{
		gpio_mem += PAGE_SIZE - ((unsigned long)gpio_mem % PAGE_SIZE);
	}

	gpio_map = (unsigned char *)mmap(	(caddr_t)gpio_mem,
						BLOCK_SIZE,
						PROT_READ|PROT_WRITE,
						MAP_SHARED|MAP_FIXED,
						mem_fd,
						GPIO_BASE);

	if ((long)gpio_map < 0)
	{
		perror("mmap");
		exit (-1);
	}

	__gpio_ptr = (volatile unsigned *)gpio_map;
}

