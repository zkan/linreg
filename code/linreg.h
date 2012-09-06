/*
    Linear Regression with one or multiple variables
    Author: Kan Ouivirach
    Credit: David C. Swaim II, Ph.D.
*/
#ifndef _LINREG_H_
#define _LINREG_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class LinearRegression {
    public:
        LinearRegression();
        ~LinearRegression();

        void read_data(char* file_data);
        void print_data();

        void gradient_descent();

    private:
        vector< vector<double> > _data;
        vector<double> _predicted_data;
        vector<double> _theta;
        
        double string_to_double(string str);
        vector<string> split(string str, string delimiters);

        vector<double> dot_product(vector< vector<double> > X, vector<double> theta);
        double compute_cost(vector< vector<double> > X, vector<double> y, vector<double> theta);
};

#endif
// end of linreg.h

