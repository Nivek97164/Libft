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
	title("ft_putstr_fd\t: ")

	int fd = open("tripouille", O_RDWR | O_CREAT);
	ft_putstr_fd((char*)"42", fd);
	lseek(fd, SEEK_SET, 0);
	char s[10] = {0}; read(fd, s, 3);
	/* 1 */ check(!strcmp(s, "42")); showLeaks();
	close(fd);
	unlink("./tripouille");
	{
		int fd = open("tripouille", O_RDWR | O_CREAT | O_TRUNC, 0777);
		ft_putstr_fd((char*)"hello world", fd);
		/* 2 */ check(readBack(fd) == "hello world"); showLeaks();
		close(fd); unlink("tripouille");
	}
	{
		int fd = open("tripouille", O_RDWR | O_CREAT | O_TRUNC, 0777);
		ft_putstr_fd((char*)"", fd);
		/* 3 */ check(readBack(fd) == ""); showLeaks();
		close(fd); unlink("tripouille");
	}
	{
		int fd = open("tripouille", O_RDWR | O_CREAT | O_TRUNC, 0777);
		ft_putstr_fd((char*)"a\nb", fd);
		/* 4 */ check(readBack(fd) == "a\nb"); showLeaks();
		close(fd); unlink("tripouille");
	}
	{
		int fd = open("tripouille", O_RDWR | O_CREAT | O_TRUNC, 0777);
		ft_putstr_fd((char*)"ab", fd); ft_putstr_fd((char*)"cd", fd);
		/* 5 */ check(readBack(fd) == "abcd"); showLeaks();
		close(fd); unlink("tripouille");
	}
	{
		int fd = open("tripouille", O_RDWR | O_CREAT | O_TRUNC, 0777);
		string big(10000, 'x'); ft_putstr_fd((char*)big.c_str(), fd);
		/* 6 */ check(readBack(fd) == string(10000, 'x')); showLeaks();
		close(fd); unlink("tripouille");
	}
	{
		int fd = open("tripouille", O_RDWR | O_CREAT | O_TRUNC, 0777);
		char withNul[] = "ab\0cd"; ft_putstr_fd(withNul, fd);
		/* 7 */ check(readBack(fd) == "ab"); showLeaks();
		close(fd); unlink("tripouille");
	}
	ft_putstr_fd((char*)"a", -1); //Invalid fd must not crash
	/* 8 */ check(1); showLeaks();

	write(1, "\n", 1);
	return (0);
}
