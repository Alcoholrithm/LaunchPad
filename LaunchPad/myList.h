#ifndef MYLIST_H_
#define MYLIST_H_
#include <SD.h>

class trackInfo
{
    static const int max_track = 10;
    int size = 0;
    static const int length = 13;
public:
    int find(const char *str) const;
    char current_track[length];        //현재 곡
    char shortList[max_track][length]; //파일명
    uint16_t fileIndex[max_track][11];      // 디렉토리상의 인덱스 저장
    void move_back();
    void move_forward();
    void appendtrack(char *str, uint16_t index);
    const int get_length(void) const;
};

#endif
