#include "parking.h"
#include "Functions.h"

#include <string>
#include <windows.h>
#include <iostream>


MainProg::MainProg()
    : Admin(false), IsRunning(true)
{

    SaveAdmins = true;
    SaveUsers = true;
    SaveData = true;

    TemporalRates[0] = 0;
    TemporalRates[1] = 0;
    TemporalRates[2] = 0;

    SaveType = 0;

}

void MainProg::Setup(){

    {

        std::string Name, Pass;

        system("cls");
        printf("%s\n %s\n\n", "Tenga mucho cuidado al ingresar los datos pues la informacion que registre aqui", "luego sera importante para su acceso a la configuracion del programa y sus datos.");
        printf("%s\n %s", "Ingrese el nombre de usuario de administrador:", "-");
        std::cin >> Name;

        system("cls");
        printf("%s\n\n %s\n %s\n\n", "Setup del programa.", "Tenga mucho cuidado al ingresar los datos pues la informacion que registre aqui", "luego sera importante para su acceso a la configuracion del programa y sus datos.");
        printf("%s\n %s", "Ingrese la contraseña de administrador:", "-");
        std::cin >> Pass;

        AdminsData[Name] = Pass;

    }

    {

        int CostosT[3];
        int CostosM[3];

        system("cls");
        printf("%s\n\n", "Elija las tarifas de parqueo por hora.");
        printf("%s", "Parqueo de carro temporal: ");
        std::cin >> CostosT[0];

        printf("%s", "Parqueo de moto temporal: ");
        std::cin >> CostosT[1];

        printf("%s", "Parqueo de bicicleta temporal: ");
        std::cin >> CostosT[2];

        system("cls");
        printf("%s\n\n", "Elija las tarifas de parqueo por semana.");
        printf("%s", "Parqueo de carro mensual: ");
        std::cin >> CostosM[0];

        printf("%s", "Parqueo de moto mensual: ");
        std::cin >> CostosM[1];

        printf("%s", "Parqueo de bicicleta mensual: ");
        std::cin >> CostosM[2];

    }

    {

        short setAdmin = 0;
        system("cls");
        printf("%s\n\n 1) %s\n 2) %s\n %s", "Desea ingresar como administrador?", "Si", "No", "Opcion: ");
        scanf("%hi", &setAdmin);

        setAdmin <= 1? setIsAdmin(true) : setIsAdmin(false);

    }
}

void MainProg::UserMenu(){

    while(true){

        int Ans = 0;
        bool Cont = false;

        system("cls");
        printf("\n\n1) %s\n\n2) %s\n\n", "Iniciar sesion.", "Registrarse.");
        printf("%s", "Opcion: ");
        std::cin >> Ans;

        Ans = Ans <= 1? 1 : Ans == 256? 256 : 2;

        switch(Ans){

        case 1: Cont = Login(); break;
        case 2: Cont = Register(); setSaveUsers(Cont); break;
        default: Admin = true; return;

        }

        if(Cont){

            printf("\n\n1) %s\n\n2) %s\n\n3) %s\n\n", "Parquear.", "Retirar.", "Salir.");
            printf("%s", "Opcion: ");
            std::cin >> Ans;

            Ans = Ans <= 1? 1 : Ans >= 3? 3 : Ans;

            switch(Ans){

            case 1:{
                int Type;
                std::string TypeStr;
                system("cls");
                printf("Seleccione el tipo de parqueo que desea\n\n");
                showRates();
                printf("\n\n1) Temporal\n2) Mensual\n\nOpcion: ");
                std::cin >> Type;

                TypeStr = Type <= 1? "T" : "M";

                setSaveData(Parking(TypeStr));
                break;
            }

            case 2:{
                setSaveData(PickUp());
                break;
            }

            case 3: return;

            }
        }
    }
}

void MainProg::AdminMenu(){

    static int Ans = 0;
    static bool InMenu = true;

    if(InMenu){
        system("cls");
        printf("%s\n\n\n 1) %s\n\n 2) %s\n\n 3) %s\n\n 4) %s\n\nOpcion: ", "Modo administrador", "Registrar nuevo administrador.", "Iniciar sesion.", "Salir del modo administrador.", "Salir del programa.");
        std::cin >> Ans;
        Ans = Ans <= 1? 1 : Ans >= 4? 4 : Ans;
    }

    switch(Ans){

    case 1: setSaveAdmins(RegisterAdmin()); break;
    case 2: setSaveData(LoginAdmin()); break;
    case 3: Admin = false; IsRunning = true; return;
    case 4: Admin = false; IsRunning = false; return;

    }

    return;

}

