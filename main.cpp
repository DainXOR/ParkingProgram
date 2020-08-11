#include "filehandler.h"
#include "parking.h"


int main(){

    MainProg Prog;
    FileHandler Data;


    if(Data.LoadData())
        Data.getData(Prog.getMainData(), Prog.getFloorsData(), Prog.getAdminsData(), Prog.getUsersData());

    else{
        Prog.Setup();
        Data.setData(Prog.getAdminsData());
    }

    while(Prog.getIsRunning()){

        while(Prog.getIsAdmin() && Prog.getIsRunning()){

            Prog.AdminMenu();

            if(Prog.doSaveAdmins()){
                Data.setData(Prog.getAdminsData());
                Prog.setSaveAdmins(false);
            }

            if(Prog.doSaveData()){

                Prog.getRatePresets(Data.getTemporalRates(), Data.getMonthlyRates());
                Prog.getSavePresets(Data.getSaveType(), Data.getEncryptData(), Data.getHash());
                Prog.setSaveData(false);

            }
        }

        while(!Prog.getIsAdmin() && Prog.getIsRunning()){

            Prog.UserMenu();

            if(Prog.doSaveUsers()){
                Data.setData(Prog.getUsersData());
                Prog.setSaveUsers(false);
            }
            if(Prog.doSaveData()){
                Data.setData(Prog.getMainData());
                Data.setData(Prog.getFloorsData());
                Prog.setSaveData(false);
            }
        }
    }

    Data.Destroy();

}
