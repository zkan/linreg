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

        prediction = self.dot_product(X, theta)
        error = prediction - y
        J = (1.0 / 2.0) * error * error

        return J