//***************************  Setter functions  ***************************//
void MainProg::setIsAdmin(bool Status){Admin = Status;}
void MainProg::setIsRunning(bool Status){IsRunning = Status;}
void MainProg::setSavePresets(short ST, std::pair<int, int> ED, std::string HT){

    SaveType = ST;
    EncryptData = ED;
    Hash = HT;
    return;

}

void MainProg::setRatePresets(int TR[3], int MR[3]){

    TemporalRates[0] = TR[0];
    TemporalRates[1] = TR[1];
    TemporalRates[2] = TR[2];

    MonthlyRates[0] = MR[0];
    MonthlyRates[1] = MR[1];
    MonthlyRates[2] = MR[2];

    return;

}

void MainProg::setRatePresets(int CarTRate, int BikeTRate, int BicycleTRate, int CarMRate, int BikeMRate, int BicycleMRate){

    TemporalRates[0] = CarTRate;
    TemporalRates[1] = BikeTRate;
    TemporalRates[2] = BicycleTRate;

    MonthlyRates[0] = CarMRate;
    MonthlyRates[1] = BikeMRate;
    MonthlyRates[2] = BicycleMRate;

    return;

}

void MainProg::setSaveAdmins(bool Status){SaveAdmins = Status;}
void MainProg::setSaveUsers(bool Status){SaveUsers = Status;}
void MainProg::setSaveData(bool Status){SaveData = Status;}

//***************************  Getter functions  ***************************//
bool MainProg::getIsAdmin(){return Admin;}
bool MainProg::getIsRunning(){return IsRunning;}

void MainProg::getSavePresets(short &ST, std::pair<int, int> &ED, std::string &HT){

    ST = SaveType;
    ED = EncryptData;
    HT = Hash;
    return;

}
void MainProg::getRatePresets(int *TR, int *MR){

    TR[0] = TemporalRates[0];
    TR[1] = TemporalRates[1];
    TR[2] = TemporalRates[2];

    MR[0] = MonthlyRates[0];
    MR[1] = MonthlyRates[1];
    MR[2] = MonthlyRates[2];

    return;

}

void MainProg::getRatePresets(int &CarTRate, int &BikeTRate, int &BicycleTRate, int &CarMRate, int &BikeMRate, int &BicycleMRate){

    CarTRate = TemporalRates[0];
    BikeTRate = TemporalRates[1];
    BicycleTRate = TemporalRates[2];

    CarMRate = MonthlyRates[0];
    BikeMRate = MonthlyRates[1];
    BicycleMRate = MonthlyRates[2];

    return;

}

std::map<int, std::string[3]> &MainProg::getMainData(){return MainData;}
std::map<int, std::map<int, std::string[4]>> &MainProg::getFloorsData(){return FloorsData;}
std::map<std::string, std::string> &MainProg::getAdminsData(){return AdminsData;}
std::map<std::string, std::string[3]> &MainProg::getUsersData(){return UsersData;}

int *MainProg::getTemporalRates(){return TemporalRates;}
int *MainProg::getMonthlyRates(){return MonthlyRates;}

bool MainProg::doSaveAdmins(){return SaveAdmins;}
bool MainProg::doSaveUsers(){return SaveUsers;}
bool MainProg::doSaveData(){return SaveData;}

std::pair<int, int> MainProg::SearchSpot(std::string VehicleType){

    int LastSlot = 0;

    for(auto Level : MainData){

        std::cout << StrToDec(Level.second[2]) << "\n";

        if(StrToDec(Level.second[2]) < 100 && Level.second[1] == VehicleType){

            for(auto Slot : FloorsData[Level.first]){

                if(Slot.first > LastSlot + 1)
                    return std::pair<int, int>(Level.first, LastSlot + 1);

                else
                    LastSlot = Slot.first;
            }
            return std::pair<int, int>(Level.first, LastSlot + 1);
        }
    }

    return std::pair<int, int>(0, 0);

}


