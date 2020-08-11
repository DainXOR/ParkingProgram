#include "parking.h"
#include "Functions.h"

#include <string>
#include <windows.h>
#include <iostream>


MainProg::MainProg()
    : Admin(false), IsRunning(true)
{

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

        printf("\n\n1) %s\n\n2) %s\n\n", "Iniciar sesion.", "Registrarse.");
        printf("%s", "Opcion: ");
        std::cin >> Ans;

        Ans = Ans <= 1? 1 : Ans == 256? 256 : 2;

        switch(Ans){

        case 1: Cont = Login(); break;
        case 2: Cont = Register(); setSaveUsers(Cont); break;
        default: return;

        }

        if(Cont){

            printf("\n\n1) %s\n\n2) %s\n\n3) %s\n\n", "Parquear.", "Retirar.", "Salir.");
            printf("%s", "Opcion: ");
            std::cin >> Ans;

            Ans = Ans <= 1? 1 : Ans >= 3? 3 : Ans;

            if(Login() || Register())
                switch(Ans){

                case 1: setSaveData(Parking()); break;
                case 2: setSaveData(PickUp()); break;
                case 3: return;

                }

            else{
                Cont = false;
                break;
            }

        }

            // Parquear

                // Usuario?

                    // Registrado o no?

                        // Registrado = Parquear

                            // Obtener hora

                        // No registrado = Registrar usuario

                            // Registro completado = Parquear

                                // Obtener hora

                            // No registra = Volver al menu

            // Retirar

                // Placa

                    // Estacionado o no?

                        // Estacionado = Confirmar cuenta

                            // Correcta

                                // Obtener hora

                                // Cobrar

                                    // Suficiente

                                        // Devuelta

                                        // Retirar

                                        // Volver al menu

                                    // Insuficiente

                                        // Restar total

                                        // Volver a cobrar

                            // Incorrecta 5 veces

                                // Consultar administracion

                                // Volver al menu

                        // No estacionado

                            // Consultar administracion

                            // Volver al menu



    }
}

void MainProg::AdminMenu(){

    static int Ans = 0;
    static bool InMenu = true;

    if(InMenu){
        system("cls");
        printf("%s\n\n\n 1) %s\n\n 2) %s\n\n 3) %s\n\n 4) %s\n\n", "Modo administrador", "Registrar nuevo administrador.", "Iniciar sesion.", "Salir del modo administrador.", "Salir del programa.");
        std::cin >> Ans;
        Ans = Ans <= 1? 1 : Ans >= 4? 4 : Ans;
    }

    switch(Ans){

    case 1: setSaveAdmins(RegisterAdmin()); break;
    case 2: setSaveData(LoginAdmin()); break;
    case 3: Admin = false; IsRunning = true; return;
    case 4: Admin = false; IsRunning = false; return;

    }
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

void MainProg::getSavePresets(short &SaveType, std::pair<int, int> &EncryptData, std::string &HashType)
{

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

bool MainProg::doSaveAdmins(){return SaveAdmins;}
bool MainProg::doSaveUsers(){return SaveUsers;}
bool MainProg::doSaveData(){return SaveData;}


bool MainProg::Parking(){

    std::pair<int, int> Spot = SearchSpot(UsersData[ActUser][2]);

    if(Spot.first == 0){
        system("cls");
        printf("Lamentablemente no hay espacio para guardar el vehiculo, le recomendamos regresar mas tarde.\n");
        system("pause");
        return false;
    }

    return 1;
}

bool MainProg::PickUp()
{
    return 1;
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
            printf("Su nombre o contraseña son incorrectos, por favor intente nuevamente.");
            printf("Si no se ha registrado regrese al menu e ingrese en la opcion 'Registrarse'.");
            printf("Para regresar al menu ingrese '1', de lo contrario presione la tecla 'Enter'.");
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
        else{

            int Ans = 0;

            system("cls");
            printf("\n\n1) %s\n\n2) %s\n\n3) %s\n\n4) %s\n\n5) %s\n\n6) %s", "Verificar ocupacion total.", "Verificar ocupacion por pisos.", "Buscar vehiculo.", "Cambiar tarifas.", "Cambiar datos de guardado.", "Salir.");
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

void MainProg::searchVehicle(std::string License){

    int Found = 0;

    system("cls");
    printf("|------------------------------------------------------------------------------------------|\n");
    printf("|  Nivel        Celda        Placa         Hora y Fecha Ingreso        Tipo de Estamiento  |\n");

    for(auto Level : FloorsData)
        for(auto Slot : Level.second)
            if(Slot.second[0].data() == License){

                Found++;
                printf("|------------------------------------------------------------------------------------------|\n");
                printf("|    %i            %i         %s           %s %s                   %s          |\n",
                       Level.first, Slot.first, Slot.second[0].data(), Slot.second[1].data(), Slot.second[2].data(), Slot.second[3].data());

            }

    printf("|__________________________________________________________________________________________|\n");

    if(!Found){

        system("cls");
        printf("\nNo se han encontrado vehiculos con la placa especificada.\n\n");
        system("pause");

    }

    return;

}








