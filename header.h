#ifndef __header_h__
#define __header_h__

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>


using namespace std;

class cReport
{
private:
    string sName,sPath;
    vector<double> vVersion;
public:
    string Name(){return(sName);}
    string Path(){return(sPath);}
};

#endif
