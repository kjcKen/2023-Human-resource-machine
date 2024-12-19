#include"function.h"
using namespace std;

int getConsoleHeight() {//�������̨�߶�
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	int Height = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
	return Height;
}
int getConsoleWidth() {//�������̨����
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	int Width = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
	return Width;
}
void setCursorPosition(int x, int y) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hConsole, pos);//һ�����еĺ���
}
void printVerticalLine(int x, int y, int length) {
	setCursorPosition(x, y);
	for (int i = 0; i < length; i++)
	{
		cout << "|";
		setCursorPosition(x, y + i + 1);
	}
}
void printsquare(int x, int y, int a) {
	setCursorPosition(x, y); cout << "+---+" << endl;
	setCursorPosition(x, y + 1);
	if (a != 1024)cout << "|" << setw(3) << a << "|" << endl;
	if (a == 1024)cout << "|" << "   " << "|" << endl;
	setCursorPosition(x, y + 2); cout << "+---+" << endl;
}
void printRobot(int x, int y, int a) {
	setCursorPosition(x, y);
	printsquare(x, y, a);
	setCursorPosition(x, y + 3); cout << "@   @" << endl;
	setCursorPosition(x, y + 4); cout << "-----" << endl;
	setCursorPosition(x, y + 5); cout << "|@ @|" << endl;
	setCursorPosition(x, y + 6); cout << "  +  " << endl;
	setCursorPosition(x, y + 7); cout << "/   \\" << endl;
	setCursorPosition(x, y + 8); cout << " | | " << endl;
}
void leveln(int a[], int b[], int c[], int d[], int m1, int m2, int m3) {
	setCursorPosition(0, 2);
	cout << "IN" << endl;
	for (int i = 0; i < m1; i = i + 1)
		printsquare(0, 3 * i + 3, a[i]);
	setCursorPosition(wid * 2 / 3 - 5, 2);
	cout << "OUT" << endl;
	for (int i = 0; i < m2; i = i + 1)
		printsquare(wid * 2 / 3 - 5, 3 * i + 3, b[i]);
	for (int k = 0; k < m3; k = k + 1)
	{
		printsquare(wid / 3 - 4 * numc + 8 * k, 15, c[k]);
		setCursorPosition(wid / 3 - 4 * numc + 2 + 8 * k, 18); cout << k;
	}
	setCursorPosition(28, 20);
	cout << "Goal:";
	for (int i = 0; i < m2; i++) {
		if (i != m2 - 1)cout << d[i] << ",";
		else cout << d[i];
	}
	setCursorPosition(wid * 5 / 6 - 6, 2);
	cout << "Instructions";
	printVerticalLine(wid * 2 / 3, 2, hei - 1);
}
void clearRobot(int x, int y) {
	for (int k = y; k <= y + 8; k = k + 1) {
		setCursorPosition(x, k); cout << "     " << endl;
	}
}
void moveRobot(int x, int y, int z, int w, int a, int b) {
	int pos = x;
	while (pos != z) {
		clearRobot(pos, y);
		printRobot(pos + (z - x) / abs(z - x), w, a);
		pos = pos + (z - x) / abs(z - x);
		this_thread::sleep_for(chrono::milliseconds(10));
	}
	printRobot(z, w, b);
}

void inbox(int pos, int a[], int p) {
	moveRobot(pos, 5, 8, 5, r, a[0]);
	r = a[0];
	for (int i = 0; i <= p - 2; i = i + 1)
	{
		a[i] = a[i + 1];
	}
	a[p - 1] = 1024;
}
void outbox(int pos, int b[], int cnt) {
	if (r != 1024)
	{
		moveRobot(pos, 5, getConsoleWidth() * 2 / 3 - 13, 5, r, 1024);
		b[cnt] = r;
	}
}
void copyto(int c[], int x, int pos) {
	if (r != 1024 && x >= 0 && x <= numc - 1)
	{
		moveRobot(pos, 5, wid / 3 - 4 * numc + 8 * x, 5, r, r);
		c[x] = r;
		printsquare(wid / 3 - 4 * numc + 8 * x, 15, c[x]);
	}
}
void copyfrom(int c[], int x, int pos) {
	if (c[x] != 1024 && x <= numc - 1 && x >= 0)
	{
		moveRobot(pos, 5, wid / 3 - 4 * numc + 8 * x, 5, r, c[x]);
		r = c[x];
		printsquare(wid / 3 - 4 * numc + 8 * x, 15, c[x]);
	}
}
void add(int c[], int x, int pos) {
	if (c[x] != 1024 && r != 1024 && x <= numc - 1 && x >= 0)
	{
		moveRobot(pos, 5, wid / 3 - 4 * numc + 8 * x, 5, r, r + c[x]);
		r = r + c[x];
	}
}
void sub(int c[], int x, int pos) {
	if (c[x] != 1024 && r != 1024 && x <= numc - 1 && x >= 0)
	{
		moveRobot(pos, 5, wid / 3 - 4 * numc + 8 * x, 5, r, r - c[x]);
		r = r - c[x];
	}
}
bool pass(int b[], int d[], int p) {
	bool ans = true;
	if (b[p - 1] != 1024)
	{
		for (int k = 0; k <= p - 1; k = k + 1)
		{
			if (b[k] != d[k]) ans = false;
		}
	}
	else ans = false;
	return ans;
}

