#include<alsa/asoundlib.h>
int main()
{
	int card = 0;
	snd_card_next(&card);
	return 0;
}