bool MainProg::Parking(std::string ParkType){

    std::pair<int, int> Spot = SearchSpot(UsersData[ActUser][2]);

    if(Spot.first == 0){
        system("cls");
        printf("Lamentablemente no hay espacio para guardar el vehiculo, le recomendamos regresar mas tarde.\n");
        system("pause");
        return false;
    }
    else{

        int MaxSpots;
        float Porcent;

        system("cls");
        printf("Su vehiculo esta siento parqueado, ya puede retirarse y disfrutar de nuestras instalaciones.\n\nQue tenga un buen dia!\n");

        MaxSpots = StrToInt(MainData[Spot.first][0]);
        Porcent = StrToDec(MainData[Spot.first][2]);
        Porcent += 1 / MaxSpots;

        MainData[Spot.first][2] = DecToStr(Porcent);

        if(FloorsData[Spot.first][0][0] == "Floor Empty")
            FloorsData[Spot.first].erase(0);

        FloorsData[Spot.first][Spot.second][0] = UsersData[ActUser][1];
        FloorsData[Spot.first][Spot.second][1] = getTimeStr();
        FloorsData[Spot.first][Spot.second][2] = getDateStr();
        FloorsData[Spot.first][Spot.second][3] = ParkType;
        system("pause");
        return true;

    }
}

bool MainProg::PickUp(){

    if(VerifyVehicle(UsersData[ActUser][1]) &&
    VerifyVehicle(UsersData[ActUser][1], ActUser, UserPass) && searchVehicle(UsersData[ActUser][1], true) != std::pair<int, int>(0, 0)){

        system("cls");
        printf("Su vehiculo esta siendo retirado, por favor espere...\n\n");

        int MaxSpots, Cost, THours, TWeeks, VehicleType;
        float Porcent;
        std::string InDate, InHour, OutDate, OutHour, ParkType;
        std::pair<int, int> Pos = searchVehicle(UsersData[ActUser][1], true);

        /// Get vehicle type to know the rate
        if(UsersData[ActUser][2] == "C")
            VehicleType = 0;

        else if(UsersData[ActUser][2] == "M")
            VehicleType = 1;

        else
            VehicleType = 2;


        MaxSpots = StrToInt(MainData[Pos.first][0]);
        Porcent = StrToDec(MainData[Pos.first][2]);
        Porcent -= 1 / MaxSpots;
        MainData[Pos.first][2].clear();
        MainData[Pos.first][2] = DecToStr(Porcent);

        InHour = FloorsData[Pos.first][Pos.second][1];
        InDate = FloorsData[Pos.first][Pos.second][2];
        ParkType = FloorsData[Pos.first][Pos.second][3];

        OutHour = getTimeStr();
        OutDate = getDateStr();

        {
            std::string HoursStr, MinutesStr;
            int InHours, InMinutes, OutHours, OutMinutes;

            HoursStr = InHour[0] + InHour[1];
            MinutesStr = InHour[3] + InHour[4];

            InHours = StrToInt(HoursStr);
            InMinutes = StrToInt(MinutesStr);

            ///--------------------------------------------

            HoursStr.clear();
            MinutesStr.clear();

            HoursStr = OutHour[0] + OutHour[1];
            MinutesStr = OutHour[3] + OutHour[4];

            OutHours = StrToInt(HoursStr);
            OutMinutes = StrToInt(MinutesStr);

            ///--------------------------------------------

            if(InDate != OutDate){

                std::string InDayStr, InMonthStr, InYearStr, OutDayStr, OutMonthStr, OutYearStr;
                int Days = 0, Months = 0, Years = 0;

                InDayStr = InDate[0] + InDate[1];
                InMonthStr = InDate[2] + InDate[3];
                InYearStr = InDate[5] + InDate[6] + InDate[7] + InDate[8];

                OutDayStr = OutDate[0] + OutDate[1];
                OutMonthStr = OutDate[2] + OutDate[3];
                OutYearStr = OutDate[5] + OutDate[6] + OutDate[7] + OutDate[8];

                if(OutYearStr != InYearStr)
                    Years = StrToInt(OutYearStr) - StrToInt(InYearStr);

                if(OutMonthStr != InMonthStr){
                    if(StrToInt(OutMonthStr) - StrToInt(InMonthStr) < 0){
                        Years--;
                        Months = 12 + (StrToInt(OutMonthStr) - StrToInt(InMonthStr));
                    }
                    else
                        Months = StrToInt(OutMonthStr) - StrToInt(InMonthStr);
                }

                if(OutDayStr != InDayStr){
                    if(StrToInt(OutDayStr) - StrToInt(InDayStr) < 0){
                        Months--;
                        Days = 30 + (StrToInt(OutDayStr) - StrToInt(InDayStr));
                    }
                    else
                        Days = StrToInt(OutDayStr) - StrToInt(InDayStr);
                }

                TWeeks = (Days / 7) + (Months * 4) + (Years * 52);
                THours = (Days * 24) + (Months * 30) + (Years * 365);

                if(ParkType == "T")
                    Cost = THours * TemporalRates[VehicleType];

                else
                    Cost = TWeeks * MonthlyRates[VehicleType];

            }
            else{

                THours = OutHours - InHours;

                if(OutMinutes < InMinutes)
                    THours--;

                if(ParkType == "T")
                    Cost = THours * TemporalRates[VehicleType];

                else
                    Cost = MonthlyRates[VehicleType];

            }
        }

        FloorsData[Pos.first].erase(Pos.second);

        printf("El vehiculo ha sido retirado exitosamente!\n");
        system("pause");

        showTicket(Cost, InHour, InDate, OutHour, OutDate);

        return true;

    }

    else{

        system("cls");
        printf("El vehiculo no ha sido encontrado, si tiene alguna duda por favor contactar con los administradores.\n\n");
        printf("Linea de atencion: Numero no disponible.\n\n");
        system("pause");
        return false;

    }
}

