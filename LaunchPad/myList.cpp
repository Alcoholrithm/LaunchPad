#include <String.h>
#include "myList.h"
#include <SD.h>

void songInfo::appendsong(char* str, uint16_t index){
    int i;
    char name[name_length];
    int num=0;
    for(i=0;i<name_length&&str[i]!='@';++i)
        name[i]=str[i];
    name[i++]='\0';
    for(;i<name_length&&str[i]!='.';++i)
        num=num*10+str[i]-'0';
    for(i=0;i<size&&strcmp(shortList[i],name);++i);   
    if(i==size)
        strncpy(shortList[size++],name,name_length);
    fileIndex[find(name)][num] = index;
}
int songInfo::find(char* str){
    for(int i = 0;i<size;++i)
        if(!strcmp(shortList[i],str)){
            return i; 
        }
    Serial.println("error occur in find");
    Serial.print("with str : ");
    Serial.println(str);
    for(int i=0;i<size;++i)
        Serial.println(shortList[i]);
    return -1;
}
