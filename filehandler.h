#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>

class FileHandler
{
public:
    FileHandler(std::string ConfigFile = "Config.txt");
    void Destroy();

    void getData(std::map<int, std::string[3]> &Parking, std::map<int,std::map<int, std::string[4]>> &Floors, std::map<std::string, std::string> &AdminsData, std::map<std::string, std::string[3]> &UsersData);
    short &getSaveType();
    std::pair<int, int> &getEncryptData();
    std::string &getHash();
    int *getTemporalRates();
    int *getMonthlyRates();


    bool LoadData();
    void SaveData();

    void saveConfig();
    void saveParking();
    void saveFloors();
    void saveAdminsData();
    void saveUserData();

    //*********  Setter functions  *********//
    void setDataFile(std::string Name);
    void setFloorFile(std::string Name);
    void setAdminsFile(std::string Name);
    void setUsersFile(std::string Name);

    void setSaveType(short type);
    void setSaveType(short EncryptType, short BitsBlocks);
    void setSaveType(std::string HashType);

    void setData(std::map<int, std::string[3]> &Parking);
    void setData(std::map<int,std::map<int, std::string[4]>> &Floors);
    void setData(std::map<std::string, std::string> &AdminsData);
    void setData(std::map<std::string, std::string[3]> &UsersData);

    void setTemporalRates(int TemporalRatesArray[3]);
    void setTemporalRates(int CarTRate, int BikeTRate, int BicycleTRate);

    void setMonthlyRates(int MonthlyRatesArray[3]);
    void setMonthlyRates(int CarMRate, int BikeMRate, int BicycleMRate);

protected:
    //*********  Load functions  *********//
    void newLoad(std::ofstream &);
    void LoadConfig(std::ifstream &);

    // Load types
    void normalLoad(std::ifstream &);
    void encryptLoad(std::ifstream &);
    void hashLoad(std::ifstream &);

    //*********  Save functions  *********//
    // Save types
    void normalSave(std::ofstream &);
    void encryptSave(std::ofstream &);
    void hashSave(std::ofstream &);

    //*********  Encrypt functions  *********//
    /// Corrimiento de bits en rueda
    void EncryptType1(bool UndoEncrypt);
    /// Intercambio de bits basado en el grupo anterior
    void EncryptType2(bool UndoEncrypt);
    /// Intercalado de bits en zigzag
    void EncryptType3(bool UndoEncrypt);
    /// Mezclado aleatorio
    void EncryptType4(bool UndoEncrypt);

    //*********  Hash functions  *********//
    void Hash_SHA1(bool UndoHash);
    void Hash_DM5(bool UndoHash);
    void Hash_NTLM(bool UndoHash);
    void Hash_RipeMD128(bool UndoHash);
    void Hash_CRC32(bool UndoHash);

private:
    /// Parking[Floor][MaxSlots, Vehicle, Ocupation]
    std::map<int, std::string[3]> Parking;
    /// FloorsMap[Floor][Slot][License, Hour, Kind]
    std::map<int,std::map<int, std::string[4]>> FloorsMap;
    /// AdminsData[AdminName] = Pass
    std::map<std::string, std::string> AdminsData;
    /// map[UserName][Pass, License, Vehicle]
    std::map<std::string, std::string[3]> UsersData;
    /// First = Type / Second = Bits size block
    std::pair<int, int> EncryptData;

    int TemporalRates[3];
    int MonthlyRates[3];

    std::string ConfigFile;
    std::string DataFile;
    std::string FloorsFile;
    std::string AdminsFile;
    std::string UsersFile;
    std::string HashType;

    /// 0: No changes to the data in the save file.
    /// 1: Aplies an encriptation algorithm.
    /// 2: Aplies a hash algorithm.
    short SaveType;
    short Seed;

};

#endif // FILEHANDLER_H
