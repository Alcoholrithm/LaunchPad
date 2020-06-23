#include <SD.h>
#include "myPlayer.h"
#include <avr/pgmspace.h>

#define SONGSWITCH \
    case 4:        \
    case 5:        \
    case 6:        \
    case 7:        \
    case 8:        \
    case 9:        \
    case 10:       \
    case 11:       \
    case 12:       \
    case 13:       \
    case 14:       \
    case 15
static unsigned char fileBuf[32];

VS10XX VS1053;
Sd2Card card;
SdVolume volume;
SdFile root;
SdFile file;

/**************************************************************/
volatile uint8_t sig = 1;
ISR(TIMER1_OVF_vect) //Timer1 Service
{
    if (sig == 0)
    {
        return;
    }
    player.resist = analogRead(pin::resistor_pin);
    player.button.scan(&(player.input));
    switch (player.input)
    {
    case 0:
    case 1:
        player.state = IDLE;
        break;
    case 2:
        if (player.state == PLAY)
            player.state = PAUSE;
        else
            player.state = PLAY;
        break;
    SONGSWITCH:
        player.state = PLAY;
    }
}

/**************************************************************/
#define RESOLUTION 65536        // Timer1 is 16 bit
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
    pinMode(pin::sd_cs_pin, OUTPUT);
    digitalWrite(pin::sd_cs_pin, HIGH);

    pinMode(pin::vs_xcs, OUTPUT);
    digitalWrite(pin::vs_xcs, HIGH);
}

/**************************************************************/
void myPlayer::initSD(void)
{
    dir_t p;
    char name[13];

    /* init sd card */
    if (!card.init(SPI_FULL_SPEED, pin::sd_cs_pin)) //SPI_FULL_SPEED
    {
        Serial.println("SD initialization failed.");
        while (1)
            ;
    }
    if (!volume.init(card))
    {
        Serial.println("Could not find FAT16/FAT32 partition.");
        while (1)
            ;
    }
    root.openRoot(volume);
    Serial.println("---- songs in TF card (root dir) ----");
    while (root.readDir(&p) != 0)
    {
        SdFile::dirName(p, name);
        char *s = name;
        s = strupr(s);
        if (strstr(s, ".MP3") || strstr(s, ".WAV") || strstr(s, ".WMA") || strstr(s, ".OGG") || strstr(s, ".AAC"))
        {
            uint32_t curPos = root.curPosition();
            uint16_t index = (curPos - 32) >> 5;
            if (file.open(&root, index, O_READ))
            {
                file.close();
                songs.appendsong(name, index);
                Serial.println(name);
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
    VS1053.init();
    button.init();
    Serial1.begin(9600);
    initTimer1(); // init timer1
    strncpy(songs.current_song, songs.shortList[0], songs.name_length);
}

/**************************************************************/
void myPlayer::play(uint16_t index)
{
    input = 99;
    unsigned char bytes; // How many bytes in buffer left
    unsigned char n;
    SPI.setClockDivider(SPI_CLOCK_DIV2);
    sig = 0; //disable interrupt
    if (file.open(&root, songs.fileIndex[songs.find(songs.current_song)][index], O_READ))
    {
        Serial.print("Playing ");
        Serial.println(songs.current_song);
    }
    else
    {
        Serial.print("Could not open: ");
        Serial.println(songs.current_song);
        return;
    }
    state = PLAY;
    while (bytes = file.read(fileBuf, sizeof(fileBuf)))
    {
        // actual audio data gets sent to VS10xx.
        sig = 1; //enable interrupt
        setVol();
        VS1053.writeData(fileBuf, bytes);
        switch (input)
        {
        SONGSWITCH:
            Serial.println("Switch song");
            file.close();
            return;
        case 3:
            //pattern
            break;
        case 0:
            songs.move_back();
            input = 99;
            Serial.println(songs.current_song);
            break;
        case 1:
            songs.move_forward();
            input = 99;
            Serial.println(songs.current_song);
            break;
            //   play 상태에서 -> 얘는 play()함수 내부에서 처리
            // 곡 누르면 바로 곡 재생
            // play,pause = pause
            // pattern = 인식
            // 곡 재생 끝나면 idle상태로 변환

            // pause 상태에서 -> 애도 play()함수 내부에서 처리
            // 곡 누르면 바로 곡 재생
            // play,pause = play
            // pattern = 인식
        }
        switch (state)
        {
        case PLAY:
            input = 99;
            break;
        case PAUSE:
            input = 99;
            while (state == PAUSE)
                ;
            break;
        }
        sig = 0; //disable interrupt
    }
    file.close();
    VS1053.softReset();
    Serial.println("[done!]");
    state = IDLE;
    sig = 1; //enable interrupt
}

void myPlayer::run(void)
{
    setVol();
    switch (input)
    {
    SONGSWITCH:
        play(input - 4);
        return;
    }
    if (state == IDLE)
    {
        switch (input)
        {
        case 0:
            songs.move_back();
            input = 99;
            Serial.println(songs.current_song);
            break;
        case 1:
            songs.move_forward();
            input = 99;
            Serial.println(songs.current_song);
            break;
        }
    }
    if (input == 3)
        ;   //////////////////////////패턴 버튼 처리
            //pattern
}

void myPlayer::setVol()
{
    if (resist != pre_resist)
    {
        pre_resist = resist;
        Vol = map(resist, 0, 1023, minVol, maxVol);
        VS1053.writeRegister(SPI_VOL, Vol * 0x101);
    }
}
