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

        while(Prog.getIsAdmin() && !Prog.exit()){

            Prog.AdminMenu();

            if(Prog.doSaveAdmins()){
                Data.setData(Prog.getAdminsData());
                Prog.setSaveAdmins(false);
            }

            if(Prog.doSaveData()){

                Prog.getRate();
                Prog.getSavePresets(Data.getSaveType(), Data.getEncryptData(), Data.getHash());
                Prog.setSaveData(false);

            }
        }

        while(!Prog.getIsAdmin() && !Prog.exit()){

            Prog.UserMenu();

            if(Prog.doSaveUsers())
                Data.setData(Prog.getMainData());
                Data.setData(Prog.getFloorsData());

                Prog.setSaveUsers(false);
        }
    }

    Data.Destroy();

}