vector<Level> load() {//���ļ����عؿ�״̬
	vector<Level> levels0;
	ifstream fin("levels.txt");
	if (fin) {
		int number;
		bool passed;
		while (fin >> number >> passed) {
			Level leveltemp;
			leveltemp.number = number;
			leveltemp.passed = passed;
			levels0.push_back(leveltemp);
		}
		fin.close();
		setCursorPosition(0, 0); cout << "�ؿ�״̬���سɹ���" << endl;
	}
	else {
		setCursorPosition(0, 0); cout << "�޷����عؿ�״̬��" << endl;
	}
	return levels0;
}
void chooselevel(int num) {//ѡ��ؿ� 
	for (int i = 0; i < num; i++) {
		setCursorPosition(0, i + 1);
		cout << "�ؿ�" << levels[i].number;
		if (levels[i].passed) cout << " - ��ͨ��";
		else cout << " - δͨ��";
		cout << endl;
	}
}
bool checklevel(int selected, int num) {
	if (selected != 0 && selected != 1024 && selected != 999) {
		if (selected > num) return 0;//�����˹ؿ���
		for (int i = 0; i < selected - 1; i++) {//ǰ�ùؿ�û��ͨ��
			if (!levels[i].passed) return 0;
		}
	}
	return 1;
}
void save(vector<Level>& levels) {//����һ����������������ٸ��Ƶ��˷� 
	ofstream fout("levels.txt");
	if (fout) {
		for (int i = 0; i < levels.size(); i++) {//����levels�е�ÿ��Ԫ�� 
			fout << levels[i].number << " " << levels[i].passed << endl;
		}
		fout.close();
		cout << "�ؿ�״̬����ɹ�!" << endl;
	}
	else {
		cout << "�޷�����ؿ�״̬!" << endl;
	}
}//����ؿ�״̬���ļ�
void renew(vector<Level>& levels) {
	ofstream fout("levels.txt");
	if (fout) {
		for (int i = 0; i < levels.size(); i++) {//����levels�е�ÿ��Ԫ�� 
			levels[i].passed = 0;
			fout << levels[i].number << " " << levels[i].passed << endl;
		}
		fout.close();
		cout << "�ؿ�״̬���óɹ�!" << endl;
	}
	else {
		cout << "�ؿ�״̬����ʧ��!" << endl;
	}
}
void clearPart(int x, int y) {
	for (int i = 0; i <= y - 1; i = i + 1)
		for (int j = 0; j <= x - 1; j = j + 1) {
			setCursorPosition(j, i); cout << ' ';
		}
}
void clearScreen() {
	for (int i = 0; i <= getConsoleHeight() + 2; i = i + 1)
		for (int j = 0; j <= getConsoleWidth(); j = j + 1)
		{
			setCursorPosition(j, i); cout << ' ';
		}
}
bool checkInstruction(int n, string s) {
	if (n == 1) {
		if (s == "inbox" || s == "outbox") return 1;
		else return 0;
	}
	if (n == 2) {
		if (s == "inbox" || s == "outbox" || s == "copyto" || s == "copyfrom" || s == "add" || s == "sub" || s == "jump" || s == "jumpifzero")return 1;
		else return 0;
	}
	if (n == 3) {
		if (s == "inbox" || s == "outbox" || s == "copyto" || s == "copyfrom" || s == "add" || s == "sub") return 1;
		else return 0;
	}
}
bool parameter(string s) {
	if (s == "copyto" || s == "copyfrom" || s == "add" || s == "sub" || s == "jump" || s == "jumpifzero")return 1;
	else return 0;
}
bool integral(string s, int start) {
	bool ans = true;
	for (int i = start; i <= s.length() - 1; i++) {
		if (int(s[i]) < 48 || int(s[i]) > 57)ans = false;
	}
	return ans;
}
bool space(string s, int start) {
	bool ans = false;
	for (int i = start; i <= s.length() - 1; i++) {
		if (int(s[i]) == 32)ans = true;
	}
	return ans;
}
void inputInstruction(string instruction[]) {
	setCursorPosition(0, 6);
	cout << "��ѡ���ȡָ��ķ�ʽ����1���������� 2���ļ�����" << endl;
	int ans1;
	cin >> ans1;
	while (ans1 != 1 && ans1 != 2) {
		cout << "��Чѡ����ѡ���ȡָ��ķ�ʽ����1���������� 2���ļ�����" << endl;
		cin >> ans1;
	}
	if (ans1 == 1) {
		cout << "������ָ����" << endl;
		cin >> m;
		string s;
		cout << "������" << m << "��ָ��" << endl;
		cin.ignore();//�����������з� 
		for (int i = 0; i <= m - 1; i++) {
			string s;
			cin >> s;
			instruction[i] = s;
			if (parameter(s)) {
				getline(cin, input[i]);
				if (!space(input[i], 1) && integral(input[i], 1)) {
					int suma = 0; v[i] = 1;
					for (int j = 1; j <= input[i].length() - 1; j++) {
						suma = suma + (int(input[i][j]) - 48) * pow(10, input[i].length() - 1 - j);
					}
					x[i] = suma;
				}
				else v[i] = 0;
			}
			else v[i] = 1;
		}
	}
	if (ans1 == 2) {
		cout << "�������ļ�·��" << endl;
		string path;
		cin >> path;
		ifstream fin(path.c_str());//ת��ΪC�����ַ��� 
		while (!fin) {//����޷��� 
			cout << "�����ڶ�Ӧ���ļ�" << endl;
			cin >> path;
			fin.open(path.c_str());
		}
		fin >> m;
		for (int i = 0; i <= m - 1; i++) {
			string s;
			fin >> s;
			instruction[i] = s;
			if (parameter(s)) {
				getline(fin, input[i]);
				if (!space(input[i], 1) && integral(input[i], 1)) {
					int suma = 0; v[i] = 1;
					for (int j = 1; j <= input[i].length() - 1; j++) {
						suma = suma + (int(input[i][j]) - 48) * pow(10, input[i].length() - 1 - j);
					}
					x[i] = suma;
				}
				else v[i] = 0;
			}
			else v[i] = 1;
		}
		fin.close();
	}
}
void printInstruction(string instruction[])
{
	for (int i = 0; i <= m - 1; i = i + 1)
	{
		setCursorPosition(getConsoleWidth() * 2 / 3 + 2, i + 3);
		cout << i + 1 << ' ' << instruction[i];
		if (parameter(instruction[i]))
			cout << input[i];
	}
}
void printRequest(int a[], int d[], int n, int p, int q, int space, string inst)
{
	setCursorPosition(0, 0); cout << "��" << n << "�أ�" << endl;
	cout << "�ṩ���֣�"; for (int i = 0; i <= p - 1; i = i + 1)cout << a[i] << ' ';
	cout << endl << "Ŀ�꣺"; for (int i = 0; i <= q - 1; i = i + 1)cout << d[i] << ' ';
	cout << endl << "����ָ���" << inst; cout << endl << "���ÿյ�����" << space;
}
void currentinstruction(int n) {
	setCursorPosition(getConsoleWidth() * 2 / 3 + 1, n + 3);
	cout << ">";
}
void clearcurrent(int n) {
	setCursorPosition(getConsoleWidth() * 2 / 3 + 1, n + 3);
	cout << " ";
}
bool checkInstruction2(string s, string inst[], int len) {
	bool ans = false;
	for (int i = 0; i <= len - 1; i++) {
		if (inst[i] == s)ans = true;
	}
	return ans;
}