import unittest

from linreg import LinearRegression


class LinearRegressionTest(unittest.TestCase):
    def test_dot_product_for_two_vectors_should_get_dot_product_result(self):
        a = [1, 2, 3]
        b = [4, 5, 6]

        linreg = LinearRegression()
        result = linreg.dot_product(a, b)

        expected = 32
        self.assertEquals(result, expected)


if __name__ == '__main__':
    unittest.main()
