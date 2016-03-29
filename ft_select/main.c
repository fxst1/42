#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
int	main(int argc, char **argv)
{
	struct termios	term;

	if (argc == 1)
		return (0);
	int fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (0);
	tcgetattr(fd, &term);
	close(fd);
	printf("%x\n%x\n%x\n%x\n\n", term.c_iflag, term.c_oflag, term.c_cflag, term.c_lflag);
	printf("Input\n");
	if (term.c_iflag & IGNBRK)
		printf("Ignore brk\n");
	if (term.c_iflag & BRKINT)
		printf("brk\n");
	if (term.c_iflag & PARMRK)
		printf("Ignore framing error\n");
	if (term.c_iflag & INPCK)
		printf("Inpck\n");
	if (term.c_iflag & ISTRIP)
		printf("Istrip\n");
	if (term.c_iflag & INLCR)
		printf("Inlcr\n");
	if (term.c_iflag & IGNCR)
		printf("Igncr\n");
	if (term.c_iflag & ICRNL)
		printf("Icrnl\n");
	if (term.c_iflag & IUCLC)
		printf("Iuclc\n");
	if (term.c_iflag & IXON)
		printf("Ixon\n");
	if (term.c_iflag & IXANY)
		printf("Ixany\n");
	if (term.c_iflag & IXOFF)
		printf("Ixoff\n");
	if (term.c_iflag & IMAXBEL)
		printf("Imaxbel\n");
	if (term.c_iflag & IUTF8)
		printf("Iutf8\n");
	printf("\nOutput\n");
	if (term.c_oflag & OPOST)
		printf("opost\n");
	if (term.c_oflag & OLCUC)
		printf("olcuc\n");
	if (term.c_oflag & ONLCR)
		printf("onlcr\n");
	if (term.c_oflag & ONOCR)
		printf("onocr\n");
	if (term.c_oflag & ONLRET)
		printf("onlret\n");
	if (term.c_oflag & OFILL)
		printf("ofill\n");
	if (term.c_oflag & OFDEL)
		printf("ofdel\n");
	if (term.c_oflag & NLDLY)
		printf("nldly\n");
	if (term.c_oflag & CRDLY)
		printf("crdly\n");
	if (term.c_oflag & TABDLY)
		printf("tabdly\n");
	if (term.c_oflag & BSDLY)
		printf("bsdly\n");
	if (term.c_oflag & VTDLY)
		printf("vtdly\n");
	if (term.c_oflag & FFDLY)
		printf("ffdly\n");
	printf("\nConstants\n");
	if (term.c_cflag & CBAUD)
		printf("cbaud\n");
	if (term.c_cflag & CBAUDEX)
		printf("cbaudex\n");
	if (term.c_cflag & CSIZE)
		printf("csize\n");
	if (term.c_cflag & CSTOPB)
		printf("cstopb\n");
	if (term.c_cflag & CREAD)
		printf("cread\n");
	if (term.c_cflag & PARENB)
		printf("parenb\n");
	if (term.c_cflag & PARODD)
		printf("parodd\n");
	if (term.c_cflag & HUPCL)
		printf("hupcl\n");
	if (term.c_cflag & CLOCAL)
		printf("clocal\n");
//	if (term.c_cflag & LOBLK)
//		printf("tabdly\n");
	if (term.c_cflag & CIBAUD)
		printf("cibaud\n");
	if (term.c_cflag & CMSPAR)
		printf("cmspar\n");
	if (term.c_cflag & CRTSCTS)
		printf("crtscts\n");
	printf("\nOther constants\n");
	if (term.c_lflag & ISIG)
		printf("isig\n");
	if (term.c_lflag & ICANON)
		printf("icanon\n");
	if (term.c_lflag & XCASE)
		printf("xcase\n");
	if (term.c_lflag & ECHO)
		printf("echo\n");
	if (term.c_lflag & ECHOE)
		printf("echo e\n");
	if (term.c_lflag & ECHOK)
		printf("echo k\n");
	if (term.c_lflag & ECHONL)
		printf("echo nl\n");
	if (term.c_lflag & ECHOCTL)
		printf("echo ctl\n");
	if (term.c_lflag & ECHOPRT)
		printf("echo prt\n");
	if (term.c_lflag & ECHOKE)
		printf("echo ke\n");
//	if (term.c_lflag & DEFECHO)
//		printf("defecho\n");
	if (term.c_lflag & FLUSHO)
		printf("flusho\n");
	if (term.c_lflag & NOFLSH)
		printf("no flush\n");
	if (term.c_lflag & TOSTOP)
		printf("tostop\n");
	if (term.c_lflag & PENDIN)
		printf("pendin\n");
	if (term.c_lflag & IEXTEN)
		printf("iexten\n");
	printf("\nSpec characters\n");
	if (term.c_lflag & VDISCARD)
		printf("vdiscard\n");
//	if (term.c_lflag & VDSUSP)
//		printf("vdsusp\n");
	if (term.c_lflag & VEOF)
		printf("veof\n");
	if (term.c_lflag & VEOL)
		printf("veol\n");
	if (term.c_lflag & VEOL2)
		printf("veol2\n");
	if (term.c_lflag & VERASE)
		printf("verase\n");
	if (term.c_lflag & VINTR)
		printf("vintr\n");
	if (term.c_lflag & VKILL)
		printf("vkill\n");
	if (term.c_lflag & VLNEXT)
		printf("vlnext\n");
	if (term.c_lflag & VMIN)
		printf("vmin\n");
	if (term.c_lflag & VQUIT)
		printf("vquit\n");
	if (term.c_lflag & VREPRINT)
		printf("vreprint\n");
	if (term.c_lflag & VSTART)
		printf("vstart\n");
//	if (term.c_lflag & VSTATUS)
//		printf("vstatus\n");
	if (term.c_lflag & VSTOP)
		printf("vstop\n");
	if (term.c_lflag & VSUSP)
		printf("vsusp\n");
//	if (term.c_lflag & VSWTCH)
//		printf("vswtch\n");
	if (term.c_lflag & VTIME)
		printf("vtime\n");
	if (term.c_lflag & VWERASE)
		printf("vwerase\n");
}