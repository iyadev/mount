#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
using namespace std;
#ifdef WIN32
//Windows
#include <windows.h>
#define MAX_REGVALEUR 50
const string PATH  = "c:\\users\\Iya\\AppData\\Roaming\\IyaMount\\";
const string EXT =  ".bat";
#else
// Not windows
#define PATH "/etc/IyaMount/"
const string EXT =  ".sh";
#endif

using namespace std;

#ifdef WIN32
string getBiosVendor()
{
    HKEY hkCle = NULL;
    char sValeur[MAX_REGVALEUR];
    string ssValeur;
    DWORD dwTailleValeur1 = MAX_REGVALEUR;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", 0, KEY_ALL_ACCESS, &hkCle) == ERROR_SUCCESS)
    {
             RegQueryValueEx(hkCle, "BIOSVendor", NULL, NULL, (LPBYTE)sValeur, &dwTailleValeur1);
             RegCloseKey(hkCle);
             ssValeur = sValeur;
    }
    else
    {
        ssValeur = "error";
    }
    return ssValeur;
}
#else
string getBiosVendor()
{
    string vendor;
    char cvendor;
    FILE* fichier = NULL;
    fichier = fopen("/sys/class/dmi/id/bios_vendor", "r");

    if (fichier != NULL)
    {
        do {
            cvendor = fgetc (fichier);
            if( cvendor != 10 )
            {
                vendor = vendor + cvendor;
            }
        } while (cvendor != EOF && cvendor != 10 );
        fclose(fichier);
    }
    return vendor;
}
#endif
bool isVirtualBox()
{
    if(getBiosVendor() != "LENOVO")
    {
        return true;
    }
    else
    {
        return false;
    }
}
void start()
{
     string cmd;
     string is;
    if(isVirtualBox())
    {
        is = "virtualbox_start";

    }
    else
    {
        is = "native_start";
    }
        cmd = PATH + is + EXT ;
        cout << cmd << endl;
        system(cmd.c_str());
}
void stop()
{
     string cmd;
     string is;
    if(isVirtualBox())
    {
        is = "virtualbox_stop";

    }
    else
    {
        is = "native_stop";
    }
        cmd = PATH + is + EXT ;
        cout << cmd << endl;
        system(cmd.c_str());
}
int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        string temp = argv[1];
        if( temp == "--help")
        {
            cout << "IyaMount - v0 :" << endl;
            if(isVirtualBox())
            {
                cout << "\t Sur une VirtualBox" << endl;
            }
            else
            {
                cout << "\t Sur une Machine Physique" << endl;
            }
            cout << "Aide : \n\t --help Affiche l'aide \n\t --config Specifier un dossier de configuration manuel \n\t --start Executer le script de montage \n\t --stop Executer le script de demontage \n\t --check Renvoi un boolean, 0 pour physique, 1 pour Virtual Machine " << endl;
        }
        else if( temp == "--check")
        {
            cout << isVirtualBox() << endl;
        }
        else if( temp == "--config")
        {
            cout << "Not yet implanted" << endl;
        }
        else if( temp == "--start")
        {
            cout << "Execution de " ;
            start();
        }
        else if( temp == "--stop")
        {
            cout << "Execution de " ;
            stop();
        }
    }
    else
    {
        cout << "\t Veuillez saisir une commande." << endl;
    }
        system("pause");
       return 0;
}
