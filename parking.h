#ifndef PARKING_H
#define PARKING_H

#include <map>

class MainProg
{
public:
    MainProg();
    void Setup();

    void UserMenu();
    void AdminMenu();

    //*********  Setter functions  *********//
    void setIsAdmin(bool Status);
    void setIsRunning(bool Status);
    void setSavePresets(short SaveType = 0, std::pair<int, int> EncryptData = std::pair<int, int>(0, 0), std::string HashType = "");

    void setRatePresets(int TemporalRates[3], int MonthlyRates[3]);
    void setRatePresets(int CarTRate, int BikeTRate, int BicycleTRate, int CarMRate,int BikeMRate, int BicycleMRate);

    void setSaveAdmins(bool Status);
    void setSaveUsers(bool Status);
    void setSaveData(bool Status);

    //*********  Getter functions  *********//
    bool getIsAdmin();
    bool getIsRunning();
    void getSavePresets(short &SaveType, std::pair<int, int> &EncryptData, std::string &HashType);
    void getRatePresets(int *TemporalRates, int *MonthlyRates);
    void getRatePresets(int &CarTRate, int &BikeTRate, int &BicycleTRate, int &CarMRate, int &BikeMRate, int &BicycleMRate);

    std::map<int, std::string[3]>& getMainData();
    std::map<int, std::map<int, std::string[4]>>& getFloorsData();
    std::map<std::string, std::string>& getAdminsData();
    std::map<std::string, std::string[3]>& getUsersData();

    bool doSaveAdmins();
    bool doSaveUsers();
    bool doSaveData();

protected:
    std::pair<int, int> SearchSpot(std::string VehicleType);

    bool Parking(std::string ParkType);
    bool PickUp();

    bool Register();
    bool RegisterAdmin();
    bool Login();
    bool LoginAdmin();

private:
    bool VerifyAdmin(std::string Name, std::string Pass);
    bool VerifyUser(std::string Name, std::string Pass);
    bool VerifyVehicle(std::string License, std::string Name = "", std::string Pass = "");

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

    std::string ActUser;
    std::string UserPass;

    bool Admin;
    bool IsRunning;
    bool SaveAdmins;
    bool SaveUsers;
    bool SaveData;

    int TemporalRates[3];
    int MonthlyRates[3];

    short SaveType;
    std::pair<int, int> EncryptData;
    std::string Hash;

};

#endif // PARKING_H
