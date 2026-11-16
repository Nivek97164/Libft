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
	title("ft_putendl_fd\t: ")

	int fd = open("tripouille", O_RDWR | O_CREAT);
	ft_putendl_fd((char*)"42", fd);
	lseek(fd, SEEK_SET, 0);
	char s[10] = {0}; read(fd, s, 4);
	/* 1 */ check(!strcmp(s, "42\n")); showLeaks();
	close(fd);
	unlink("./tripouille");
	{
		int fd = open("tripouille", O_RDWR | O_CREAT | O_TRUNC, 0777);
		ft_putendl_fd((char*)"", fd);
		/* 2 */ check(readBack(fd) == "\n"); showLeaks();
		close(fd); unlink("tripouille");
	}
	{
		int fd = open("tripouille", O_RDWR | O_CREAT | O_TRUNC, 0777);
		ft_putendl_fd((char*)"hello", fd);
		/* 3 */ check(readBack(fd) == "hello\n"); showLeaks();
		close(fd); unlink("tripouille");
	}
	{
		int fd = open("tripouille", O_RDWR | O_CREAT | O_TRUNC, 0777);
		ft_putendl_fd((char*)"a", fd); ft_putendl_fd((char*)"b", fd);
		/* 4 */ check(readBack(fd) == "a\nb\n"); showLeaks();
		close(fd); unlink("tripouille");
	}
	{
		int fd = open("tripouille", O_RDWR | O_CREAT | O_TRUNC, 0777);
		ft_putendl_fd((char*)"a\nb", fd);
		/* 5 */ check(readBack(fd) == "a\nb\n"); showLeaks();
		close(fd); unlink("tripouille");
	}
	{
		int fd = open("tripouille", O_RDWR | O_CREAT | O_TRUNC, 0777);
		string big(10000, 'x'); ft_putendl_fd((char*)big.c_str(), fd);
		/* 6 */ check(readBack(fd) == string(10000, 'x') + "\n"); showLeaks();
		close(fd); unlink("tripouille");
	}
	ft_putendl_fd((char*)"a", -1); //Invalid fd must not crash
	/* 7 */ check(1); showLeaks();

	write(1, "\n", 1);
	return (0);
}
