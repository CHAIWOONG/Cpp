#include <iostream>
#include <algorithm>
#include <foward_list> 
#include <list>
#include <deque>
#include <stack>
#include <queue>

using namespace std;

int main()
{	
	// --------------------------------------------------------------------sort()--------------------------------------------------------------------------
	// 기본은 오름차순 정렬
	// sort(st, en, cmp = less<>{})의 인자로 구현
	// ----------------------list, stack, queue와 같이 v.begin() + i 등의 연산이 불가능한 container는 std::sort를 사용할 수 없다
	
	vector<int> v = { 3, 1, 4, 1, 5, 9, 2 };
	int w[5] = { 1, 2, 3, 4, 5 };
	string s = "hello";

	sort(v.begin(), v.end());     // v.begin은 시작원소, v.end()는 마지막 원소 다음 가리킴
				      // sort(v.begin(), v.begin()+7) 도 가능
	//sort(v.rbegin(), v.rend()); // reverse iterator를 사용하여 ++해도 감소하므로 내림 차순으로 정렬
	
	sort(w, w + 5, greater<>{}); // a > b를 리턴하는 greater<> functor를 이용하여 내림 차순으로 정렬
				     // arr는 배열 이름(시작원소 포인터), a+(배열크기)
	sort(s.begin(), s.end());  // string 타입에서의 정렬

	for (auto& i : v) cout << i << ' '; cout << '\n'; // 1 1 2 3 4 5 9
	for (auto& i : w) cout << i << ' '; cout << '\n'; // 5 4 3 2 1
	cout << s << '\n'; // ehllo
	
	// -------------------------------------------비교함수 cmp를 사용하여 정렬하는 경우--------------------------------------------------------------------
	bool cmp(int a, int b){
		if(a%5 != b%5) return a%5 < b%5;
		return a < b;                           
	}
							// int 형을 5로 나눈 나머지 순으로, 나머지가 같으면 크기순으로 정렬
							// a가 b의 앞에 오면 true, 그렇지 않으면 false 반환
							// 일반적으로 a=b의 경우는 false로 판단하도록 함수를 구현해야 런타임 에러가 발생하지 않는다.
	
	int a[7] = {1,2,3,4,5,6,7};
	sort(a, a+7, cmp);
	
	// 비교함수의 인자로 STL 혹은 클래스 객체를 전달할 시에, 값이 변경되지 않는다면 reference로 전달 (ex: const string& a)
	
	// ------------------------------------------------------stable_sort-------------------------------------------------------------------------------------
	// sort는 불안정 정렬, (3, a), (3, b)의 순서가 (3, b), (3, a)가 될 수도 있다
	// stable_sort를 통해서 정렬되지 않는 원소끼리의 [초기 순서]를 유지할 수 있도록 한다 (std::sort보다는 느리게 작동)
	
	vector<pair<int,int>> v{ { 3, 'a' }, { 3, 'b' }, { 1, 'c' }, { 2, 'd' } }, w = v;
	stable_sort(v.begin(), v.end(), [](const pair<int,int>& a, const pair<int,int>& b) { return a.first < b.first; });  // lambda 함수 식
	
	for (auto& [a, b] : v) cout << a << b << ' '; cout << '\n'; 		// 1c 2d 3a 3b
	
	// -------------------------------------------------------partial_sort-------------------------------------------------------------------------------------
	// partial_sort(st, mid, en)
	// [st, en) 범위의 원소들을 부분적으로 정렬해서 [st, mid) 범위에 올바른 값이 들어가도록 한다
	
	vector<int> v{ 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
	partial_sort(v.begin(), v.begin() + 5, v.end());
	for (auto& i : v) cout << i << ' '; cout << '\n'; // 1 1 2 3 3 ? ...
	
	// ------------------------------------------------------nth_element-------------------------------------------------------------------------------------
	// 평균 시간복잡도 O(n)에 k번째 원소를 구하는 함수
	// nth_element(st, mid, en)
	// [st, en) 범위의 원소들을 정렬했을 때 v[mid]에 위치할 원소를 v[mid]에 오도록 하고, 
	// [1, mid) 범위의 i에 대해 v[i] <= v[mid]를, (mid, n - 1] 범위의 i에 대해 v[mid] <= v[i]를 만족하도록 v 배열을 이분
	// (이때 [1, mid), (mid, n - 1] 범위의 원소들은 v[mid]에 대해 구분되어있을 뿐이며 정렬이 되어있진 않다)
	
	vector<int> v{ 3, 1, 4, 1, 5, 9, 2 };
	nth_element(v.begin(), v.begin() + 3, v.end()); // [1, 1, 2] [3] [4, 5, 9]
	cout << v[3] << '\n';
	for (auto& i : v) cout << i << ' '; cout << '\n';
	
	// ----------------------------------------------------------is_sorted-------------------------------------------------------------------------------------
	// 배열이 정렬된 상태인지 확인 (bool 타입 return)
	
	vector<int> v{ 3, 1, 4, 1, 5, 9, 2 };
	vector<int> w{ 1, 2, 3, 3, 4, 5, 5 };
	cout << is_sorted(v.begin(), v.end()) << '\n'; // 0
	cout << is_sorted(w.begin(), w.end()) << '\n'; // 1
	
	return 0;
	
}
