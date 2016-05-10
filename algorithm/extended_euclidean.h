#pragma once
#include <algorithm>

/*
확장 유클리드 알고리즘
m*a + n*b = gcd(a, b)를 만족하는 m, n을 구함

[ri : 나머지, qi : 몫]
r1 = a - b*q1
r2 = b - r1*q2
r3 = r1 - r2*q3
r4 = r2 - r3*q4
....
rK = gcd(a, b) = r(K - 2) - r(K - 1)*qK
의 유클리드 호제법식 중
gcd(a, b)의 r(K - 2)와 r(K - 1)가 r1, r2로 풀어질 수 있음을 이용해서
식을 푼 후, a, b의 계수, 즉 m, n을 찾는다.
*/
namespace ExtendedEuclid {
	int m, n;

	/*
	반환값은 gcd(a, b)
	m, n에 값이 저장됨
	*/
	int extended_euclid(int a, int b) {
		if (a < b) std::swap(a, b);

		int ppR = a%b;
		if (!ppR) {
			m = -1;
			n = a / b + 1;
			return b;
		}
		int pR = b%ppR;
		int ppM = 1, ppN = -a / b;
		int pM = -ppM*(b / ppR), pN = 1 - ppN*(b / ppR);

		while (pR) {
			const auto &v = std::div(ppR, pR);
			ppM -= pM*v.quot;
			std::swap(pM, ppM);
			ppN -= pN*v.quot;
			std::swap(pN, ppN);
			ppR = v.rem;
			std::swap(pR, ppR);
		}

		m = ppM;
		n = ppN;

		return ppR;
	}
}