bool MainProg::Register(){

    bool GoMenu = false;

    do{

        system("cls");
        printf("\n\n %s", "Ingrese el nombre de usuario: ");
        std::cin >> ActUser;

        printf("\n\n %s", "Ingrese la contraseña: ");
        std::cin >> UserPass;

        if(VerifyUser(ActUser, UserPass)){

            printf("%s\n\n", "Los datos ingresados ya existen, por favor intente nuevamente.\n");
            printf("%s", "Si desea volver al menu ingrese '0' (cero).");
            std::cin >> GoMenu;

            if((GoMenu = !GoMenu))
                return false;

        }
        else{

            std::string License, Type;
            int opt = 0;

            do{

                system("cls");
                printf("Ingrese los datos de su vehiculo\n\nPlaca: ");
                std::cin >> License;

                if(VerifyVehicle(License))
                    printf("La placa del vehiculo ya ha sido registrada, por favor intente nuevamente.\n");

                else
                    break;

            }while(true);

            printf("\nTipo de vehiculo:\n\n1) Carro\n2) Moto\n3) Bicicleta\n\nOpcion: ");
            std::cin >> opt;

            system("cls");
            printf("Guardando datos...");

            opt = opt <= 1? 1 : opt >= 3? 3 : opt;

            UsersData[ActUser][0] = UserPass; UsersData[ActUser][1] = License;

            switch(opt){

            case 1: UsersData[ActUser][2] = "C"; break;
            case 2: UsersData[ActUser][2] = "M"; break;
            case 3: UsersData[ActUser][2] = "B"; break;

            }

            setSaveUsers(true);
            return true;

        }

    }while(!GoMenu);

    return false;

}

bool MainProg::RegisterAdmin(){

    bool GoMenu = false;

    do{

        std::string Name, Pass;

        system("cls");
        printf("\n\n %s", "Ingrese el nombre de usuario: ");
        std::cin >> Name;

        printf("\n\n %s", "Ingrese la contraseña: ");
        std::cin >> Pass;

        if(VerifyAdmin(Name, Pass)){

            printf("%s\n\n", "Los datos ingresados ya existen, por favor intente nuevamente.");
            printf("%s", "Si desea volver al menu ingrese '0' (cero).");
            std::cin >> GoMenu;

        }
        else{
            system("cls");
            printf("%s", "Guardando datos...");
            AdminsData[Name] = Pass;
            return true;
        }

    }while(!GoMenu);

    return false;

}

