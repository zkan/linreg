class LinearRegression:
    def dot_product(self, a, b):
        result = 0

        for each in xrange(len(a)):
            result += a[each] * b[each]

        return result
