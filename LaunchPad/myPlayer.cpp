#include <SD.h>
#include "myPlayer.h"
#include  <avr/pgmspace.h>



static unsigned char fileBuf[32];

VS10XX VS1053;
Sd2Card     card;
SdVolume    volume;
SdFile root;
SdFile file;



/* PCM file Header */
unsigned char pcmHeader[44] = {
  'R', 'I', 'F', 'F',
  0xFF, 0xFF, 0xFF, 0xFF,
  'W', 'A', 'V', 'E',
  'f', 'm', 't', ' ',
  0x10, 0, 0, 0,          /* 16 */
  0x1, 0,                 /* PCM */
  0x1, 0,                 /* chan */
  0x40, 0x1F, 0x0, 0x0,   /* sampleRate */
  0x80, 0x3E, 0x0, 0x0,   /* byteRate */
  2, 0,                   /* blockAlign */
  0x10, 0,                /* bitsPerSample */
  'd', 'a', 't', 'a',
  0xFF, 0xFF, 0xFF, 0xFF
};

/**************************************************************/

ISR(TIMER1_OVF_vect) //Timer1 Service
{
/*
    player.input = player.button.scan();
    switch (player.input){
        case 0: case 1:
            player.state = IDLE;
            break;
        case 2:
            if (player.state == PLAY)
                player.state = PAUSE;
            else
                player.state = PLAY;
            break;
        case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 11: case 12:
            player.state = PLAY;
            
    }
*/
}


/**************************************************************/
#define RESOLUTION 65536           // Timer1 is 16 bit
void myPlayer::initTimer1(void) //initialize Timer1 to 100us overflow
{
    TCCR1A = 0;          // clear control register A
    TCCR1B = _BV(WGM13); // set mode as phase and frequency correct pwm, stop the timer

    long cycles;
    long microseconds = 500; //setup microseconds here
    unsigned char clockSelectBits;
    cycles = (F_CPU / 2000000) * microseconds; // the counter runs backwards after TOP, interrupt is at BOTTOM so divide microseconds by 2
    if (cycles < RESOLUTION)
        clockSelectBits = _BV(CS10); // no prescale, full xtal
    else if ((cycles >>= 3) < RESOLUTION)
        clockSelectBits = _BV(CS11); // prescale by /8
    else if ((cycles >>= 3) < RESOLUTION)
        clockSelectBits = _BV(CS11) | _BV(CS10); // prescale by /64
    else if ((cycles >>= 2) < RESOLUTION)
        clockSelectBits = _BV(CS12); // prescale by /256
    else if ((cycles >>= 2) < RESOLUTION)
        clockSelectBits = _BV(CS12) | _BV(CS10); // prescale by /1024
    else
        cycles = RESOLUTION - 1, clockSelectBits = _BV(CS12) | _BV(CS10); // request was out of bounds, set as maximum

    ICR1 = cycles;
    TCCR1B &= ~(_BV(CS10) | _BV(CS11) | _BV(CS12));
    TCCR1B |= clockSelectBits; // reset clock select register, and starts the clock

    TIMSK1 = _BV(TOIE1);
    TCNT1 = 0;
    sei(); //enable global interrupt
}


/**************************************************************/
void myPlayer::initIO(void)
{
  pinMode(SD_CS_PIN, OUTPUT);
  digitalWrite(SD_CS_PIN, HIGH);
  
  pinMode(VS_XCS, OUTPUT);
  digitalWrite(VS_XCS, HIGH);
}


/**************************************************************/
void myPlayer::initSD(void)
{
  dir_t p;
  char name[13];

  /* init sd card */
  if(!card.init(SPI_FULL_SPEED, SD_CS_PIN))   //SPI_FULL_SPEED
  { 
    Serial.println("SD initialization failed.");
	while(1);
  }
  if (!volume.init(card))
  {
    Serial.println("Could not find FAT16/FAT32 partition.");
    while(1);
  }
  root.openRoot(volume);
  Serial.println("---- songs in TF card (root dir) ----");
  while(root.readDir(&p) != 0)
  {
    SdFile::dirName(p, name);
	char *s = name;
	s = strupr(s);
	if(strstr(s,".MP3")||strstr(s,".WAV")||strstr(s,".WMA")||strstr(s,".OGG")
             ||strstr(s,".AAC"))
    {
		uint32_t curPos = root.curPosition();
		uint16_t index = (curPos - 32) >> 5;
		if (file.open(&root,index, O_READ))
		{
			file.close();
      songs.appendsong(name,index);
			Serial.println(songs.shortList[songs.size-1]);
		}	
    }
  }
  Serial.println("InitSD Done");
}

/**************************************************************/
void myPlayer::begin(void)
{
  	initIO();
  	initSD();
    Serial.println("init VS1053");
  	VS1053.init();
    //Serial.println("Init Timer1");
  	initTimer1();  // init timer1 
    Serial.println("begin done");
    strncpy(songs.current_song,songs.shortList[0],songs.name_length);
}

/**************************************************************/
void myPlayer::play(uint16_t index)
{

	unsigned char bytes;        // How many bytes in buffer left
	unsigned char n;
	
	SPI.setClockDivider(SPI_CLOCK_DIV2);
  Serial.println(songs.find(songs.current_song));
	if(file.open(&root,songs.fileIndex[songs.find(songs.current_song)][index],O_READ))
  	{
		Serial.print("Playing ");	
		Serial.println(songs.current_song);		
  	}
	else
	{
		Serial.print("Could not open: ");
		Serial.println(songs.current_song);
		while(1);
	}

	state = PLAY;
	while(bytes = file.read(fileBuf,sizeof(fileBuf)))
	{      
        // actual audio data gets sent to VS10xx.
       	VS1053.writeData(fileBuf,bytes);
				
	}
	file.close();
	VS1053.softReset();
	Serial.println("[done!]");

}
