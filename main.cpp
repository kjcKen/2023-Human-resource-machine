#include"function.h"
using namespace std;
string instruction[1000], input[1000],inst1[10];//记录指令
int m, x[1000], v[1000], r=1024, total=0, hei = getConsoleHeight(), wid = getConsoleWidth();;//m表示指令条数，x记录指令参数
int numa, numb, numc, numi;
vector<Level> levels;
int main() {
	while (true)
	{
		numa = 0; numb = 0; numc = 0; numi = 0;
		levels = load();
		int cntk = levels.size(), cntj = cntk + 1;
		chooselevel(cntk);
		cout << "请选择关卡：";
		for (int i = 1; i <= cntk; i++) {
			if (i != cntk) cout << i << '/';
			else cout << i;
		}
		cout << "或输入0自定义关卡" << endl;
		cout << "输入1024清除自定义关卡数据，输入999重置通关状态。\n";
		int ans0;
		cin >> ans0;//输入以选择关卡 
		while (!checklevel(ans0, cntk)) {
			cout << "当前选择不合理，请重新选择" << endl;
			cin >> ans0;
		}
		if (ans0 == 999) {
			renew(levels); clearScreen(); chooselevel(cntk);
		}
		if (ans0 == 0) {
			clearPart(50, cntk + 5); setCursorPosition(0, 0);
			string stra;
			stringstream ss0; ss0 << "level" << cntk + 1 << "data" << ".txt"; stra = ss0.str();
			ofstream file(stra.c_str());
			int m1, m2, m3, m4;//m1表示输入的积木数，m2表示输出的积木数，m3表示空地数，m4表示指令数
			if (!file) {
				cout << "关卡文件打开失败" << endl;
			}
			cout << "请输入输入序列的积木个数" << endl;
			cin >> m1;
			file << m1 << endl;
			cout << "请输入" << m1 << "个积木的数字" << endl;
			for (int i = 1; i <= m1; i++) {
				int temp;
				cin >> temp;
				file << temp << " ";
			}
			file << endl;
			cout << "请输入输出序列的积木个数" << endl;
			cin >> m2;
			file << m2 << endl;
			cout << "请输入" << m2 << "个积木的数字" << endl;
			for (int i = 1; i <= m2; i++) {
				int temp;
				cin >> temp;
				file << temp << " ";
			}
			file << endl;
			cout << "请输入可用的空地数（最多8个）" << endl;
			cin >> m3;
			while (m3 < 0 || m3 >= 9) {
				cout << "空地数目过多！\n"; cin >> m3;
			}
			file << m3 << endl;
			cout << "请输入可用的指令数" << endl;
			cin >> m4;
			file << m4 << endl;
			cout << "请输入" << m4 << "个可用的指令" << endl;
			for (int i = 1; i <= m4; i++) {
				string temp;
				cin >> temp;
				while (!checkInstruction(2, temp)) {
					cout << "输入的指令不在指令集中，请重新输入" << endl;
					cin >> temp;
				}
				if (i != m4) {
					file << temp << " "; inst1[i] = temp;
				}
				else file << temp;
			}
			file << endl;
			file.close();
			Level temp;
			temp.number = cntk + 1;
			temp.passed = 0;
			levels.push_back(temp);
			save(levels);
			cout << "是否完成？（1：完成/其他：退出）" << endl;
			char finishset; cin >> finishset;
			if (finishset == '1') {
				clearScreen(); chooselevel(cntk + 1);
			}
			else return 0;
		}
		if (ans0 != 0 && ans0 != 1024 && ans0 != 999) {
			for (int i = 0; i <= 999; i++) v[i] = 1;
			cout << "现在进入关卡" << ans0 << endl;
			this_thread::sleep_for(chrono::milliseconds(300));
			clearScreen();
			total = 0; r = 1024;
			int pos = 28, cnt = 0;
			string ffile;
			stringstream ss; ss << "level" << ans0 << "data" << ".txt"; ffile = ss.str();
			ifstream fin(ffile.c_str());
			int a[100], b[100], c[100], d[100];
			string instadd[8];
			fin >> numa;
			for (int i = 0; i <= numa - 1; i++)fin >> a[i];
			fin >> numb;
			for (int i = 0; i <= numb - 1; i++)fin >> d[i]; for (int i = 0; i <= numb - 1; i++)b[i] = 1024;
			fin >> numc; for (int i = 0; i <= numc - 1; i++)c[i] = 1024;
			fin >> numi; for (int i = 0; i <= numi - 1; i++)fin >> instadd[i];
			fin.close();
			string inst2 = instadd[0];
			for (int i = 1; i <= numi - 1; i++) inst2 = inst2 + "," + instadd[i];
			printRequest(a, d, ans0, numa, numb, numc, inst2);
			inputInstruction(instruction);
			clearScreen(); leveln(a, b, c, d, numa, numb, numc);
			printInstruction(instruction);
			printRobot(28, 5, 1024);
			this_thread::sleep_for(chrono::milliseconds(500));
			for (int i = 0; i <= m - 1; i = i + 1)
			{
				currentinstruction(i);
				if (!checkInstruction2(instruction[i], instadd, numi) || v[i] == 0) {
					setCursorPosition(getConsoleWidth() - 24, i + 3); cout << "Error on instruction " << i + 1;
					break;
				}
				if (instruction[i] == "inbox")
				{
					inbox(pos, a, numa);
					pos = 8;
					leveln(a, b, c, d, numa, numb, numc); total++;
					this_thread::sleep_for(chrono::milliseconds(500));
				}
				if (instruction[i] == "outbox")
				{
					if (r != 1024) {
						outbox(pos, b, cnt);
						pos = getConsoleWidth() * 2 / 3 - 13;
						r = 1024;
						if (b[cnt] != 1024)cnt = cnt + 1; total++;
					}
					else {
						setCursorPosition(getConsoleWidth() - 24, i + 3); cout << "Error on instruction " << i + 1; break;
					}
					leveln(a, b, c, d, numa, numb, numc);
					this_thread::sleep_for(chrono::milliseconds(500));
				}
				if (instruction[i] == "copyto")
				{
					if (r != 1024 && x[i] >= 0 && x[i] <= numc - 1) {
						copyto(c, x[i], pos); pos = wid / 3 - 4 * numc + 8 * x[i]; total++;
					}
					else {
						setCursorPosition(getConsoleWidth() - 24, i + 3); cout << "Error on instruction " << i + 1; break;
					}
					this_thread::sleep_for(chrono::milliseconds(500));
				}
				if (instruction[i] == "copyfrom")
				{
					if (c[x[i]] != 1024 && x[i] >= 0 && x[i] <= numc - 1) {
						copyfrom(c, x[i], pos); pos = wid / 3 - 4 * numc + 8 * x[i]; total++;
					}
					else {
						setCursorPosition(getConsoleWidth() - 24, i + 3); cout << "Error on instruction " << i + 1; break;
					}
					this_thread::sleep_for(chrono::milliseconds(500));
				}
				if (instruction[i] == "add")
				{
					if (c[x[i]] != 1024 && r != 1024 && x[i] <= numc - 1 && x[i] >= 0) {
						add(c, x[i], pos);
						pos = wid / 3 - 4 * numc + 8 * x[i]; total++;
					}
					else {
						setCursorPosition(getConsoleWidth() - 24, i + 3); cout << "Error on instruction " << i + 1; break;
					}
					this_thread::sleep_for(chrono::milliseconds(500));
				}
				if (instruction[i] == "sub")
				{
					if (c[x[i]] != 1024 && r != 1024 && x[i] <= numc - 1 && x[i] >= 0) {
						sub(c, x[i], pos);
						pos = wid / 3 - 4 * numc + 8 * x[i]; total++;
					}
					else {
						setCursorPosition(getConsoleWidth() - 24, i + 3); cout << "Error on instruction " << i + 1; break;
					}
					this_thread::sleep_for(chrono::milliseconds(500));
				}
				clearcurrent(i);
				if (instruction[i] == "jump") {
					if (x[i] <= m && x[i] > 0) { i = x[i] - 2; total++; }
					else {
						setCursorPosition(getConsoleWidth() - 24, i + 3); cout << "Error on instruction " << i + 1;
						break;
					}
				}
				if (instruction[i] == "jumpifzero") {
					if (r != 1024 && x[i] <= m && x[i] > 0) {
						if (r == 0)i = x[i] - 2;
						else continue;
						total++;
					}
					else {
						setCursorPosition(getConsoleWidth() - 24, i + 3); cout << "Error on instruction " << i + 1;
						break;
					}
				}
				if ((instruction[i + 1] == "inbox" && a[0] == 1024 && r == 1024) || i == m - 1)
				{
					if (pass(b, d, numb))
					{
						setCursorPosition(0, getConsoleHeight() - 2); cout << "Success.The number of instruction performed is " << total << "." << endl;
						levels[ans0 - 1].passed = true;//在通关后标记为通过 
						save(levels);//保存关卡状态
						break;
					}
					else {
						setCursorPosition(0, getConsoleHeight() - 2); cout << "Fail.The number of instruction performed is " << total << "." << endl; break;
					}
				}
				clearcurrent(i);
			}
			printVerticalLine(getConsoleWidth() * 2 / 3, 2, getConsoleHeight() - 1);
			char back;
			setCursorPosition(0, getConsoleHeight() - 1);
			cout << "是否继续？（按1回到选关界面，按2重置通关状态，按其他键结束）\n";
			cin >> back;
			if (back == '2') renew(levels);
			if (back != '1' && back != '2') break;
			else clearScreen();
		}
		if (ans0 == 1024) {
			setCursorPosition(0, cntk + 4);
			for (int i = 5; i <= cntk; i++) {
				string filename, filen;
				stringstream ss1; ss1 << "level" << i << "data" << ".txt"; filename = ss1.str();
				stringstream ss2; ss2 << "level" << i << ".txt"; filen = ss2.str();
				remove(filename.c_str()); remove(filen.c_str());
			}
			ifstream fin("levels.txt");
			ofstream fout("temp.txt");
			string line1;
			for (int i = 1; i <= 4; i++) {
				getline(fin, line1);
				fout << line1 << endl;
			}
			fin.close(); fout.close();
			remove("levels.txt");
			rename("temp.txt", "levels.txt");
			cout << "是否继续？（1：初始化选关界面/其他：退出）\n";
			char outgame; cin >> outgame;
			if (outgame == '1') { clearScreen(); chooselevel(4); }
			else return 0;
		}
	}
	return 0;
}
