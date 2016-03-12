class LinearRegression:
    def dot_product(self, a, b):
        if len(a) != len(b):
            return -1

        result = 0
        for each in xrange(len(a)):
            result += a[each] * b[each]

        return result
