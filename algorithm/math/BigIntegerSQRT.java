import java.math.BigInteger;

/**
 * Heron's method (https://en.wikipedia.org/wiki/Heron%27s_method)
 * fast big integer square root function.
 *
 * source : http://stackoverflow.com/a/11962756
 */
public class BigIntegerSQRT {
	public static BigInteger bigIntSqRootFloor(BigInteger x) throws IllegalArgumentException {
		if (x.compareTo(BigInteger.ZERO) < 0) {
			throw new IllegalArgumentException("Negative argument.");
		}

		// square roots of 0 and 1 are trivial and
		// y == 0 will cause a divide-by-zero exception
		if (x.equals(BigInteger.ZERO) || x.equals(BigInteger.ONE)) {
			return x;
		}

		BigInteger two = BigInteger.valueOf(2L);
		// starting with y = x / 2 avoids magnitude issues with x squared
		BigInteger y = x.divide(two);
		while (y.compareTo(x.divide(y)) > 0) {
			y = ((x.divide(y)).add(y)).divide(two);
		}
		return y;
	}
}
