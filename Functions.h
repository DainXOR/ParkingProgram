#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <ctime>

std::string getTimeStr(){

    time_t rawTime;
    tm *TimeInfo;
    char Buffer[80];

    time(&rawTime);
    TimeInfo = localtime(&rawTime);

    // I = 12H format   H = 24H format %H:%M:%S Con segundos
    strftime(Buffer, sizeof(Buffer), "%H:%M %d-%m-%Y", TimeInfo);
    std::string Str(Buffer);

    return Str;

}

int StrToInt(std::string Str){

    int Num = 0;

    for(unsigned int i = 0; Str.length() > i; i++){

        Num *= 10;
        Num += Str[i] - 48;

    }

    return Num;

}

float StrToDec(std::string Str){

    int IntNum = 0;
    float DecNum = 0;
    bool DecPart = false;

    for(unsigned int i = 0; Str.length() > i; i++){

        if(Str[i] == ',' || Str[i] == '.')
            DecPart = true;

        else if(DecPart){
            DecNum *= 10;
            DecNum += Str[i] - 48;
        }

        else{
            IntNum *= 10;
            IntNum += Str[i] - 48;
        }
    }

    while(DecNum > 1)
        DecNum /= 10;

    return (IntNum + DecNum);

}

#endif // FUNCTIONS_H
