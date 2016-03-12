import unittest

from linreg import LinearRegression


class LinearRegressionTest(unittest.TestCase):
    def setUp(self):
        self.linreg = LinearRegression()

    def test_dot_product_of_two_vectors_should_get_dot_product_result(self):
        a = [1, 2, 3]
        b = [4, 5, 6]

        result = self.linreg.dot_product(a, b)

        expected = 32
        self.assertEquals(result, expected)

    def test_dot_product_should_get_negative_if_vectors_have_different_length(
        self
    ):
        a = [1, 2, 3]
        b = [4, 5, 6, 7]

        result = self.linreg.dot_product(a, b)

        expected = -1
        self.assertEquals(result, expected)


if __name__ == '__main__':
    unittest.main()
