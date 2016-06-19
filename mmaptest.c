#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void mmexec_test()
{
	char code[] = {
		0x55, 0x48, 0x89, 0xe5, 0x89, 0x7d, 0xfc, 0x8b, 0x7d, 0xfc, 0x83, 0xc7, 0x01, 0x89, 0xf8, 0x5d, 0xc3
	};

	void* ptr = mmap(0, sizeof(code), PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if(ptr == MAP_FAILED) {
		perror("mmap error");
		return;
	}

	memcpy(ptr, code, sizeof(code));

	typedef int (*TestFunc)(int);

	TestFunc func = ptr;

	int res = func(3);

	printf("result: %d\n", res);
}

int main()
{
	mmexec_test();
}