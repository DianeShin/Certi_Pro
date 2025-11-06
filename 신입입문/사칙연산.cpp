#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

int N;
int Number[1001], Firstchild[1001], Secondchild[1001];
char Operator[1001];
int Answer;

int inorder(int idx) {
	bool isOperator = (Operator[idx] == '+' || Operator[idx] == '-' || Operator[idx] == '*' || Operator[idx] == '/');
	bool hasChild = (Firstchild[idx] != 0 || Secondchild[idx] != 0);
	
	if (!hasChild) return Number[idx];
	if (isOperator) {
		// recurrsion
		int left = inorder(Firstchild[idx]);
		int right = inorder(Secondchild[idx]);
		if (Operator[idx] == '+') return left + right;
		if (Operator[idx] == '-') return left - right;
		if (Operator[idx] == '*') return left * right;
		if (Operator[idx] == '/') return left / right;
	}
}

int main(int argc, char** argv)
{
	int test_case;
	/*
	   아래의 freopen 함수는 input.txt 를 read only 형식으로 연 후,
	   앞으로 표준 입력(키보드) 대신 input.txt 파일로부터 읽어오겠다는 의미의 코드입니다.
	   여러분이 작성한 코드를 테스트 할 때, 편의를 위해서 input.txt에 입력을 저장한 후,
	   freopen 함수를 이용하면 이후 cin 을 수행할 때 표준 입력 대신 파일로부터 입력을 받아올 수 있습니다.
	   따라서 테스트를 수행할 때에는 아래 주석을 지우고 이 함수를 사용하셔도 좋습니다.
	   freopen 함수를 사용하기 위해서는 #include <cstdio>, 혹은 #include <stdio.h> 가 필요합니다.
	   단, 채점을 위해 코드를 제출하실 때에는 반드시 freopen 함수를 지우거나 주석 처리 하셔야 합니다.
	*/
	//freopen("system_input.txt", "r", stdin);

	/*
	   10개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for (test_case = 1; test_case <= 10; ++test_case)
	{
		int i;
		memset(Firstchild, 0, sizeof(int) * 1001);
		memset(Secondchild, 0, sizeof(int) * 1001);
		memset(Number, 0, sizeof(int) * 1001);
		memset(Operator, 0, sizeof(char) * 1001);

		/*
			 각 테스트 케이스를 표준 입력에서 읽어옵니다.
			 정점의 개수는 N에 저장됩니다.

			 각 정점 번호 i에 대해서 해당하는 정보가 다음 배열 i번째 index에 저장됩니다.
			 해당 정점이 연산자를 갖는 경우, Operator[i]에 해당 연산자가 저장되며 Firstchild[i], Secondchild[i]에 각각 자식 정점의 번호가 저장됩니다.
			 해당 정점이 단순 숫자일 경우, Number[i]에 해당 양의 정수가 저장됩니다.
			 단순 숫자일 경우 해당 위치의 Operator,Firstchild,Secondchild의 값은 보장되지 않습니다.
			 사칙연산의 경우 해당 위치의 Number의 값은 보장되지 않습니다.
		 */
		cin >> N;
		for (i = 0; i < N; i++)
		{
			int addr;
			char buf[100];

			cin >> addr;
			cin >> buf;
			if ((buf[0] == '+') || (buf[0] == '-') || (buf[0] == '*') || (buf[0] == '/'))
			{
				Operator[addr] = buf[0];
				cin >> Firstchild[addr] >> Secondchild[addr];
			}
			else Number[addr] = atoi(buf);
		}


		/////////////////////////////////////////////////////////////////////////////////////////////
		Answer = inorder(1);
		 /////////////////////////////////////////////////////////////////////////////////////////////

		// 표준출력(화면)으로 답안을 출력합니다.
		cout << "#" << test_case;
		cout << " " << Answer << endl;;
	}

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
