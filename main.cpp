#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <list>
#include <iterator>
#include <algorithm>
#include <functional>
#include <cstdlib>
#include <chrono>

#include "Factory.h"
#include "FactoryBox.h"
#include "FactoryTetra.h"
#include "FactorySphere.h"
#include "Figure.h"
#include "Sphere.h"
#include "Box.h"
#include "Tetra.h"
#include "Ray.h"
#include "RGB.h"
#include "functions.h"
//#include "CImg.h"

//using namespace cimg_library;
using namespace std;
int main()
{
    std::cout << "Hello World!\n";
	/*CImg<unsigned char> img(640, 400, 1, 3);
	img.fill(0);
	unsigned char purple[] = { 255,0,255 };
	img.draw_text(100, 100, "Hello World", purple);
	img.display("My first CImg code");*/
	/*int i=0;
	std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    //#pragma omp parallel for private(i)

	for (i = 0; i < 5; ++i) {
		std::cout << i;
	}
	std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
	int elapsed_ms = static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
	std::cout << "Addition operator runtime is " << elapsed_ms << " ms\n";*/

    try {
        //READ THE PARAMETERS 
        const string inputData = "inputData.txt";
        ifstream inputO(inputData.c_str(), ios_base::in);
        if (!inputO.is_open()) {
            cerr << "Error! Cannot open file " + inputData << endl;
            return 1;
        }
        map< string, Factory* > factoryMap;
        factoryMap["sphere"] = (new FactorySphere);
        factoryMap["box"] = (new FactoryBox);
        factoryMap["tetra"] = (new FactoryTetra);
        //double Camera[3] = {0, 0, 0}, Normal[3] = { 0, 0, 0 }, Up[3] = { 0, 0, 0 }, Screen_dist = 0, Limit = 0;
        //double  Angle_of_view = 0, Width = 0, Height = 0, Light[3] = { 0, 0, 0 };

        map < string, vector<double> > parameters;
        map < string, int > screen_size; // Width and Height

        string str;
        while (getline(inputO, str)) {
            // get words
            //list<string> words;
            cout << str << endl;
            istringstream ist(str);
            string ValueType;
            double curEl;
            int curVal;
            ist >> ValueType;
            if((ValueType == "height") || (ValueType == "width")){
                ist >> curVal;
                screen_size[ValueType] = curVal;
                continue;
            }
            vector <double> CurVect;
            while (ist >> curEl)
                CurVect.push_back(curEl);
            Check_lenParam(ValueType, CurVect.size());
            Normalize(ValueType, CurVect);
            parameters[ValueType] = CurVect;
        }
        Check_CntParams(&parameters);
        Check_Screen(&screen_size);
        
        inputO.close();

        //READ THE FIGURES
        vector< Figure* > vectFigure;
        const string inputFgr = "in.txt";
        ifstream inputF(inputFgr.c_str(), ios_base::in);
        if (!inputF.is_open()) {
            cerr << "Error! Cannot open file " + inputFgr << endl;
            return 1;
        }
        string line;
        while (getline(inputF, line)) {
            list<string> words;
            //cout << line << endl;
            istringstream ist(line);
            string curType;
            //Figure* curFigure = NULL;
            RGB curColor;
            vector<double> curData;
            vector<int> rgb;
            //unsigned char num;
            int i = 0, num;
            double val;
            //Type of Figure
            ist >> curType;
            //RGB 
            while (ist >> num) {
                rgb.push_back(num);
                i++;
                if (i == 3) break;
            }
            if (i != 3) {
                cerr << "Error! Wrong length of colorData " << endl;
                return 1;
            }
            cout << curType << i << endl;
            curColor = RGB(rgb.at(0), rgb.at(1), rgb.at(2));
            while (ist >> val) {
                curData.push_back(val);
            }
            cout << rgb.at(0)<< rgb.at(1)<< rgb.at(2) <<  endl;
            //cout << "curData.size "<<curData.size() << endl;
            auto curFactory = factoryMap.find(curType);
            if (curFactory == factoryMap.end()) {
                cerr << "Error! Wrong type in file in.txt!" << endl;
                return 1;
            }
            /*cout << "Curdata.size = " << curData.size() << endl;
            for(int i=0; i< curData.size(); i++) cout << curData.at(i)<<" ";
            cout <<  endl;
            for (int i = 0; i < rgb.size(); i++) cout << rgb.at(i) << " ";
            cout << endl;*/
            auto curFigure = curFactory->second->Create(curColor, curData);
            if (curFigure->IsNotInTheArea(curFigure->get_Center(), &parameters)) {
                cout << "Warning! Figure " + curType + " is not in the area" << endl;
                delete curFigure;
                continue;
            }
            vectFigure.push_back(curFigure);
            cout << curFigure->get_Blue() << endl;
            //curFigure = Create_Figure(words);
            if (curFigure)
                curFigure->print();
        }
        //prov(&parameters);
        Ray_tracing(&parameters, &screen_size, &vectFigure);
        vector<double> v, res;
        //float a = 3;
        //cout << 1.0f / a << endl;
        /*v.push_back(3);
        v.push_back(0);
        v.push_back(0);
        v.push_back(1);
        Sphere sp(RGB(0, 0, 0), v);
        sp.print();
        Ray r(Point(0, 0, 0), Point(3, 0, 0)), r2(Point(0, 0, 0), Point(0, 0, 1));
        cout << "dir "<<r.get_dirX()<< r.get_dirY() << r.get_dirZ() << endl;
        cout <<"point"<< r.get_pntX() << r.get_pntY() << r.get_pntZ() << endl;
        if (sp.intersect(&r, res))
            cout << "YEEEEEEEES" << endl;
        else
            cout << "NO" << endl;
        if (sp.intersect(&r2, res))
            cout << "YEEEEEEEES" << endl;
        else
            cout << "NO" << endl;*/
        inputF.close();
        delete factoryMap["tetra"];
        delete factoryMap["box"];
        delete factoryMap["sphere"];
        for (const auto& vect : vectFigure) {
            delete vect;
        }
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }
	return 0;
}





/*list<string> ::iterator it = words.begin(), last = words.end();
            if (it == last) {
                cerr << "Error! Empty data" << endl;
                return 1;
            }
            if (*words.begin() == "sphere")
            {
                cout << "Sp" << endl;
                if (words.size() != 8) {
                    cerr << "Error! Wrong data" << endl;
                    return 1;
                }
                curFigure = new Sphere(atof((*(++it)).c_str()), atof((*(++it)).c_str()), \
                    atof((*(++it)).c_str()), atof((*(++it)).c_str()), \
                    atoi((*(++it)).c_str()), atoi((*(++it)).c_str()), atoi((*(++it)).c_str()));

            }
            else if (*words.begin() == "box")
            {
                cout << "B" << endl;
                if (words.size() != 10) {
                    cerr << "Error! Wrong data" << endl;
                    return 1;
                }
            }
            else if (*words.begin() == "tetra")
            {
                cout << "T" << endl;
                if (words.size() != 16) {
                    cerr << "Error! Wrong data" << endl;
                    return 1;
                }
            }*/
            /*++it;
            arr[i]->Set_fname(*it);
            ++it;
            while(it!=last){
                arr[i]->Set(atof((*it).c_str()));
                ++it;
            }
            i++;*/