#include "filehandler.h"
#include "filehandler.h"

#include <windows.h>


FileHandler::FileHandler(std::string CF)
   : ConfigFile(CF), DataFile("Data.txt"), FloorsFile("Floors.txt"), AdminsFile("AdminsData.txt"), UsersFile("UsersData.txt"), SaveType(0)
{

   EncryptData = std::pair<int, int>(0, 0);
   Seed = 0;

   TemporalRates[0] = 0;
   TemporalRates[1] = 0;
   TemporalRates[2] = 0;

   MonthlyRates[0] = 0;
   MonthlyRates[1] = 0;
   MonthlyRates[2] = 0;

}

void FileHandler::Destroy(){

   SaveData();

}

void FileHandler::getData(std::map<int, std::string[3]> &P, std::map<int, std::map<int, std::string[4]>> &F, std::map<std::string, std::string> &AD, std::map<std::string, std::string[3]> &UD, int TR[3], int MR[3]){

   P = Parking;
   F = FloorsMap;
   AD = AdminsData;
   UD = UsersData;
   TR[0] = TemporalRates[0];
   TR[1] = TemporalRates[1];
   TR[2] = TemporalRates[2];

   MR[0] = MonthlyRates[0];
   MR[1] = MonthlyRates[1];
   MR[2] = MonthlyRates[2];

   return;

}

short &FileHandler::getSaveType(){return SaveType;}
std::pair<int, int> &FileHandler::getEncryptData(){return EncryptData;}
std::string &FileHandler::getHash(){return HashType;}

int *FileHandler::getTemporalRates(){return TemporalRates;}
int *FileHandler::getMonthlyRates(){return MonthlyRates;}

//******************  Load functions  ******************//
bool FileHandler::LoadData(){

   std::ifstream ReadFile;

   ReadFile.open(ConfigFile, std::_S_in);

   if(ReadFile.fail()){

       std::ofstream WriteFile;

       ReadFile.close();
       system("cls");
       newLoad(WriteFile);
       return false;

   }
   else{

       LoadConfig(ReadFile);
       ReadFile.close();
       return true;

   }

}

void FileHandler::newLoad(std::ofstream &File){

   int Data;
   int Opts[3];

   printf("%s\n\n %s\n\n", "Setup del lector de archivos","Elija los valores del programa, si ingresa '-1' se elegiran los valores por defecto.");
   printf("%s\n\n 1) %s\n 2) %s\n 3) %s\n\n", "Tipo de guardado de datos:", "Sin seguridad.", "Con encriptado.", "Con algoritmo hash.");
   printf("%s", "Opcion: ");
   scanf("%i", &Data);
   Data--;
   Data = Data > 2? 2 : Data;
   Opts[0] = Data;

   switch(Data){

   case 1:{
       system("cls");
       printf("%s\n\n 1) %s\n 2) %s\n 3) %s\n 4) %s\n\n", "Tipo de encriptacion:", "Corrimiento de bits.", "Intercambio de bits.", "Intercalado de bits", "Mezclado aleatorio");
       printf("%s", "Opcion: ");
       scanf("%i", &Opts[1]);

       Opts[1] = Opts[1] >= 3? 3 : Opts[1];
       Opts[1]--;

       system("cls");
       printf("%s\n\n", !Opts[1]? "Corrimiento de bits" : Opts[1] == 1? "Intercambio de bits" : Opts[1] == 2? "Intercalado de bits" : "Mezclado aleatorio");
       printf("%s","Cantidad de bits agrupados: ");
       scanf("%i", &Opts[2]);

       break;
   }
   case 2:{
       system("cls");
       printf("%s\n\n 1) %s\n 2) %s\n 3) %s\n 4) %s\n 5) %s\n\n", "Tipo de hash:", "SHA-1.", "MD5", "NTLM", "RipeMD-128", "CRC32");
       printf("%s", "Opcion: ");
       scanf("%i", &Opts[1]);

       Opts[1] = Opts[1] >= 5? 5 : Opts[1];
       Opts[1]--;
       break;
   }
   }

   system("cls");
   printf("%s\n\n %s\n", "Setup terminado.", "Creando archivos...\n");

   File.open(ConfigFile, std::_S_out);

   if(File.fail()){

       // Fail message
       File.close();

   }
   else{

       switch(Opts[0]){

       case 0:{
           File << std::to_string(Opts[0]) << ";\n";
           break;
       }
       case 1:{
           File << std::to_string(Opts[0]) << ":" << std::to_string(Opts[1]) << "," << std::to_string(Opts[2]) << ";\n";
           break;
       }
       case 2:{
           File << std::to_string(Opts[0]) << ":" << (!Opts[1]? "SHA-1\n;" : Opts[1] == 1? "MD5;\n" : Opts[1] == 2? "NTLM;\n" : Opts[1] == 3? "RipeMD-128;\n" : "CRC32;\n");
           break;
       }
       }

       File << "Data.txt:Floors.txt,AdminsData.txt,UsersData.txt;\n";
       File << TemporalRates[0] << "," << TemporalRates[1] << "," << TemporalRates[2] << "," << MonthlyRates[0] << "," << MonthlyRates[1] << "," << MonthlyRates[2] << ";";

   }

   File.close();
   File.open(DataFile, std::_S_out);
   File.close();
   File.open(FloorsFile, std::_S_out);
   File.close();
   File.open(AdminsFile, std::_S_out);
   File.close();
   File.open(UsersFile, std::_S_out);
   File.close();

   printf("%s\n\n %s", "Archivos creados.\n");
   system("cls");
   printf("IMPORTANTE: Para ingresar como administrador debera ingresar el numero 256 en el menu de usuario.\n\n");
   system("pause");
   printf("Iniciando programa principal...\n");
   return;


}

