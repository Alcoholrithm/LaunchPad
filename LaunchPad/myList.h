#ifndef MYLIST_H_
#define MYLIST_H_
#include <SD.h>

class songInfo
{
    static const int max_song = 10;
    int size = 0;

public:
    static const int name_length = 13;
    int find(const char *str) const;
    char current_song[name_length];        //현재 곡
    char shortList[max_song][name_length]; //파일명
    uint16_t fileIndex[max_song][11];      // 디렉토리상의 인덱스 저장
    void move_back();
    void move_forward();
    void appendsong(char *str, uint16_t index);
};

#endif
