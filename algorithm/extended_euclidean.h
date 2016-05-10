#pragma once
#include <algorithm>

/*
Ȯ�� ��Ŭ���� �˰���
m*a + n*b = gcd(a, b)�� �����ϴ� m, n�� ����

[ri : ������, qi : ��]
r1 = a - b*q1
r2 = b - r1*q2
r3 = r1 - r2*q3
r4 = r2 - r3*q4
....
rK = gcd(a, b) = r(K - 2) - r(K - 1)*qK
�� ��Ŭ���� ȣ������ ��
gcd(a, b)�� r(K - 2)�� r(K - 1)�� r1, r2�� Ǯ���� �� ������ �̿��ؼ�
���� Ǭ ��, a, b�� ���, �� m, n�� ã�´�.
*/
namespace ExtendedEuclid {
	int m, n;

	/*
	��ȯ���� gcd(a, b)
	m, n�� ���� �����
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