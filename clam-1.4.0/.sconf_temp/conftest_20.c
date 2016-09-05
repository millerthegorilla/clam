#include <sndfile.h>
int main()
{
	SF_INFO sfinfo;
	sf_open_fd(fileno(stdout),SFM_WRITE,&sfinfo,0);
	return 0;
}
