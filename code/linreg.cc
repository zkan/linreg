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

void LinearRegression::read_training_data(char* file_data) {
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
        
        // split the data into tokens and add 1 to the first column
        tokens = split(line, ", ");
        // first to second last column are data X
        for(unsigned int i = 0; i < tokens.size() - 1; i++) {
            val.push_back(string_to_double(tokens[i]));
        }
        this->_data.push_back(val);

        // last column is the predicted data y
        this->_predicted_data.push_back(string_to_double(tokens[tokens.size() - 1]));

        val.clear();
    }
}

double LinearRegression::dot_product(vector<double> a, vector<double> b) {
    double sum_product = 0;

    for(unsigned int i = 0; i < a.size(); i++) {
        sum_product += a[i] * b[i];
    }

    return sum_product;
}

void LinearRegression::feature_normalize() {
    // initialize the mean and std vectors
    for(unsigned int i = 0; i < this->_data[0].size(); i++) {
        this->_mean.push_back(0);
        this->_std.push_back(0);
    }

    // compute mean and std (both have same vector size)
    unsigned int N = this->_data.size();
    for(unsigned int i = 0; i < this->_data.size(); i++) {
        for(unsigned int j = 0; j < this->_data[i].size(); j++) {
            this->_mean[j] += this->_data[i][j];
            this->_std[j] += this->_data[i][j] * this->_data[i][j];
        }
    }
    for(unsigned int i = 0; i < this->_mean.size(); i++) {
        this->_mean[i] = this->_mean[i] / N;
        this->_std[i] = sqrt((this->_std[i] / N) - (this->_mean[i] * this->_mean[i]));
    }

    for(unsigned int i = 0; i < this->_data.size(); i++) {
        // normalize all except the first column (the first column is used for theta_0)
        for(unsigned int j = 1; j < this->_data[i].size(); j++) {
            this->_data[i][j] = (this->_data[i][j] - this->_mean[j]) / this->_std[j];
        }
    }

}

double LinearRegression::compute_cost(vector< vector<double> > X, 
                                      vector<double> y, 
                                      vector<double> theta) {
    double J = 0;
    unsigned int m = y.size();

    vector<double> predictions;
    for(unsigned int i = 0; i < X.size(); i++) {
        double val = dot_product(X[i], theta);
        predictions.push_back(val);
    }

    vector<double> errors;
    for(unsigned int i = 0; i < predictions.size(); i++) {
        double diff = predictions[i] - y[i];
        errors.push_back(diff);
    }

    J = (1.0 / (2 * m)) * dot_product(errors, errors);

    return J;
}

void LinearRegression::gradient_descent(double alpha, int num_iters, bool norm) {
    vector<double> J_history;
    unsigned int m = this->_predicted_data.size();

    // normalize the data
    if(norm) {
        feature_normalize();
    }

    // initialize theta
    for(unsigned int i = 0; i < this->_data[0].size(); i++) {
        this->_theta.push_back(0);
    }

    double J = 0;
    for(int iter = 0; iter < num_iters; iter++) {
        cout << "Iter " << iter + 1 << ": ";

        // predict first
        vector<double> predictions;
        for(unsigned int i = 0; i < this->_data.size(); i++) {
            double val = dot_product(this->_data[i], this->_theta);
            predictions.push_back(val);
        }

        // then compute the error and update the theta
        double error = 0;
        for(unsigned int i = 0; i < this->_theta.size(); i++) {
            vector<double> diff;
            vector<double> X_col;
            for(unsigned int j = 0; j < this->_data.size(); j++) {
                diff.push_back(predictions[j] - this->_predicted_data[j]);
                X_col.push_back(this->_data[j][i]);
            }
            error = dot_product(diff, X_col);

            // update the theta
            this->_theta[i] = this->_theta[i] - (alpha * (1.0 / m) * error);
        }
        
        J = compute_cost(this->_data, this->_predicted_data, this->_theta);
        cout << J << endl;
        J_history.push_back(J);
    }
    cout << endl;
}

void LinearRegression::print_theta() {
    cout << "Theta:" << endl;
    for(unsigned int i = 0; i < this->_theta.size(); i++) {
        cout << this->_theta[i] << endl;
    }
    cout << endl;
}

vector<double> LinearRegression::get_theta() {
    return this->_theta;
}

vector<double> LinearRegression::get_mean() {
    return this->_mean;
}

vector<double> LinearRegression::get_std() {
    return this->_std;
}

