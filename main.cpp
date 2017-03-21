#include <fstream>
#include <cstdlib>
#include <ctime>
#include <direct.h>
#include <io.h>
#include <cstring>
#include "header.h"

using namespace std;

inline bool IsExist(vector<string> v,string s);
void CopyAllRule();
void CompileAllRule();
void ReplaceComponent(string sTarget,string sReplace);
void ReplaceComponent(string sFile,string sTarget,string sReplace);
vector<string> ListReport();

int main(int argv,char* argc[])
{
    fstream fIn,fOut;    
    string sTarget,sReplace,sFile;
    clock_t tic,toc;    

    if( argv == 2 && strcmp(argc[1],"-CopyAllRule")==0 ) // -CopyAllRule
    {
        CopyAllRule();
    }
    else if( argv==2 && strcmp(argc[1],"-Compile")==0 ) // -Compile
    {
        CompileAllRule();
    }
    else if( argv==4 && strcmp(argc[1],"-Change")==0 ) // -Change [target text] [replace text]
    {
        sTarget = argc[2];
        sReplace = argc[3];        

        ReplaceComponent(sTarget,sReplace);        
    }
    else if( argv == 4 && strcmp(argc[1],"-Change")!=0 ) // FARC.exe [Rule Name] [Target Text] [Replace Text]
    {
        sFile = argc[1];
        sTarget = argc[2];
        sReplace = argc[3];        

        ReplaceComponent(sFile,sTarget,sReplace);        
    }
    else if( argv == 6 && strcmp(argc[1],"-Change")==0 && strcmp(argc[4],"-Add")==0 )
    {
        cout << "\\\"\\\"" << endl;
    }
    else if( argv == 2 && strcmp(argc[1],"-ListReport")==0 ) // FARC.exe -ListReport
    {
        vector<string> vFile;

        vFile = ListReport();

        /*for(int i=0;i<vFile.size();i++)
        {
            cout << vFile.at(i) << endl;
        }*/
    }
    else
    {
        std::cout << "FARC.exe [FileName] [Find Text] [Replace Text]" << endl;    
        std::cout << "FARC.exe -Change [Find Text] [Replace Text]" << endl;    
        std::cout << "FARC.exe -Change [Find Text] [Replace Text] -Add [Parameter]" << endl;
        std::cout << "FARC.exe -CopyAllRule" << endl;
        std::cout << "FARC.exe -Compile" << endl;        
        std::cout << "FARC.exe -ListReport" << endl;
        return(0);
    }    

    return(0);
}

bool IsExist(vector<string> v,string s)
{
    for(int i=0;i<v.size();i++)
    {
        if( v.at(i) == s )
            return(true);
    }

    return(false);
}

void CopyAllRule()
{
    fstream fIn,fOut;            

    fIn.open("station.cfg");
    vector<string> vRuleName;    

    while( !fIn.eof() )
    {
        int iptr=0;
        string sLine,sRuleName;

        getline(fIn,sLine);

        if( sLine.empty() || sLine.at(0) == '#')
        {
            //system("pause");
            continue;
        }

        iptr = sLine.find("|");
        sRuleName = sLine.substr(iptr+1,sLine.length()-iptr-1);

        while( sRuleName.at(0) == ' ' )
        {
            sRuleName.erase(sRuleName.begin());
        }

        while (sRuleName.back() == ' ')
        {
            sRuleName.pop_back();
        }

        if( !IsExist(vRuleName,sRuleName) && sRuleName.substr(0,4) == "rule" )
        {
            std::cout << sRuleName << endl;
            string cmd;
            if( sRuleName.find(".report") != string::npos )
                cmd = "copy C:\\apfhome\\models\\300Works\\reports\\c\\DISPATCHER\\c\\RULES\\d\\DispatchScreen\\" + sRuleName + " " + ".\\Input\\" + sRuleName + " /Y";
            else
                cmd = "copy C:\\apfhome\\models\\300Works\\reports\\c\\DISPATCHER\\c\\RULES\\d\\DispatchScreen\\" + sRuleName + ".report " + ".\\Input\\" + sRuleName + ".report /Y";
            system(cmd.c_str());
            vRuleName.push_back(sRuleName);
        }


    }

    fIn.close();        
}

