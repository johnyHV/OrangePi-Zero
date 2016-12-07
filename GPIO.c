#include <sys/stat.h>
#include <sys/types.h>
//#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
//#include <fcntl.h>

/*  gcc GPIO.c -o GPIO */

int fd;
char buf[255];


/* create GPIO */
void gpioExport(int gpio)
{
//	int fd;
//	char buf[255];
	fd = open("/sys/class/gpio/export", O_WRONLY);
	sprintf(buf, "%d", gpio);
	write(fd, buf, strlen(buf));
	close(fd);
}

/*IN/OUT GPIO*/
void gpioDirection(int gpio, int direction) // 1 for output, 0 for input
{
	sprintf(buf, "/sys/class/gpio/gpio%d/direction", gpio);
	fd = open(buf, O_WRONLY);

	if (direction)
	{
		write(fd, "out", 3);
	}
	else
	{
		write(fd, "in", 2);
	}
	close(fd);
}

/*SET GPIO */
void gpioSet(int gpio, int value)
{
	sprintf(buf, "/sys/class/gpio/gpio%d/value", gpio);
	fd = open(buf, O_WRONLY);
	sprintf(buf, "%d", value);
	write(fd, buf, 1);
	close(fd);
}

/* GET GPIO*/
int gpioRead(int gpio)
{
	char value;
	int retn = 0;
	sprintf(buf, "/sys/class/gpio/gpio%d/value", gpio);
	fd = open(buf, O_RDONLY);
	read(fd, &value, 1);

	if(value == '0')
	{
		retn = 0;
	}
	else
	{
		retn = 1;
	}
	close(fd);

	return retn;
}

/* MAIN */
void main()
{
	gpioExport(3);
	gpioDirection(3,1);
	gpioSet(3,1);
}

/*EOF*/