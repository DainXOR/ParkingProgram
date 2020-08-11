#ifndef PARKING_H
#define PARKING_H

#include <map>

class MainProg
{
public:
    MainProg();
    void Setup();
    bool exit();

    void UserMenu();
    void AdminMenu();

    void setIsAdmin(bool Status);
    void setIsRunning(bool Status);
    void setSavePresets(short SaveType = 0, std::pair<int, int> EncryptData = std::pair<int, int>(0, 0), std::string HashType = "");

    bool getIsAdmin();
    bool getIsRunning();
    void getSavePresets(short &SaveType, std::pair<int, int> &EncryptData, std::string &HashType);

    std::map<int, std::string[3]>& getMainData();
    std::map<int, std::map<int, std::string[4]>>& getFloorsData();
    std::map<std::string, std::string>& getAdminsData();
    std::map<std::string, std::string[3]>& getUsersData();

    bool doSaveAdmins();
    void setSaveAdmins(bool Status);

    bool doSaveUsers();
    void setSaveUsers(bool Status);

    bool doSaveData();
    void setSaveData(bool Status);

protected:
    bool Parking();
    bool PickUp();

    bool Register();
    bool RegisterAdmin();
    bool Login();
    bool LoginAdmin();

private:
    bool VerifyAdmin(std::string Name, std::string Pass);
    bool VerifyAccount(std::string Name, std::string Pass);
    bool VerifyVehicle(std::string Name, std::string Pass, std::string License);

    bool ChangeCosts();
    bool ChangeSavePresets();

    void showGeneralData();
    void showLevelData(int Floor);
    void searchVehicle(std::string License);

private:
    std::map<int, std::string[3]> MainData;
    std::map<int, std::map<int, std::string[4]>> FloorsData;
    std::map<std::string, std::string> AdminsData;
    std::map<std::string, std::string[3]> UsersData;

    bool Admin;
    bool IsRunning;
    bool SaveAdmins;
    bool SaveUsers;
    bool SaveData;

    int TarifasTemporal[3];
    int TarifasMensual[3];

    short SaveType;
    std::pair<int, int> EncryptData;
    std::string Hash;

};

#endif // PARKING_H
