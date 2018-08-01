#include <stdlib.h>
//	check_serial returns 1 if the
//	serial number is OK.
int check_serial(unsigned serial)
{
	if((serial & 0x10) == 0x11)
		return 1;
	else return 0;
}
//	main() returns 0 if the serial number
//	is OK and non-zero otherwise.
int main(int argc, char **argv)
{
	unsigned serial_no;
	if(argc <=1)return 2;
	serial_no = (unsigned)atoi(argv[1]);
	if(check_serial(serial_no))return 0;
	else return 1;
}
