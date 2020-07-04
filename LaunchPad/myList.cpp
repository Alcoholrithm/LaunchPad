#include <String.h>
#include "myList.h"
#include <SD.h>

void trackInfo::appendtrack(char *str, uint16_t index)
{ //곡 정보 추가
    int i;
    char name[length];
    int num = 0;
    for (i = 0; i < length && str[i] != '@'; ++i)
        name[i] = str[i];
    name[i++] = '\0';
    for (; i < length && str[i] != '.'; ++i)
        num = num * 10 + str[i] - '0';
    for (i = 0; i < size && strcmp(shortList[i], name); ++i)
        ;
    if (i == size)
        strncpy(shortList[size++], name, length);
    fileIndex[find(name)][num] = index;
}
int trackInfo::find(const char *str) const
{ //  shortList에 저장된 위치 반환 없으면 -1
    for (int i = 0; i < size; ++i)
        if (!strcmp(shortList[i], str))
        {
            return i;
        }
    Serial.println("error occur in find");
    Serial.print("with str : ");
    Serial.println(str);
    for (int i = 0; i < size; ++i)
        Serial.println(shortList[i]);
    return -1;
}

void trackInfo::move_forward()
{ //shortList의 다음 인덱스로 이동
    strncpy(current_track, shortList[(find(current_track) + 1) % size], length);
}

void trackInfo::move_back() //shortList의 이전 인덱스로 이동
{
    int8_t index = find(current_track) - 1;
    index = index < 0 ? size - 1 : index;
    strncpy(current_track, shortList[index], length);
}

const int trackInfo::get_length() const{
    return trackInfo::length;
}
