#ifndef MATRIXTRANSFORMATION_H
#define  MATRIXTRANSFORMATION_H
#include<iostream>
#include<vector>
#include<array>
#include<cmath>

class matrixTransformation {
public:
    static std::vector<std::array<float, 4>> matrixMultiply_nx4(std::vector<std::array<float, 4>> a, std::array<std::array<float, 4>, 4> b) {
        std::vector<std::array<float, 4>> mult;
        int size_a = a.size();
        mult.reserve(size_a);
        //initialize our vector mult;
        for (int m = 0; m < size_a; m++) {
            std::array<float, 4> ar2 = { {0,0,0,0} };
            mult.push_back(ar2);
        }
        int i, j, k;
        int r1 = size_a, c2 = 4, c1 = 4;
        // Multiplying matrix a and b and storing in array mult.
        for (i = 0; i < r1; ++i) {
            for (j = 0; j < c2; ++j) {
                float sum = 0.0f;
                for (k = 0; k < c1; ++k)
                {
                    sum += a[i][k] * b[k][j];
                }
                mult[i][j] = sum;
            }
        }
        return mult;
    }



	static void matrixMultiply_nx4(std::vector<std::array<float, 4>>& a, std::vector<std::array<float, 4>>& b, std::vector<std::array<float, 4>>& mult) {
		int size_a = a.size();
        int i, j, k;
        int r1 = size_a, c2 = 4, c1 = 4;
        // Multiplying matrix a and b and storing in array mult.
        for (i = 0; i < r1; ++i) {
            for (j = 0; j < c2; ++j) {
                float sum = 0.0f;
                for (k = 0; k < c1; ++k)
                {
                    sum += a[i][k] * b[k][j];
                }
                mult[i][j] = sum;
            }
        }
        // Displaying the multiplication of two matrix.
       

	}
   
    static void matrixMultiply_nx4(std::vector<std::array<float, 4>>& a, std::array<std::array<float, 4>,4>& b, std::vector<std::array<float, 4>>& mult) {
        int size_a = a.size();
        int i, j, k;
        int r1 = size_a, c2 = 4, c1 = 4;
        // Multiplying matrix a and b and storing in array mult.
        for (i = 0; i < r1; ++i) {
            for (j = 0; j < c2; ++j) {

                float sum = 0.0f;
                for (k = 0; k < c1; ++k)
                {
                    sum += a[i][k] * b[k][j];
                }
                mult[i][j] = sum;
            }
        }
        // Displaying the multiplication of two matrix.
       

    }

    static void matrixMultiply_4x4(std::array<std::array<float, 4>,4>& a, std::array<std::array<float, 4>, 4>& b, std::array<std::array<float, 4>,4>& mult) {
        
        int i, j, k;
        int r1 = 4, c2 = 4, c1 = 4;
        // Multiplying matrix a and b and storing in array mult
        printf("matrixMultiply4x4 called \n");
        for (i = 0; i < r1; ++i) {
            for (j = 0; j < c2; ++j) {
                float sum = 0.0f;
                for (k = 0; k < c1; ++k)
                {
                    sum += a[i][k] * b[k][j];
                }
                printf("%f", sum);
                mult[i][j] = sum;
            }
            printf("\n");
        }

    }


    static void get_translation_matrix(std::array<std::array<float, 4>,4> & trans,float tx=0,float ty=0,float tz=0) {
        std::array<std::array<float, 4>, 4> a{ {
            {{1, 0, 0, 0}},
            {{0, 1, 0, 0}},
            {{ 0, 0, 1, 0}},
            {{tx, ty, tz, 1}}
    } };
        trans = a;

    }

