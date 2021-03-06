#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include "serial.h"

int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
{
       	struct termios  newtio,oldtio;
		if(tcgetattr(fd,&oldtio) !=0)
   		{
   		perror("Serial set error!\n");
		return -1;
   		}
		bzero(&newtio,sizeof(newtio));
	/*设置字符大小*/
	newtio.c_cflag |= CLOCAL | CREAD;
	newtio.c_cflag &= ~CSIZE;
	/*设置停止位*/
	switch(nBits)
		{
		case 7:
			newtio.c_cflag |= CS7;
			break;
		case 8:
			newtio.c_cflag |= CS8;
			break;
		}
	/*设置基偶校验位*/
	switch(nEvent)
		{
	case 'O'://奇数
            newtio.c_cflag |= PARENB;
	    newtio.c_cflag |= PARODD;
            newtio.c_iflag |= (INPCK | ISTRIP);
		break;
	case 'E': //偶数
	    newtio.c_iflag |= (INPCK | ISTRIP);
            newtio.c_cflag |= PARENB;
	    newtio.c_cflag &= ~PARODD;
		break;
	case 'N':  //无校验位
            newtio.c_cflag &= ~PARENB;
		break;
		}

	/* 设置波特率*/
	switch(nSpeed)
		{
	case 2400:
			cfsetispeed(&newtio,B2400);
			cfsetospeed(&newtio,B2400);
		break;
	case 4800:
			cfsetispeed(&newtio,B4800);
			cfsetospeed(&newtio,B4800);			
		break;
	case 9600:
			cfsetispeed(&newtio,B9600);
			cfsetospeed(&newtio,B9600);			
		break;
	case 38400:
			cfsetispeed(&newtio,B38400);
			cfsetospeed(&newtio,B38400);			
		break;
	case 57600:
			cfsetispeed(&newtio,B57600);
			cfsetospeed(&newtio,B57600);			
		break;
	case 115200:
			cfsetispeed(&newtio,B115200);
			cfsetospeed(&newtio,B115200);			
		break;
	default:
			cfsetispeed(&newtio,B9600);
			cfsetospeed(&newtio,B9600);			
		}
	
     /* 设置停止位*/
	if( nStop == 1)
		newtio.c_cflag &= ~CSTOPB;
	else if(nStop == 2)
		newtio.c_cflag |= CSTOPB;
	/* 设置等待时间和最小接收字符*/
	newtio.c_cc[VTIME] = 0;
	newtio.c_cc[VMIN] = 0;
	/* 处理未接收字符*/
	tcflush(fd,TCIFLUSH);
	/*激活新配置 */
	if((tcsetattr(fd,TCSANOW,&newtio))!=0)
		{
		perror("com set error");
		return -1;
		}
	printf("set serial done! \n");
	return 0;
}

/*
int open_port(int fd,int comport)
{
	char *dev[]={"/dev/ttyS0","/dev/ttyS1","/dev/ttyS2"};
	long  vdisable;
	if (comport==1)
	{	fd = open( "/dev/ttyS0", O_RDWR|O_NOCTTY|O_NDELAY);
		if (-1 == fd){
			perror("Can't Open Serial Port");
			return(-1);
		}
	}
	else if(comport==2)
	{	fd = open( "/dev/ttyS1", O_RDWR|O_NOCTTY|O_NDELAY);
		if (-1 == fd){
			perror("Can't Open Serial Port");
			return(-1);
		}
	}
	else if (comport==3)
	{
		fd = open( "/dev/ttyS2", O_RDWR|O_NOCTTY|O_NDELAY);
		if (-1 == fd){
			perror("Can't Open Serial Port");
			return(-1);
		}
	}
	if(fcntl(fd, F_SETFL, 0)<0)
		printf("fcntl failed!\n");
	else
		printf("fcntl=%d\n",fcntl(fd, F_SETFL,0));
	if(isatty(STDIN_FILENO)==0)
		printf("standard input is not a terminal device\n");
	else
		printf("isatty success!\n");
	printf("fd-open=%d\n",fd);
	return fd;
}
*/

int open_port(int fd,int comport)
{
	char *dev[]={"/dev/ttyUSB0","/dev/ttyUSB1","/dev/ttyUSB2","/dev/ttyUSB3","/dev/ttyUSB4"};
	long  vdisable;
	if (comport==0)
	{	fd = open( "/dev/ttyUSB0", O_RDWR|O_NOCTTY|O_NDELAY);
		if (-1 == fd){
			perror("Can't Open Serial Port\n");
			return(-1);
		}
	}
	else if(comport==1)
	{	fd = open( "/dev/ttyUSB1", O_RDWR|O_NOCTTY|O_NDELAY);
		if (-1 == fd){
			perror("Can't Open Serial Port\n");
			return(-1);
		}
	}
	else if (comport==2)
	{
		fd = open( "/dev/ttyUSB2", O_RDWR|O_NOCTTY|O_NDELAY);
		if (-1 == fd){
			perror("Can't Open Serial Port\n");
			return(-1);
		}
	}
	else if (comport==3)
	{
		fd = open( "/dev/ttyUSB3", O_RDWR|O_NOCTTY|O_NDELAY);
		if (-1 == fd){
			perror("Can't Open Serial Port\n");
			return(-1);
		}
	}
	else if (comport==4)
	{
		fd = open( "/dev/ttyUSB4", O_RDWR|O_NOCTTY|O_NDELAY);
		if (-1 == fd){
			perror("Can't Open Serial Port\n");
			return(-1);
		}
	}
	if(fcntl(fd,F_SETFL,0)<0)
		printf("fcntl failed!\n");
	else
		printf("fcntl+%d\n",fcntl(fd,F_SETFL,0));
		
	/*测试是否为终端设备 */
	if(isatty(STDIN_FILENO)==0)
		printf("standard input is not a termial device\n");
	else
		printf("isatty success!\n");
	printf("fd-open=%d\n",fd);
	return fd;
}