void CompileAllRule()
{
    fstream fIn,fOut;        
    clock_t tic,toc;        
    vector<string> vRuleName;    
    string sDir,sFilter,sPath;
    struct _finddata_t c_file;
    double hFile;
    
    sDir = ".\\Output";
    sFilter = "*.report";

    _chdir(sDir.c_str());
    hFile = _findfirst(sFilter.c_str(),&c_file);

    if( hFile != -1 )
    {
        do{
            vRuleName.push_back( c_file.name );                                
        }while( _findnext(hFile, &c_file) == 0 );
    }        
    _chdir("..");
    

    /*while( !fIn.eof() )
    {
        int iptr=0;
        string sLine,sRuleName;

        getline(fIn,sLine);

        if( sLine.empty() || sLine.at(0) == '#')
        {                
            continue;
        }

        iptr = sLine.find("|");
        sRuleName = sLine.substr(iptr+1,sLine.length()-iptr-1);

        while( sRuleName.at(0) == ' ' )
        {
            sRuleName.erase(sRuleName.begin());
        }

        while (sRuleName.back() == ' ')
        {
            sRuleName.pop_back();
        }

        if( !IsExist(vRuleName,sRuleName) && sRuleName.substr(0,4) == "rule" )
        {                
            vRuleName.push_back(sRuleName);
        }


    }

    fIn.close();*/    

    for(int i=0;i<vRuleName.size();i++)
    {
        string cmd;

        cmd = "C:\\apfhome\\bin.win32\\V7.4.6\\quintc -verbose .\\Output\\" + vRuleName.at(i) + " 300Works LiveDB";

        std::cout << "compiling " << vRuleName.at(i) << "..., (" << i << "/" << vRuleName.size() << ")" << endl;
        system(cmd.c_str());
    }
}

void ReplaceComponent(string sTarget,string sReplace)
{
    fstream fIn,fOut;        
    clock_t tic,toc;            
    vector<string> vRuleName;    
    string sDir,sFilter,sPath;
    struct _finddata_t c_file;
    double hFile;
    
    sDir = ".\\Input";
    sFilter = "*.report";

    _chdir(sDir.c_str());
    hFile = _findfirst(sFilter.c_str(),&c_file);

    if( hFile != -1 )
    {
        do{
            vRuleName.push_back( c_file.name );                                
        }while( _findnext(hFile, &c_file) == 0 );
    }        
    _chdir("..");


    for(int i=0;i<vRuleName.size();i++)
    {
        fIn.open(".\\Input\\" + vRuleName.at(i),fstream::in);

        if( fIn.is_open() )
        {
            fOut.open(".\\Output\\" + vRuleName.at(i),fstream::out);
        }
        else
        {
            cout << "Open file " << vRuleName.at(i) << " failed. terminate process." << endl;
            system("pause");
            return;
        }

        tic = clock();
        std::cout << "Handling " << vRuleName.at(i) << "...(" << i << "/" << vRuleName.size() << ")" << endl;

        while( !fIn.eof() )
        {
            int iPtr=0;
            string sLine;

            getline(fIn,sLine);        

            //cout << sLine << endl;

            while( (iPtr = sLine.find(sTarget,0)) != string::npos)
            {
                sLine.replace(iPtr,sTarget.length(),sReplace);
            }

            if(iPtr != string::npos )
            {
                sLine.replace(iPtr,sTarget.length(),sReplace);            
            }

            //cout << sLine << endl;
            fOut << sLine << endl;
        }
        toc = clock();
        std::cout << vRuleName.at(i) << " Done. CPU time:" << (double)(toc-tic)/1000 << " seconds." << endl;


        fIn.close();

        if( fOut.is_open() )
            fOut.close();
    }
    
}

void ReplaceComponent(string sFile,string sTarget,string sReplace)
{
    fstream fIn,fOut;        
    clock_t tic,toc;    

    fIn.open(".\\Input\\"+sFile,fstream::in);
    fOut.open(".\\Output\\"+sFile,fstream::out);

    tic = clock();
    std::cout << "Handling " << sFile << "..." << endl;

    while( !fIn.eof() )
    {
        int iPtr=0;
        string sLine;

        getline(fIn,sLine);        

        //cout << sLine << endl;

        while( iPtr=(sLine.find(sTarget,0)) != string::npos)
        {
            sLine.replace(iPtr,sTarget.length(),sReplace);
        }

        if(iPtr != string::npos )
        {
            sLine.replace(iPtr,sTarget.length(),sReplace);            
        }

        //cout << sLine << endl;
        fOut << sLine << endl;
    }
    toc = clock();
    std::cout << sFile << " Done. CPU time:" << (double)(toc-tic)/1000 << " seconds." << endl;


    fIn.close();
    fOut.close();
}

vector<string> ListReport()
{
    vector<string> vFiles;
    string sDir,sFilter,sPath;
    struct _finddata_t c_file;
    double hFile;

    //sDir = "\\\\10.20.27.35\\Public\\backup";
    //sDir = "C:\\Users\\00072690\\Documents\\Visual Studio 2010\\Projects\\PT_Manpower_Input_Translator\\PT_Manpower_Input_Translator";
    sDir = ".\\";
    sFilter = "*.*";

    _chdir(sDir.c_str());
    hFile = _findfirst(sFilter.c_str(),&c_file);

    if( hFile != -1 )
    {
        do{
            vFiles.push_back( c_file.name );                    
            cout << c_file.name << ",";
            if( c_file.attrib & _A_SUBDIR )            
                cout << "FOLDER" << endl;            
            else
                cout << "ELSE" << endl;
        }while( _findnext(hFile, &c_file) == 0 );
    }

    return(vFiles);
}
\ No newline at end of file
