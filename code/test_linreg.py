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

    def test_compute_cost_for_single_example_should_return_cost(self):
        X = [[1, 2]]
        y = [2]
        theta = [0.1, 0.2]

        result = self.linreg.compute_cost(X, y, theta)

        expected = 1.125
        self.assertEquals(result, expected)

    def test_compute_cost_for_entire_examples_should_return_cost(self):
        X = [[1, 2], [3, 4]]
        y = [2, 2.5]
        theta = [0.1, 0.2]

        result = self.linreg.compute_cost(X, y, theta)

        expected = 2.105
        self.assertEquals(result, expected)


if __name__ == '__main__':
    unittest.main()
