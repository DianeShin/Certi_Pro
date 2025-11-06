#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

int N;
int Firstchild[201], Secondchild[201], Num[201];
char Oper[201];

int inorder(int idx) {
	if (idx == 0) return 1;

	bool isOperator = (Oper[idx] == '+' || Oper[idx] == '-' || Oper[idx] == '*' || Oper[idx] == '/');
	bool hasChild = (Firstchild[idx] != 0 || Secondchild[idx] != 0);

	// operator with no child
	if (isOperator && !hasChild)
		return 0;

	// number but has child
	if (!isOperator && hasChild)
		return 0;

	// recurrsion
	int left = inorder(Firstchild[idx]);
	int right = inorder(Secondchild[idx]);

	return left && right;
}


int main(int argc, char** argv)
{
	int test_case;

	/*
	   10개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for (test_case = 1; test_case <= 10; ++test_case)
	{
		int i;
		memset(Firstchild, 0, sizeof(int) * 201);
		memset(Secondchild, 0, sizeof(int) * 201);
		memset(Num, 0, sizeof(int) * 201);
		memset(Oper, 0, sizeof(char) * 201);

		/*
			 각 테스트 케이스를 표준 입력에서 읽어옵니다.
			 정점의 개수는 N에 저장됩니다.

			 각 정점 번호 i에 대해서 해당하는 정보가 다음 배열 i번째 index에 저장됩니다.
			 해당 정점이 자식을 갖는 경우, 연산자면 Oper[i]에 해당 연산자가 저장되며,
			 숫자일 경우, Num[i]에 해당 연산자가 저장된다.
			 Firstchild[i], Secondchild[i]에 각각 자식 정점의 번호가 저장됩니다.
			 해당 정점이 단말일 경우 해당 위치의 Firstchild,Secondchild의 값은 보장되지 않습니다.
		 */
		cin >> N;
		for (i = 0; i < N; i++)
		{
			int addr;
			char buf[200];

			cin >> addr;
			cin >> buf;

			if (strcmp(buf, "+") == 0 || strcmp(buf, "-") == 0 || strcmp(buf, "/") == 0 || strcmp(buf, "*") == 0)
				Oper[addr] = buf[0];
			else
				Num[addr] = atoi(buf);

			if (addr * 2 <= N)
			{
				cin >> Firstchild[addr];
				if (addr * 2 + 1 <= N)
					cin >> Secondchild[addr];
			}
		}

		cout << "#" << test_case << " ";

		/////////////////////////////////////////////////////////////////////////////////////////////
		cout << inorder(1) << endl;
		 /////////////////////////////////////////////////////////////////////////////////////////////

	}

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