    static void display(std::array<std::array<float, 4>, 4>& trans) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                std::cout << trans[i][j] <<"   ";
            }
                std::cout <<std::endl;
        }
    }

    static void display(std::vector<std::array<float, 4>>& trans) {
        int a = trans.size();
        for (int i = 0; i <a ; i++) {
            for (int j = 0; j < 4; j++) {
                std::cout << trans[i][j] << "   ";
            }
            std::cout << std::endl;
        }
    }

    static void display(std::vector<std::vector<float>>& trans) {
        int a = trans.size();
        for (int i = 0; i < a; i++) {
            int b = trans[i].size();
            for (int j = 0; j < b; j++) {
                std::cout << trans[i][j] << "   ";
            }
            std::cout << std::endl;
        }
    }

    static void get_rotation_x(std::array<std::array<float, 4>, 4>& trans,float angle) {
        //float a = angle * (float) (3.14/180); //for degree
       float a = angle; //for radian
        std::array<std::array<float, 4>, 4> arr{ {
            {{1, 0, 0, 0}},
            {{0,cos(a),sin(a),0}},
            {{0,-1*sin(a),cos(a),0}},
            {{0,0,0,1}},
    } };
        trans = arr;

    }
    static void get_rotation_z(std::array<std::array<float, 4>, 4>& trans, float angle) {
        //float a = angle * (float)(3.14 / 180);
        float a = angle;
        std::array<std::array<float, 4>, 4> arr{ {
            {{cos(a),sin(a),0,0}},
            {{-sin(a),cos(a),0,0}},
            {{0,0,1,0}},
            {{0,0,0,1}},
    } };
        trans = arr;

    }
    
    static void get_rotation_y(std::array<std::array<float, 4>, 4>& trans, float angle) {
        //float a = angle * (float)(3.14 / 180);
        float a = angle;
        std::array<std::array<float, 4>, 4> arr{ {
            {{cos(a),0,-sin(a),0}},
            {{0,1,0,0}},
            {{sin(a),0,cos(a),0}},
            {{0,0,0,1}},
    } };
        trans = arr;

    }
    static void scale(std::array<std::array<float, 4>, 4>& trans, float sx, float sy, float sz) {
        std::array<std::array<float, 4>, 4> arr{ {
           {{sx,0,0,0}},
           {{0,sy,0,0}},
           {{0,0,sz,0}},
           {{0,0,0,1}},
   } };
        trans = arr;
    }

    static void scale(std::array<std::array<float, 4>, 4>& trans, float s=1) {
        scale(trans, s, s, s);
    }

    static void scalar_multiply(std::array<float, 4>& ar, float k) {
        for (int i = 0; i < 4; i++) {
            float s = ar[i]*k;
            ar[i] = s;
        }
    }
    static void scalar_divide(std::array<float, 4>& ar, float k) {
        for (int i = 0; i < 4; i++) {
            float s = ar[i]/k;
            ar[i] = s;
        }
    }

    static std::array<float, 4> multiply1x4(std::array<float, 4>& a, std::array<std::array<float, 4>, 4>& b) {
        std::array<float, 4> ans = { {0,0,0,1} };
        for (int j = 0; j < 4; j++) {
            float sum = 0.0f;
            for (int k = 0; k < 4; k++) {
                sum += ((a[k]) * (b[k][j]));
            }
            ans[j] = sum;
        }

        return ans;
    }

    static void normalize_vector(std::array<float, 4>& a) {
        float w = a[3];
        scalar_divide(a, w);

    }
    static void vec_subtract(std::array<float, 4>& a, std::array<float, 4>& b) {
        for (int i = 0; i < 4; i++) {
            a[i] = a[i] - b[i];
        }
    }
    static void normalize2dvec(std::vector<std::array<float, 4>>& a) {
        int k = a.size();
        for (int i = 0; i < k; i++) {
            float w = a[i][3];
            float nx = a[i][0] / w;
            float ny = a[i][1] / w;
            float nz = a[i][2] / w;
            float nw = a[i][3] / w;
            a[i][0] = nx;
            a[i][1] = ny;
            a[i][2] = nz;
            a[i][3] = nw;
        }
    }

    static void vec_add(std::array<float, 4>& a, std::array<float, 4>& b) {
        for (int i = 0; i < 4; i++) {
            a[i] = a[i] + b[i];
        }
    }

};



#endif 