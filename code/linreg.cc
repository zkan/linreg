#include "linreg.h"

LinearRegression::LinearRegression() {
}

LinearRegression::~LinearRegression() {
}

// credit: uvts_cvs's reply at
// http://stackoverflow.com/questions/392981/how-can-i-convert-string-to-double-in-c
double LinearRegression::string_to_double(string str) {
    istringstream i(str);
    double val;
    
    if(!(i >> val)) {
        return 0;
    }

    return val;
}

// credit: heeen's reply at 
// http://stackoverflow.com/questions/599989/is-there-a-built-in-way-to-split-strings-in-c
vector<string> LinearRegression::split(string str, string delimiters) {
    vector<string> tokens;
    
    // skip delimiters at beginning
    string::size_type last_pos = str.find_first_not_of(delimiters, 0);
    // find first "non-delimiter"
    string::size_type pos = str.find_first_of(delimiters, last_pos);

    // insert first column for data X
    tokens.push_back("1");

    // npos is a static member constant value (-1) with the greatest 
    // possible value for an element of type size_t.
    // credit: http://www.cplusplus.com/reference/string/string/npos/
    while(string::npos != pos || string::npos != last_pos) {
        // found a token, add it to the vector
        tokens.push_back(str.substr(last_pos, pos - last_pos));
        // skip delimiters
        last_pos = str.find_first_not_of(delimiters, pos);
        // find next "non-delimiter"
        pos = str.find_first_of(delimiters, last_pos);
    }

    return tokens;
}

void LinearRegression::print_data() {
    for(unsigned int i = 0; i < this->_data.size(); i++) {
        for(unsigned int j = 0; j < this->_data[i].size(); j++) {
            cout << this->_data[i][j] << "|";
        }
        cout << " => " << this->_predicted_data[i] << endl;
    }
}

void LinearRegression::read_data(char* file_data) {
    ifstream ifile;
    ifile.open(file_data);

    vector<string> tokens;
    vector<double> val;
    string line;
    while(!ifile.eof()) {
        getline(ifile, line);
        // skip an empty line
        if(line.empty()) {
            continue;
        }
        
        tokens = split(line, ", ");

        for(unsigned int i = 0; i < tokens.size() - 1; i++) {
            val.push_back(string_to_double(tokens[i]));
        }
        this->_data.push_back(val);

        // last column is the predicted data y
        this->_predicted_data.push_back(string_to_double(tokens[tokens.size() - 1]));

        val.clear();
    }
}

double LinearRegression::dot_product(vector<double> X, vector<double> theta) {
    double sum_product = 0;

    for(unsigned int i = 0; i < X.size(); i++) {
        sum_product += theta[i] * X[i];
    }

    return sum_product;
}

double LinearRegression::compute_cost(vector< vector<double> > X, 
                                      vector<double> y, 
                                      vector<double> theta) {
    double J = 0;
    unsigned int m = y.size();

    vector<double> predictions;
    
    for(unsigned int i = 0; i < theta.size(); i++) {
        double val = dot_product(X[i], theta);
        predictions.push_back(val);
    }

//    cout << predictions.size() << endl;

    vector<double> errors;
    for(unsigned int i = 0; i < predictions.size(); i++) {
        errors.push_back(predictions[i] - y[i]);
    }

    J = (1.0 / (2 * m)) * dot_product(errors, errors);

    return J;
}

void LinearRegression::gradient_descent() {
    // initialize theta
    for(unsigned int i = 0; i < this->_data.size(); i++) {
        this->_theta.push_back(1);
    }

    double J = compute_cost(this->_data, this->_predicted_data, this->_theta);
    cout << "J = " << J << endl;
}