bool MainProg::Login(){

    do{

        int Opt = 0;

        system("cls");
        printf("Ingrese sus datos\n\nNombre de usuario: ");
        std::cin >> ActUser;

        printf("\nContraseña: ");
        std::cin >> UserPass;

        if(VerifyUser(ActUser, UserPass)){
            system("cls");
            printf("Bienvenido/a %s\n", ActUser.data());
            break;
        }

        else{
            system("cls");
            printf("Su nombre o contraseña son incorrectos, por favor intente nuevamente.\n");
            printf("Si no se ha registrado regrese al menu e ingrese en la opcion 'Registrarse'.\n");
            printf("Para regresar al menu ingrese '1', de lo contrario presione la tecla 'Enter'.\n");
            std::cin >> Opt;

            if(Opt == 1){
                system("cls");
                printf("Regresando al menu...");
                return false;
            }
        }

    }while(true);

    return true;
}

bool MainProg::LoginAdmin(){

    bool GoMenu = false;

    do{

        static std::string Name, Pass;

        system("cls");
        printf("\n\n%s", "Ingrese el nombre de usuario: ");
        std::cin >> Name;

        printf("\n\n%s", "Ingrese la contraseña: ");
        std::cin >> Pass;

        if(!VerifyAdmin(Name, Pass)){

            printf("\n\n%s\n\n", "Los datos ingresados no existen, por favor intente nuevamente.");
            printf("%s", "Si desea volver al menu ingrese '0' (cero).");
            std::cin >> GoMenu;
        }
        else
            break;

    }while(true);

    do{
        int Ans = 0;

        system("cls");
        printf("\n\n1) %s\n\n2) %s\n\n3) %s\n\n4) %s\n\n5) %s\n\n6) %s\n\nOpcion: ", "Verificar ocupacion total.", "Verificar ocupacion por pisos.", "Buscar vehiculo.", "Cambiar tarifas.", "Cambiar datos de guardado.", "Salir.");
        std::cin >> Ans;

        Ans = Ans <= 1? 1 : Ans >= 6? 6 : Ans;

        switch(Ans){

        case 1: showGeneralData(); break; // Tabla general

        case 2:{

            int level;
            system("cls");
            printf("%s", "Ingrese el numero del nivel: ");
            std::cin >> level;
            showLevelData(level);
            break;

        } // Pedir piso y mostrar tabla del piso

        case 3:{

            std::string License;
            system("cls");
            printf("%s", "Ingrese la placa del vehiculo: ");
            std::cin >> License;
            searchVehicle(License);
            break;

        } // Pedir placa, si esta mostrar datos de estacionamiento, sino, indicar que no esta

        case 4:{

            if(doSaveData())
                ChangeCosts();

            else
                setSaveData(ChangeCosts());

            break;

        }

        case 5:{

            if(doSaveData())
                ChangeSavePresets();

            else
                setSaveData(ChangeSavePresets());

            break;

        }

        case 6: GoMenu = true; break;

        }



    }while(!GoMenu);

    return doSaveData();

}

bool MainProg::VerifyAdmin(std::string Name, std::string Pass){

    for(auto Data : AdminsData)
        if(Data.first == Name && Data.second == Pass)
            return true;

    return false;

}

bool MainProg::VerifyUser(std::string Name, std::string Pass){

    for(auto User : UsersData)
        if(User.first == Name && User.second[0] == Pass)
            return true;

    return false;

}

bool MainProg::VerifyVehicle(std::string Lc, std::string Name, std::string Pass){

    if(Name == "" && Pass == ""){
        for(auto License : UsersData)
            if(License.second[1] == Lc)
                return true;
    }

    else{
        for(auto User : UsersData)
            if(User.first == Name && User.second[0] == Pass && User.second[1] == Lc)
                return true;
    }

    return false;

}