void FileHandler::LoadConfig(std::ifstream &File){

   for(short i = 0; !File.eof(); i += 1){

       std::string Aux;

       if(!i){

           std::getline(File, Aux);
           SaveType = Aux[0] - 48;
       }

       switch(SaveType){

       case 0: break;
       case 1:{

           int j = 0;

           for(char C : Aux){

               if(C == ':' || C == ',') j++;
               // else if(C == ',') i++;
               else if(C == ';') break;
               else{
                   switch(j){

                   case 1: EncryptData.first = C - 48; break;
                   case 2: EncryptData.second *= 10; EncryptData.second += C - 48; break;
                   default: break; //Error message

                   }
               }
           }
           break;
       }
       case 2:{

           short j = 0;

           for(char C : Aux){

               if(C == ':') j++;
               else if(C == ';') break;
               else{
                   switch(j){

                   case 1: HashType += C; break;
                   default: break; //Error message

                   }
               }
           }
           break;
       }
       default: system("cls"); printf("%s\n\n","Error."); break;

       }

       if(i == 1){
           std::getline(File, Aux);
           short j = 0;

           DataFile.clear();
           FloorsFile.clear();
           AdminsFile.clear();
           UsersFile.clear();

           for(char C : Aux){

               if(C == ':' || C == ',') j++;
               else if(C == ';') break;
               else{
                   switch(j){

                   case 0: DataFile.push_back(C); break;
                   case 1: FloorsFile.push_back(C); break;
                   case 2: AdminsFile.push_back(C); break;
                   case 3: UsersFile.push_back(C); break;
                   default: break; //Error message

                   }
               }
           }
       }

       else if(i == 2){

           std::getline(File, Aux);
           std::string NumAux;
           short j = 0;

           for(char C : Aux){

               if(C == ',' || C == ';') j++;

               if(C != ',' && C != ';') NumAux += C;
               else{
                   switch(j){

                   case 1: TemporalRates[0] = StrToInt(NumAux); break;
                   case 2: TemporalRates[1] = StrToInt(NumAux); break;
                   case 3: TemporalRates[2] = StrToInt(NumAux); break;
                   case 4: MonthlyRates[0] = StrToInt(NumAux); break;
                   case 5: MonthlyRates[1] = StrToInt(NumAux); break;
                   case 6: MonthlyRates[2] = StrToInt(NumAux); break;

                   }
                   NumAux.clear();
               }
           }
       }
   }

   File.close();

   switch(SaveType){

   case 0: normalLoad(File); break;
   case 1: encryptLoad(File); break;
   case 2: hashLoad(File); break;
   default: system("cls"); printf("%s\n\n","Error switch load type."); return; // Error message

   }

   File.close();
   return;

}

