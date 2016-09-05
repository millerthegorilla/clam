#include <jack/jack.h>
#include <stdlib.h>
jack_client_t *client;
int main()
{
	client = jack_client_new ("foo");
	if ( client != NULL )
		jack_client_close (client);
	return 0;
}
