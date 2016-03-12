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

    def test_run_gradient_descent_with_one_iteration_should_change_theta(self):
        X = [[1, 2], [3, 4]]
        y = [2, 2.5]
        theta = [0, 0]
        number_of_iterations = 1

        result = self.linreg.run_gradient_descent(X, y, theta, number_of_iterations)

        expected = (
            2.6572999999999993,
            [0.07, 0.16]
        )
        self.assertEquals(result, expected)

    def test_run_gradient_descent_with_ten_iteration_should_change_theta(self):
        X = [[1, 2], [3, 4]]
        y = [2, 2.5]
        theta = [0, 0]
        number_of_iterations = 10

        result = self.linreg.run_gradient_descent(X, y, theta, number_of_iterations)

        expected = (
            0.2953245352067722,
            [0.21850056185143937, 0.5469413946894416]
        )
        self.assertEquals(result, expected)


if __name__ == '__main__':
    unittest.main()
