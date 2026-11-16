extern "C"
{
#define new tripouille
#include "libft.h"
#undef new
}

#include "sigsegv.hpp"
#include "check.hpp"
#include "leaks.hpp"
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int iTest = 1;
static string readBack(int fd)
{
	lseek(fd, 0, SEEK_SET);
	string r; char buf[256]; ssize_t n;
	while ((n = read(fd, buf, sizeof(buf))) > 0) r.append(buf, n);
	return r;
}

int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_putchar_fd\t: ")

	int fd = open("tripouille", O_RDWR | O_CREAT);
	ft_putchar_fd('a', fd);
	lseek(fd, SEEK_SET, 0);
	char s[10] = {0}; read(fd, s, 2);
	/* 1 */ check(!strcmp(s, "a")); showLeaks();
	close(fd);
	unlink("./tripouille");
	{
		int fd = open("tripouille", O_RDWR | O_CREAT | O_TRUNC, 0777);
		ft_putchar_fd('4', fd); ft_putchar_fd('2', fd);
		/* 2 */ check(readBack(fd) == "42"); showLeaks();
		close(fd); unlink("tripouille");
	}
	{
		int fd = open("tripouille", O_RDWR | O_CREAT | O_TRUNC, 0777);
		ft_putchar_fd('\n', fd);
		/* 3 */ check(readBack(fd) == "\n"); showLeaks();
		close(fd); unlink("tripouille");
	}
	{
		int fd = open("tripouille", O_RDWR | O_CREAT | O_TRUNC, 0777);
		ft_putchar_fd(0, fd);
		/* 4 */ check(readBack(fd) == string(1, '\0')); showLeaks();
		close(fd); unlink("tripouille");
	}
	{
		int fd = open("tripouille", O_RDWR | O_CREAT | O_TRUNC, 0777);
		ft_putchar_fd((char)200, fd);
		/* 5 */ check(readBack(fd) == string(1, (char)200)); showLeaks();
		close(fd); unlink("tripouille");
	}
	ft_putchar_fd('a', -1); //Invalid fd must not crash
	/* 6 */ check(1); showLeaks();

	write(1, "\n", 1);
	return (0);
}
