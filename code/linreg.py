class LinearRegression:
    def dot_product(self, a, b):
        if len(a) != len(b):
            return -1

        result = 0
        for each in xrange(len(a)):
            result += a[each] * b[each]

        return result

    def compute_cost(self, X, y, theta):
        J = 0
        predictions = []

        for each in X:
            predictions.append(self.dot_product(each, theta))

        errors = []
        for index, each in enumerate(predictions):
            errors.append(each - y[index])

        J = (1.0 / 2.0) * self.dot_product(errors, errors)

        return J

    def run_gradient_descent(self, X, y, theta, number_of_iterations):
        alpha = 0.01

        for each_iteration in xrange(number_of_iterations):
            predictions = []
            for each_example in X:
                predictions.append(self.dot_product(each_example, theta))

            for t_index, each_theta in enumerate(theta):
                diff = []
                X_col = []
                for p_index, each_prediction in enumerate(predictions):
                    diff.append(each_prediction - y[p_index])
                    X_col.append(X[t_index][p_index])

                error = self.dot_product(diff, X_col)
                result = each_theta - (alpha * error)
                theta[t_index] = result

            J = self.compute_cost(X, y, theta)

        return (J, theta)
