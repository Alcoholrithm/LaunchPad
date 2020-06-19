#ifndef MYLIST_H_
#define MYLIST_H_
#include <SD.h>

class songInfo{
    static const int max_song = 10;

public:
    static const int name_length = 13;
    int find(char* str);
    int size=0;
    char current_song[name_length];
    char shortList[max_song][name_length];//파일명
    uint16_t fileIndex[max_song][12]; //-> 인덱스
    int operator[] (int button);
    // void song_name(char* str, int index);
    // void move_back(){
    //      strncpy(current_song,shortList[(find(current_song)-1)%size],name_length);
    //  }
    // void move_forward(){
    //      strncpy(current_song,shortList[(find(current_song)+1)%size],name_length);
    //  }
    void appendsong(char* str, uint16_t index);
    // void printfilename(uint16_t index);
    uint16_t findex[12];
};

#endif
/*

파일명이 있고 그리고 디렉토리에서 인덱스로 접근


곡 뒤로 곡 앞 재생/정지 패턴변화*/
