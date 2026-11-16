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
#include <climits>

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
	title("ft_putnbr_fd\t: ")

	int fd = open("tripouille", O_RDWR | O_CREAT, 0777);
	ft_putnbr_fd(0, fd);
	lseek(fd, SEEK_SET, 0);
	char s[42] = {0}; read(fd, s, 2);
	/* 1 */ check(!strcmp(s, "0")); showLeaks();
	close(fd);
	unlink("./tripouille");

	fd = open("tripouille", O_RDWR | O_CREAT, 0777);
	ft_putnbr_fd(10, fd);
	lseek(fd, SEEK_SET, 0);
	read(fd, s, 3);
	/* 2 */ check(!strcmp(s, "10")); showLeaks();
	close(fd);
	unlink("./tripouille");

	fd = open("tripouille", O_RDWR | O_CREAT, 0777);
	ft_putnbr_fd(INT_MAX, fd);
	lseek(fd, SEEK_SET, 0);
	read(fd, s, 11);
	/* 3 */ check(!strcmp(s, to_string(INT_MAX).c_str())); showLeaks();
	close(fd);
	unlink("./tripouille");

	fd = open("tripouille", O_RDWR | O_CREAT, 0777);
	ft_putnbr_fd(INT_MIN, fd);
	lseek(fd, SEEK_SET, 0);
	read(fd, s, 12);
	/* 4 */ check(!strcmp(s, to_string(INT_MIN).c_str())); showLeaks();
	close(fd);
	unlink("./tripouille");

	fd = open("tripouille", O_RDWR | O_CREAT, 0777);
	ft_putnbr_fd(-42, fd);
	lseek(fd, SEEK_SET, 0);
	s[read(fd, s, 4)] = 0;
	/* 5 ipenas */ check(!strcmp(s, "-42")); showLeaks();
	close(fd);
	unlink("./tripouille");
	{
		int fd = open("tripouille", O_RDWR | O_CREAT | O_TRUNC, 0777);
		ft_putnbr_fd(1, fd);
		/* 6 */ check(readBack(fd) == "1"); showLeaks();
		close(fd); unlink("tripouille");
	}
	{
		int fd = open("tripouille", O_RDWR | O_CREAT | O_TRUNC, 0777);
		ft_putnbr_fd(-1, fd);
		/* 7 */ check(readBack(fd) == "-1"); showLeaks();
		close(fd); unlink("tripouille");
	}
	{
		int fd = open("tripouille", O_RDWR | O_CREAT | O_TRUNC, 0777);
		ft_putnbr_fd(9, fd); ft_putnbr_fd(10, fd);
		/* 8 */ check(readBack(fd) == "910"); showLeaks();
		close(fd); unlink("tripouille");
	}
	{
		int fd = open("tripouille", O_RDWR | O_CREAT | O_TRUNC, 0777);
		ft_putnbr_fd(4, fd); ft_putnbr_fd(2, fd);
		/* 9 */ check(readBack(fd) == "42"); showLeaks();
		close(fd); unlink("tripouille");
	}
	{
		int fd = open("tripouille", O_RDWR | O_CREAT | O_TRUNC, 0777);
		ft_putnbr_fd(INT_MIN, fd); ft_putnbr_fd(INT_MAX, fd);
		/* 10 */ check(readBack(fd) == to_string(INT_MIN) + to_string(INT_MAX)); showLeaks();
		close(fd); unlink("tripouille");
	}
	{
		int vals[] = {-9, 99, 100, -100, 1000, 12345, -12345, 1000000000, -1000000000, 2147483646, -2147483647};
		bool ok = true;
		for (size_t i = 0; i < sizeof(vals) / sizeof(*vals); ++i)
		{
			int fd = open("tripouille", O_RDWR | O_CREAT | O_TRUNC, 0777);
			ft_putnbr_fd(vals[i], fd);
			if (readBack(fd) != to_string(vals[i])) ok = false; //No trailing '\n', no padding
			close(fd); unlink("tripouille");
		}
		/* 11 */ check(ok); showLeaks();
	}

	write(1, "\n", 1);
	return (0);
}
