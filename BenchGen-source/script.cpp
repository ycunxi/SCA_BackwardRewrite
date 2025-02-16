#include <vector>
#include <glob.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <functional>
#include <unistd.h>
#include <algorithm>
#include <map>
#include <iostream>
using namespace std;
typedef vector<string> VEC_STR;
//report for incremental sat
double return_MAX(double a,double b)
{
    if(a>=b)
    {
        return a;
    }
    else{   return b;}
}

double return_MIN(double a,double b)
{
    if(a>=b)
    {
        return b;
    }
    else{   return a;}
}


map<int, double> map_update_MAX(map<int, double> original_map,int key, double value)
{
    map<int, double>::iterator map_i;
    map_i = original_map.find(key);
    if (map_i == original_map.end()) {
        original_map.insert(std::map<int, double>::value_type(key,value));
    }
    else
    {
        map_i->second = return_MAX(map_i->second, value);
    }
    return original_map;
}

void printMap(map<int,double> map_max, map<int, double> map_min)
{
    map<int, double>::iterator map_max_i,map_min_i;
    for (map_max_i=map_max.begin(),map_min_i=map_min.begin(); map_max_i!=map_max.end(); ++map_max_i,++map_min_i) {
        cout<<map_max_i->first<<" "<<map_max_i->second<<" "<<map_min_i->second<<endl;
    }
}


bool Random_Or_Corrup(string input)
{
    int find_1=0; int find_2=0;
    find_1 = input.find("randCam",0);find_2 = input.find("corrCam",0);
    if(find_1>=0){ return true;} //random
    else { return false;}        // corrupt
}

string Cam_Gates(string input)
{
    int find_start;find_start = input.find("Cam",50);
    int find_end;  find_end = input.find(".v",find_start);
    string num; 
    num.assign(input,find_start+3,find_end-find_start-3);
    return num;
}
string Cam_Gates_NumberofRandom(string input) //works for new random tests
{
    int find_number_start=0; int find_number_end=0;
    find_number_start = input.find("-fmt-",0);
    find_number_end = input.find("-randCam",0);
    string num_rand; num_rand.assign(input,find_number_start+5,find_number_end-find_number_start-5);
	return num_rand;

}
vector<string> Files_vector(const string& pattern){
    glob_t glob_result;
    glob(pattern.c_str(),GLOB_TILDE,NULL,&glob_result);
    vector<string> files;
    for(unsigned int i=0;i<glob_result.gl_pathc;++i){
        files.push_back(string(glob_result.gl_pathv[i]));
    }
    globfree(&glob_result);
    return files;
}
//Get oracle file
string GetFileName_Oracle()
{
    vector<string> files_vec = Files_vector("*abcmap-fmt.v");
    string oracle_str = *files_vec.begin();
    return oracle_str;
}
//Get random cam circuits
vector<string> Random_Cam_Circuits()
{
//Here changed for the new random tests    fmt-randCam*  => fmt-*-randCam*
    vector<string> files_vec = Files_vector("*.csf");
    return files_vec;
}
vector<string> MUX4_Cam_Circuits()
{
//Here changed for the new random tests    fmt-randCam*  => fmt-*-randCam*
    vector<string> files_vec = Files_vector("*-mux4-*.v");
    return files_vec;
}

vector<string> QBF_SMARTCAM_CIRCUIT()
{
    vector<string> files_vec = Files_vector("*abcmap-fmt-qbf*.v");

}

//Get Corruptibility based cam circuits
vector<string> Corrup_Cam_Circuits()
{
    vector<string> files_vec = Files_vector("*abcmap-fmt-corrCam*.v");
    return files_vec;
}
void printVec_str(VEC_STR str_vec)
{
    VEC_STR::iterator str_vec_i;
    for (str_vec_i=str_vec.begin(); str_vec_i!=str_vec.end(); ++str_vec_i) {
        cout<<*str_vec_i<<endl;
    }
}
//Output log name
string BenchMark_Name(string oracle_filename)
{
    int find =0;
    find = oracle_filename.find("abcmap-fmt.v",0);
    oracle_filename.replace(find-1, find+12,"deCam.log");
    return oracle_filename;
}
//new feature for incremental SAT
string GetUsrbintimereport_Time(string time_file)
{
    ifstream timein(time_file.c_str());
    string input,time;
    int find_usertime =0; int find_time_begin = 0;
    while(getline(timein,input))
    {
        input.erase( std::remove_if( input.begin(), input.end(), ::isspace   ), input.end()   );
        find_usertime = input.find("User",0);
        if(find_usertime>=0)
        {
            find_time_begin = input.find(":",0);
            time.assign(input,find_time_begin+1,input.length());
        }
    }

    return time;
}
string GetUsrbintimereport_RandomNum(string time_file)
{
    ifstream timein(time_file.c_str());
    string input,num;
    int find_command = 0; 
    while(getline(timein,input))
    {
        find_command = input.find("Command",0);
        if(find_command>=0)
        {
            num = Cam_Gates_NumberofRandom(input);
        }
    }
    return num;
}
string getTimeFromTIMELOG(string timelog) 
{
    ifstream timein(timelog.c_str());
    string input,gate_num;
    int find_command = 0;
    int start=0; int end=0;
    while(getline(timein,input))
    {
        find_command = input.find("User time",0);
        if(find_command>=0)
        {
            start = input.find(":",0);
            gate_num.assign(input,start+1, input.length()-start-1);       
        }
    }
    return gate_num;
}

int num_gate_csf(string csf)
{
    string input;
    int c=0;
    ifstream fin(csf.c_str());
    while(getline(fin,input))
    {
        ++c;
    }
    return c;
}
int main()
{
    
    string command_start_deCam = "/usr/bin/time -v -o temp-time ./petBoss.exe -b < ";
    vector<string> random_cam,corrup_cam;
    random_cam = Random_Cam_Circuits(); 
    VEC_STR::iterator random_i,corrup_i;
    ofstream logout("tcad15_comb.log");
    int count = 0;
    for (random_i=random_cam.begin(); random_i!=random_cam.end();++random_i) 
    {
        count = num_gate_csf(*random_i);   
        command_start_deCam = command_start_deCam + *random_i;
        system(command_start_deCam.c_str());
        command_start_deCam = "/usr/bin/time -v -o temp-time ./petBoss.exe -b < ";
        cout<<*random_i<<" "<<count<<" "<<getTimeFromTIMELOG("temp-time")<<endl; 
        logout<<*random_i<<" "<<count<<" "<<getTimeFromTIMELOG("temp-time")<<endl; 
    } 
  
}
