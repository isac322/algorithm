#pragma once

/*
0부터 n까지 숫자를 나열했을때 총 등장하는 t(0~9)의 개수를 반환.
https://www.acmicpc.net/problem/11170
*/
int solve(int n, int t) {
	if (n < 0) return 0;
	int cnt = t == 0 ? 1 : 0, prev = 1;
	for (int i = 10; i <= n; i *= 10) {
		if (n % i / prev == t) cnt += ((n - i) / i) * prev + 1 + n % prev;
		else cnt += (n / i)*prev;
		prev = i;
	}
	return cnt;
}