#include <vorbis/vorbisenc.h>
int main( int argc, char** argv )
{
	vorbis_info vi;
	vorbis_info_init( &vi );
	vorbis_encode_setup_init( &vi );
	return 0;
}