//******************  Load Types
void FileHandler::normalLoad(std::ifstream &File){

   File.open(DataFile, std::_S_in);
   if(File.fail()){

        system("cls");
        printf("%s\n\n","Error normal load.");
        return;
       // Error message

   }
   else{
       for(int i = 1; !File.eof(); i++){

           std::string Aux;
           std::getline(File, Aux);

           for(char C : Aux){

               static short j = -1, Key = 0;

               if(C == ',') j++;
               else if(C == '%') j = -1;
               else{
                   if(j < 0){

                       Parking[C - 48];
                       Key = C - 48;
                   }

                   else
                       Parking[Key][j].push_back(C);

               }
           }
       }
   }

   File.close();
   File.open(FloorsFile, std::_S_in);
   if(File.fail()){

       system("cls");
       printf("%s\n\n","Error normal load 2.");
       return;
      // Error message

   }
   else{
       for(int i = 1; !File.eof(); i++){

           //static short Floor = 0;
           bool InSlot = true;
           std::string Aux;
           std::getline(File, Aux);

           for(char C : Aux){

               static short j = -1, Floor = 0, Slot = 0;

               if(Aux.length() <= 4 && C != ';' && C != '0'){

                   Floor = 0;
                   Floor *= 10;
                   Floor += C - 48;

               }
               else if(Aux.length() <= 4 && C == ';')
                   break;

               else if(Aux.length() > 10){

                   if(C == ',') j++;

                   else if(C == '='){
                       InSlot = false;
                       FloorsMap[Floor][Slot];
                       j++;
                   }

                   else if(C == ';'){
                       j = -1;
                       Slot = 0;
                   }

                   else{
                       if(j < 0){

                           if(InSlot){
                               Slot *= 10;
                               Slot += C - 48;
                           }
                       }

                       else
                           FloorsMap[Floor][Slot][j].push_back(C);

                   }
               }

               else if(C == '0' && Aux.length() <= 4){
                   FloorsMap[Floor][Slot][0] = "Floor Empty";
                   FloorsMap[Floor][Slot][1] = "Floor Empty";
                   FloorsMap[Floor][Slot][2] = "Floor Empty";
                   FloorsMap[Floor][Slot][3] = "Floor Empty";
                   break;
               }
           }
       }
   }

   File.close();
   File.open(AdminsFile, std::_S_in);
   if(File.fail()){

        system("cls");
        printf("%s\n\n","Error normal load 3.");
        return;
       // Error message

   }
   else{

       for(int i = 0; !File.eof(); i++){

           std::string UserName, Pass;
           std::string Aux;
           std::getline(File, Aux);

           for(char C : Aux){

               static short j = 0;


               if(C == ':') j++;
               else if(C == ';'){AdminsData[UserName] = Pass; j = 0;}
               else{
                   switch(j){

                   case 0: UserName.push_back(C); break;
                   case 1: Pass.push_back(C); break;
                   default: break; // Error

                   }
               }
           }
       }
   }

   File.close();
   File.open(UsersFile, std::_S_in);
   if(File.fail()){

        system("cls");
        printf("%s\n\n","Error normal load 4.");
        return;
       // Error message

   }
   else{

       for(int i = 0; !File.eof(); i++){

           std::string UserName, Pass, License, Vehicle;
           std::string Aux;
           std::getline(File, Aux);

           for(char C : Aux){

               static short j = 0;


               if(C == ':' || C == ',') j++;

               else if(C == ';'){
                   UsersData[UserName][0] = Pass;
                   UsersData[UserName][1] = License;
                   UsersData[UserName][2] = Vehicle;
                   j = 0;
               }
               else{
                   switch(j){

                   case 0: UserName.push_back(C); break;
                   case 1: Pass.push_back(C); break;
                   case 2: License.push_back(C); break;
                   case 3: Vehicle.push_back(C); break;
                   default: break; // Error

                   }
               }
           }
       }
   }

   return;

}

void FileHandler::encryptLoad(std::ifstream &){

   // Do encrypts
   printf("%s\n", "Entro al encrypt");

}

void FileHandler::hashLoad(std::ifstream &){

   // Do Hashes
   printf("%s\n", "Entro al hash");

}

