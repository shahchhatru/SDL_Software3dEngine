#ifndef OBJREADER_H
#define OBJREADER_H
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<array>
using namespace std;

class ObjReader {
    fstream newfile;
public:
    vector<vector<int>> faces;
    vector<array<float,4>> vvertices;
    void read(char* filename) {
        newfile.open(filename, ios::in);
        while (newfile.is_open()) {
            string tp;
            vector<string> newvs;
            vector<float> newvf;
            while (getline(newfile, tp)) {
                if (tp[0] == 'v' && tp[1] == ' ') {
                    int n = tp.length();
                    tp = tp.substr(2, n);
                    // cout<<tp;
                     //cout<<endl;
                    newvs = split_string(tp, ' ');
                    //display_string_vector(newvs);
                    newvf = convert_to_float(newvs);
                    newvf.push_back(1.0);
                    array<float, 4> arr;
                    for (int i = 0; i < 4; i++) {
                        arr[i] = newvf[i];
                    }
                    if (newvf.size() != 0) {
                        vvertices.push_back(arr);
                    }

                }


            }

            newfile.close();
        }

    }


    void readfaces(char* filename) {
        newfile.open(filename, ios::in);
        while (newfile.is_open()) {
            string tp;
            vector<string> newvs;
            vector<int> newvf;
            while (getline(newfile, tp)) {
                if (tp[0] == 'f' && tp[1] == ' ') {
                    int n = tp.length();
                    tp = tp.substr(2, n);

                    newvs = split_string(tp, ' ');
                    //display_string_vector(newvs);
                    newvs = refine_vector_for_face(newvs);
                    // display_string_vector(newvs);
                    newvf = convert_to_int_disp(newvs, 1);
                    //display_float_vector(newvf);
                    if (newvf.size() != 0) {
                        faces.push_back(newvf);
                    }

                }


            }

            newfile.close();
        }

    }


    void display_string_vector(vector<string> v)
    {
        int s = v.size();
        for (int i = 0; i < s; i++) {
            cout << v[i] << "   ";
        }
        cout << endl;
    }

    void display_float_vector(vector<float> v)
    {
        int s = v.size();
        for (int i = 0; i < s; i++) {
            cout << v[i] << endl;
        }
    }
    vector<float> convert_to_float(vector<string> v) {
        int s = v.size();
        vector<float> vf;
        float num;
        for (int i = 0; i < s; i++) {
            string st = v[i];
            num = std::stof(st);
            vf.push_back(num);
        }
        return vf;
    }

    vector<string> split_string(string& st, char a) {
        vector<string> vs;
        string s = "";
        int i = 0;
        for (i = 0; i < st.size(); i++) {

            if (st[i] != a) {
                s += st[i];
            }
            else {
                vs.push_back(s);
                s = "";
            }
            if (i == st.size() - 1) {
                vs.push_back(s);
            }
        }
        return vs;

    }

    vector<string> refine_vector_for_face(vector<string>& a) {
        vector<string> sample1;
        int siz = a.size();
        for (int i = 0; i < siz; i++) {
            vector<string> s = split_string(a[i], '/');
            //display_string_vector(s);
            //cout<<endl<<endl;
            sample1.push_back(s[0]);
        }
        return sample1;
    }

    vector<int> convert_to_int_disp(vector<string>v, int displacement) {
        int s = v.size();
        vector<int> vf;
        int num;
        for (int i = 0; i < s; i++) {
            string st = v[i];
            num = std::stoi(st) - displacement;
            vf.push_back(num);
        }
        return vf;
    }


    static void display_float_vector(vector<float>& v)
    {
        int s = v.size();
        for (int i = 0; i < s; i++) {
            cout << v[i] << endl;
        }
    }
    static void display_float_vector(vector<int>& v)
    {
        int s = v.size();
        for (int i = 0; i < s; i++) {
            cout << v[i] << endl;
        }
    }


    static void display_vertices(vector<vector<float>>& a) {
        int s1 = a.size();
        for (int i = 0; i < s1; i++) {
            int s2 = a[i].size();
            for (int j = 0; j < s2; j++) {
                cout << a[i][j] << "   ";//"\""<<i<<"\""<<"\""<<j<<"\""
            }
            cout << endl;
        }

    }
    static void display_vertices(vector<vector<float>>& a,int s) {
        int s1 = s;
        for (int i = 0; i < s1; i++) {
            int s2 = a[i].size();
            for (int j = 0; j < s2; j++) {
                cout << a[i][j] << "   ";//"\""<<i<<"\""<<"\""<<j<<"\""
            }
            cout << endl;
        }

    }


    static void display_vertices(vector<vector<int>>& a) {
        int s1 = 100;
        for (int i = 0; i < s1; i++) {
            int s2 = a[i].size();
            for (int j = 0; j < s2; j++) {
                cout << a[i][j] << "   ";//"\""<<i<<"\""<<"\""<<j<<"\""
            }
            cout << endl;
        }

    }

    static void display_vertices(vector<array<float, 4>>& a) {
        int s1 = a.size();
        for (int i = 0; i < s1; i++) {

            for (int j = 0; j < 4; j++) {
                cout << a[i][j] << "   ";
            }
            cout << endl;
        }

    }

    static void display_vertices(vector<array<float, 4>>& a,int s) {
        int s1 = s;
        for (int i = 0; i < s1; i++) {

            for (int j = 0; j < 4; j++) {
                cout << a[i][j] << "   ";
            }
            cout << endl;
        }

    }



};


#endif