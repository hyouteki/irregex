#include "irregex.h"

int main(int argc, char **argv) {
	printf("%s\n", Irregex_Match(argv[1], argv[2]));
	return 0;
}