//******************  Save functions  ******************//
void FileHandler::SaveData(){

   std::ofstream WriteFile;

   WriteFile.open(ConfigFile, std::_S_out);

   if(WriteFile.fail()){

       // Fail message

   }
   else{

       WriteFile << SaveType << ";\n";
       WriteFile << DataFile << ":" << FloorsFile << "," << AdminsFile << "," << UsersFile << ";\n";
       WriteFile << TemporalRates[0] << "," << TemporalRates[1] << "," << TemporalRates[2] << "," << MonthlyRates[0] << "," << MonthlyRates[1] << "," << MonthlyRates[2] << ";";
       WriteFile.close();

       switch(SaveType){

       case 0: normalSave(WriteFile); break;
       case 1: encryptSave(WriteFile); break;
       case 2: hashSave(WriteFile); break;
       default: normalSave(WriteFile); break;

       }
   }
}

//******************  Save types
void FileHandler::normalSave(std::ofstream &File){

   File.open(DataFile, std::_S_out);

   if(File.fail()){

       system("cls");
       printf("%s\n", "Error en normal save.");

   }
   else
       for(auto Key : Parking)
           File << Key.first << "," << Key.second[0] << "," << Key.second[1] << "," << Key.second[2] << "%\n";

   File.close();
   File.open(FloorsFile, std::_S_out);

   if(File.fail()){

       system("cls");
       printf("%s\n", "Error en normal save 2.");

   }
   else
       for(auto Floors : FloorsMap){

           File << Floors.first << ";\n";

           for(auto Slots : Floors.second){

               if(Slots.second[0] == "Floor Empty")
                   File << Slots.first << "=\n";

               else
                   File << Slots.first << "=" << Slots.second[0] << "," << Slots.second[1] << "," << Slots.second[2] << "," << Slots.second[3] << ";\n";

           }
       }

   File.close();
   File.open(AdminsFile, std::_S_out);

   if(File.fail()){

       system("cls");
       printf("%s\n", "Error en normal save 3.");

   }
   else
       for(auto Admin : AdminsData)
           File << Admin.first << ":" << Admin.second << ";\n";

   File.close();
   File.open(UsersFile, std::_S_out);

   if(File.fail()){

       system("cls");
       printf("%s\n", "Error en normal save 4.");

   }
   else
       for(auto User : UsersData)
           File << User.first << ":" << User.second[0] << "," << User.second[1] << "," << User.second[2] << ";\n";

   File.close();

}

void FileHandler::encryptSave(std::ofstream &File){

    switch(EncryptData.first){

    case 0:{
        //CodedArray = EncryptType1(BinArray, EncryptSpace);
        break;
    }

    case 1:{ // Guardado de los datos de usuarios // Traduccion a binario

            std::string BinArray, CodedArray;

            File.open(DataFile, std::_S_out);

            if(File.fail()){

                printf("[ERROR]:No se pudo abrir el archivo de datos.\n");
                exit(-1);

            }

            for(auto Level : Parking){
                for(auto Data : Level.second){

                    int j = 0;

                    for(char C : Data){

                    std::string AuxStr;
                    int AuxInt;


                    AuxInt = TextToBin(C);

                    for(int l = 0; l < 8; l++){

                        AuxStr.push_back((AuxInt % 10) + 48);
                        AuxInt /= 10;

                    }

                    std::string AuxStrInv(AuxStr.rbegin(), AuxStr.rend());
                    BinArray += AuxStrInv;
                    AuxStr.clear();
                    AuxStrInv.clear();

                }

                BinArray += j < 2? "00101110" : "00111011";
                j++;

            } // Fin de traduccion a binario // Encriptacion segun lo configurado

            {

                std::string AuxArray1[400], AuxArray2[400], AuxStr;

                BinRedimension(BinArray, AuxArray1, EncryptData.second);
                EncryptType2(AuxArray1, AuxArray2, false);

                for(int j = 0; AuxArray1[j] != ""; j++)
                    AuxArray1[j].clear();

                for(std::string String : AuxArray2){

                    if(String == "") break;
                    AuxStr += String;

                }

                BinRedimension(AuxStr, AuxArray1, int(BinArray.length()));
                CodedArray = AuxArray1[0];

            }


            File << CodedArray << "\n";
            BinArray.clear();
            CodedArray.clear();

        }

            File.close();

         // Fin de guardado de datos generales

        break;
    }

    case 2: break;

    case 3: break;

    default: /*EncryptType2(false);*/ break;

    }

}

void FileHandler::hashSave(std::ofstream &File){



}