bool MainProg::ChangeCosts(){

    int Opt[2] = {0, 0};

    showRates();

    printf("Desea cambiar alguna tarifa?\n\n1) Si\n2) No\n\nOpcion: ");
    std::cin >> *Opt;

    *Opt = *Opt <= 1? 1 : 2;

    switch(*Opt){

    case 1:{
        while(true){

            int Value = 0;

            system("cls");
            printf("Que tipo de tarifa desea cambiar?\n\n1) Temporal\n2) Mensual\n\nOpcion: ");
            std::cin >> Opt[0];
            Opt[0] = Opt[0] <= 1? 1 : 2;

            printf("\n\nElija el vehiculo\n\n1) Carro\n2) Moto\n3) Bicicleta\n\nOpcion: ");
            std::cin >> Opt[1];
            Opt[1] = Opt[1] <= 1? 1 : Opt[1] >= 3? 3 : Opt[1];

            printf("\n\nEscriba el valor de la nueva tarifa:\n-");
            std::cin >> Value;

            switch(Opt[0]){

            case 1: TemporalRates[Opt[1] - 1] = Value; break;
            case 2: MonthlyRates[Opt[1] - 1] = Value; break;

            }

            system("cls");
            printf("Valor cambiado con exito.\n\nDesea seguir haciendo cambios?\nRecuerde que para que estos sean guardados debera regresar al menu.\n\n1) Si\n2) No\n\nOpcion: ");
            std::cin >> *Opt;
            *Opt = *Opt <= 1? 1 : 2;

            if(*Opt == 1)
                break;

        }

        return true;

    }

    case 2: return false;
    default: return false;

    }
}

bool MainProg::ChangeSavePresets(){

    int Opt = 0;

    system("cls");
    printf("Opciones de guardado actuales:\n\n");

    switch(SaveType){

    case 0: printf("Sin seguridad."); break;
    case 1: printf("Algoritmo de encriptacion."); break;
    case 2: printf("Algoritmo de hash."); break;

    }

    printf("Desea cambiar las opciones de guardado?\n\n1) Si\n2) No\n\nOpcion: ");
    std::cin >> Opt;

    Opt = Opt <= 1? 1 : 2;

    if(Opt == 1){

        system("cls");
        printf("Elija el tipo de guardado\n\n");
        printf("1) Sin seguridad.\n"
               "2) Algoritmo de encriptacion.\n"
               "3) Algoritmo de hash.\n\n");
        printf("Opcion: ");
        std::cin >> Opt;

        switch(Opt){

        case 1: SaveType = 0; EncryptData = std::pair<int, int>(0, 0); Hash = ""; break;
        case 2:{

            SaveType = 1;
            int Type, Size;

            system("cls");
            printf("Elija el tipo de encriptado\n\n");
            printf("1) Corrimiento de bits.\n2) Intercambio de bits\n3) Intercalado de bits en zigzag\n 4) Algoritmo de aleatorizacion\n\nOpcion: ");
            std::cin >> Type;
            Type--;
            Type = Type <= 0? 0 : Type >= 3? 3 : Type;

            printf("Elija la cantidad de bits que se agruparan\n\n");
            printf("Cantidad: ");
            std::cin >> Size;

            EncryptData = std::pair<int, int>(Type, Size);
            break;

        }
        case 3:{

            SaveType = 2;

            system("cls");
            printf("Elija el tipo de hash que desea usar\n\n");
            printf("1) SHA-1\n2) DM5\n3) NTLM\n 4) RipeMD128\n5) CRC32\n\nOpcion: ");
            std::cin >> Opt;
            Opt = Opt <= 1? 1 : Opt >= 5? 5 : Opt;

            switch(Opt){

            case 1: Hash = "SHA-1"; break;
            case 2: Hash = "DM5"; break;
            case 3: Hash = "NTLM"; break;
            case 4: Hash = "RipeMD128"; break;
            case 5: Hash = "CRC32"; break;

            }

        }
        }

        system("cls");
        printf("Cambios efectuados, volviendo al menu...");
        return true;

    }

    else
        return false;

}

void MainProg::showTicket(int Money, std::string HourIn, std::string DateIn, std::string HourOut, std::string DateOut){

    system("cls");
    printf("|==================================|\n"
           "|------     PARQUEADERO      ------|\n"
           "|-----      DEBORA PLATA      -----|\n"
           "|==================================|\n"
           "|----   FECHA Y HORA INGRESO   ----|\n"
           "|----                          ----|\n"
           "|----        %s        ----|\n"
           "|----          %s           ----|\n"
           "|----                          ----|\n"
           "|----   FECHA Y HORA SALIDA    ----|\n"
           "|----                          ----|\n"
           "|----        %s        ----|\n"
           "|----          %s           ----|\n"
           "|----                          ----|\n"
           "|----                          ----|\n"
           "|----       VALOR A PAGAR      ----|\n"
           "|----                          ----|\n"
           "|----          $%i          ----|\n"
           "|----                          ----|\n"
           "|----                          ----|\n"
           "|----       GRACIAS  POR       ----|\n"
           "|----        SU VISITA!        ----|\n"
           "|==================================|\n", DateIn.data(), HourIn.data(), DateOut.data(), HourOut.data(), Money);

    system("pause");

}

