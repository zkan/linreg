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