void FileHandler::EncryptType2(std::string Binstr[], std::string EncryptBintStr[], bool UndoEncrypt){

    for(int i = 0; Binstr[i] != ""; i++){

        int Comp;

            if(!UndoEncrypt)
                Comp = i > 0? Count01(Binstr[i - 1]) : -1;

            else
                Comp = i > 0? Count01(EncryptBintStr[i - 1]) : -1;

        for(int j = 0; j < EncryptData.second || Binstr[i][unsigned(j)] != '\0'; j++){

            if(Comp == 0){
                if((j + 1) % 2 == 0){

                    if(Binstr[i][unsigned(j)] == '0')
                        EncryptBintStr[i].push_back('1');

                    else if(Binstr[i][unsigned(j)] == '1')
                        EncryptBintStr[i].push_back('0');

                }

                else {

                    if(Binstr[i][unsigned(j)] == '1')
                        EncryptBintStr[i].push_back('1');

                    else if(Binstr[i][unsigned(j)] == '0')
                        EncryptBintStr[i].push_back('0');

                }
            }

            else if(Comp == 1){
                if((j + 1) % 3 == 0){

                    if(Binstr[i][unsigned(j)] == '0')
                        EncryptBintStr[i].push_back('1');

                    else if(Binstr[i][unsigned(j)] == '1')
                        EncryptBintStr[i].push_back('0');

                }

                else{

                    if(Binstr[i][unsigned(j)] == '1')
                        EncryptBintStr[i].push_back('1');

                    else if(Binstr[i][unsigned(j)] == '0')
                        EncryptBintStr[i].push_back('0');

                }
            }

            else if(Comp == 2 || i == 0)
                Binstr[i][unsigned(j)] == '0'?
                    EncryptBintStr[i].push_back('1') :
                    EncryptBintStr[i].push_back('0');

        }
    }
}

//************** Setter Functions  **************//

void FileHandler::setDataFile(std::string Name){

   remove(DataFile.c_str());
   DataFile.clear();
   DataFile = Name;
   SaveData();
   return;

}

void FileHandler::setFloorFile(std::string Name){

   remove(FloorsFile.c_str());
   FloorsFile.clear();
   FloorsFile = Name;
   SaveData();
   return;

}

void FileHandler::setAdminsFile(std::string Name){

   remove(AdminsFile.c_str());
   AdminsFile.clear();
   AdminsFile = Name;
   SaveData();
   return;

}

void FileHandler::setUsersFile(std::string Name){

   remove(UsersFile.c_str());
   UsersFile.clear();
   UsersFile = Name;
   SaveData();
   return;

}

void FileHandler::setSaveType(short type){

   SaveType = type;
   switch(SaveType){

   case 0: EncryptData = std::pair<int, int>(0, 0); HashType = ""; break;
   case 1: EncryptData = std::pair<int, int>(3, 12); break;
   case 2: HashType = "RipeMD128"; break;
   default: SaveType = 0; EncryptData = std::pair<int, int>(0, 0); HashType = ""; break;

   }

   SaveData();
   return;

}

void FileHandler::setSaveType(short EncryptType, short BitsBlocks){

   SaveType = 1;
   EncryptType = EncryptType < 1? 1 : EncryptType > 4? 4 : EncryptType;
   EncryptData = std::pair<int, int>(EncryptType, BitsBlocks);
   SaveData();
   return;

}

void FileHandler::setSaveType(std::string Hash){

   SaveType = 2;
   HashType = Hash;
   SaveData();
   return;

}

void FileHandler::setData(std::map<int, std::string[3]> &P){Parking = P; SaveData(); SaveData(); return;}
void FileHandler::setData(std::map<int, std::map<int, std::string [4]>> &F){FloorsMap = F; SaveData(); return;}
void FileHandler::setData(std::map<std::string, std::string> &AD){AdminsData = AD; SaveData(); return;}
void FileHandler::setData(std::map<std::string, std::string[3]> &UD){UsersData = UD; SaveData(); return;}
void FileHandler::setData(int *TRates, int *MRates){

    TemporalRates[0] = TRates[0];
    TemporalRates[1] = TRates[1];
    TemporalRates[2] = TRates[2];

    MonthlyRates[0] = MRates[0];
    MonthlyRates[1] = MRates[1];
    MonthlyRates[2] = MRates[2];

    SaveData();
    return;

}






