void MainProg::showRates(){

    system("cls");
    printf("Tabla de tarifas\n\n");
    printf("|---------------------------------------------------------------------------------|\n");
    printf("|    Vehiculo               Tipo               Precio               Cobra cada    |\n");
    printf("|---------------------------------------------------------------------------------|\n");
    printf("|    Carro                Temporal              $%i                  Hora       |\n", TemporalRates[0]);
    printf("|---------------------------------------------------------------------------------|\n");
    printf("|    Moto                 Temporal              $%i                  Hora       |\n", TemporalRates[1]);
    printf("|---------------------------------------------------------------------------------|\n");
    printf("|    Bicicleta            Temporal              $%i                   Hora       |\n", TemporalRates[2]);
    printf("|---------------------------------------------------------------------------------|\n");
    printf("|    Carro                Mensual               $%i                Semana      |\n", MonthlyRates[0]);
    printf("|---------------------------------------------------------------------------------|\n");
    printf("|    Moto                 Mensual               $%i                Semana      |\n", MonthlyRates[1]);
    printf("|---------------------------------------------------------------------------------|\n");
    printf("|    Bicicleta            Mensual               $%i                 Semana      |\n", MonthlyRates[2]);
    printf("|_________________________________________________________________________________|\n\n");
    return;

}

void MainProg::showGeneralData(){

    system("cls");
    printf("|-----------------------------------------------------------------------------------|\n");
    printf("|  Nivel    Celdas Ocupadas     Celdas Totales    Tipo de Vehiculo     % Ocupacion  |\n");

    for(auto Level : MainData){

        std::string VType;

        if(Level.second[1] == "C")
            VType = "Carros";

        else if(Level.second[1] == "M")
            VType = "Motos";

        else if(Level.second[1] == "B")
            VType = "Bicicletas";

        printf("|-----------------------------------------------------------------------------------|\n");
        printf("|   %i            %i                  %i                %s             %3.2f%%     |\n",
               Level.first, int(StrToInt(Level.second[0]) * (StrToDec(Level.second[2])) / 100), StrToInt(Level.second[0]), VType.data(), StrToDec(Level.second[2]));

    }

    printf("|___________________________________________________________________________________|\n");
    system("pause");
    return;

}

void MainProg::showLevelData(int Floor){

    system("cls");
    printf("|-----------------------------------------------------------------------------|\n");
    printf("|  Celda        Placa         Hora y Fecha Ingreso        Tipo de Estamiento  |\n");

    for(auto Slot : FloorsData[Floor]){

        printf("|-----------------------------------------------------------------------------|\n");
        printf("|    %i         %s           %s %s                  %s           |\n",
               Slot.first, Slot.second[0].data(), Slot.second[1].data(), Slot.second[2].data(), Slot.second[3].data());

    }

    printf("|_____________________________________________________________________________|\n");
    system("pause");
    return;

}

std::pair<int, int> MainProg::searchVehicle(std::string License, bool Return){

    int Found = 0;

    if(!Return){
        system("cls");
        printf("|------------------------------------------------------------------------------------------|\n");
        printf("|  Nivel        Celda        Placa         Hora y Fecha Ingreso        Tipo de Estamiento  |\n");
    }

    for(auto Level : FloorsData)
        for(auto Slot : Level.second)
            if(Slot.second[0].data() == License){

                if(Return) return std::pair<int, int>(Level.first, Slot.first);

                Found++;

                if(!Return){
                    printf("|------------------------------------------------------------------------------------------|\n");
                    printf("|    %i            %i         %s           %s %s                   %s          |\n",
                           Level.first, Slot.first, Slot.second[0].data(), Slot.second[1].data(), Slot.second[2].data(), Slot.second[3].data());
                }

            }

    if(!Return)
        printf("|__________________________________________________________________________________________|\n");

    if(!Found && !Return){

        system("cls");
        printf("\nNo se han encontrado vehiculos con la placa especificada.\n\n");
        system("pause");

    }

    return std::pair<int, int>(0, 0);

}








