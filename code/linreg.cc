#include "linreg.h"

LinearRegression::LinearRegression() {
}

LinearRegression::~LinearRegression() {
}

void LinearRegression::read_data(char* file_data) {
    ifstream ifile;
    ifile.open(file_data);

    string line;
    while(!ifile.eof()) {
        getline(ifile, line);
        cout << line;
    }
}
