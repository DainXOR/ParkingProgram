#include "Functions.h"

std::string getTimeStr(){

    time_t rawTime;
    tm *TimeInfo;
    char Buffer[80];

    time(&rawTime);
    TimeInfo = localtime(&rawTime);

    // I = 12H format   H = 24H format %H:%M:%S Con segundos
    strftime(Buffer, sizeof(Buffer), "%H:%M", TimeInfo);
    std::string Str(Buffer);

    return Str;

}

std::string getDateStr(){

    time_t rawTime;
    tm *TimeInfo;
    char Buffer[80];

    time(&rawTime);
    TimeInfo = localtime(&rawTime);

    // I = 12H format   H = 24H format %H:%M:%S Con segundos
    strftime(Buffer, sizeof(Buffer), "%d-%m-%Y", TimeInfo);
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

std::string IntToStr(int Num){

    std::string StrNum;

    for(; Num > 0;){

        StrNum += (Num % 10) + 48;
        Num /= 10;

    }

    std::string InvStrNum(StrNum.rbegin(), StrNum.rend());

    return InvStrNum;

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

std::string DecToStr(float Num){

    int IntPart = int(Num);
    float DecPart = Num - IntPart;

    std::string CompNum = IntToStr(IntPart) + "." + IntToStr(int(DecPart * 100));
    return CompNum;

}

int Count01(std::string Num){

    int Ones = 0;
    int Ceros = 0;
    int Long = int(Num.length());



    for(int i = Long - 1; i >= 0; i--){

        if(Num[unsigned(i)] == '0')
            Ceros += 1;

        else if(Num[unsigned(i)] == '1')
            Ones += 1;

    }

    if(Ones < Ceros)
        return 0;

    else if(Ceros < Ones)
        return 1;

    else if(Ceros == Ones)
        return 2;

    return -1;

}

void BinRedimension(const std::string &var1, std::string str2[], const int &key){

    bool finish = false;

    for (int i = 0; finish == false; ++i){

        for (int j = 0; j < key; ++j){

            if (var1[unsigned((key * i) + j)] != 0){
                str2[i].push_back(var1[unsigned((key * i) + j)]);
            }

            else{

                finish = true;
                break;

            }
        }
    }
}

int TextToBin(int Num){

    int Mod, Base = 1, Bin = 0;

    while(Num > 0){

        Mod = Num % 2;
        Bin += Mod * Base;
        Num /= 2;
        Base *= 10;

    }

    return Bin;

}

std::string BinToText(std::string &BinStr){

    char a = {static_cast<char>(stoi(BinStr, nullptr, 2))};
    std::string s;
    return s += a;

}

int NumDigits(int Num){

    int Count = 0;
    for(; Num > 0; Num /= 10, Count++);
    return Count;

}
