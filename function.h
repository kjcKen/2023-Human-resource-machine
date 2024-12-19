#ifndef HEADER_FILE_NAME_H  // ���δ����HEADER_FILE_NAME_H�꣬��ִ������Ĵ���
#define HEADER_FILE_NAME_H  // ����HEADER_FILE_NAME_H��
#pragma once
#include<iostream>
#include<cmath>
#include<string>
#include<iomanip>
#include<cstdlib>
#include<windows.h>
#include<vector>
#include<fstream>
#include<thread>
#include<chrono>
#include<sstream>
using namespace std;

struct Level {
	int number;
	bool passed;
};//�ؿ��ṹ�壬�����ؿ���ź��Ƿ�ͨ����״̬
extern string instruction[1000], input[1000],inst1[10];//��¼ָ��
extern int m, x[1000], v[1000], r, total, hei, wid;//m��ʾָ��������x��¼ָ�����
extern int numa, numb, numc, numi;
extern vector<Level> levels; //���عؿ�״̬

int getConsoleHeight();//�������̨�ĸ߶�
int getConsoleWidth();//�������̨�Ŀ��� 
void setCursorPosition(int x, int y);//�ƶ����
void printVerticalLine(int x, int y, int length);//��ӡ���� 
void printsquare(int x, int y, int a);//��ӡ�յ� 
void printRobot(int x, int y, int a);//��ӡ������
void leveln(int a[], int b[], int c[], int d[], int m1, int m2, int m3);//�ؿ�������ʾ
void clearRobot(int x, int y);//��������� 
void moveRobot(int x, int y, int z, int w, int a, int b);//�ƶ������� 
void clearPart(int x, int y);//���һ���� 
void clearScreen();
//�����ǹؿ���ʾ�����õ��ĺ��� 

void inbox(int pos, int a[], int p);
void outbox(int pos, int b[], int cnt);
void copyto(int c[], int x, int pos);
void copyfrom(int c[], int x, int pos);
void add(int c[], int x, int pos);
void sub(int c[], int x, int pos);
bool pass(int b[], int d[], int p);
//����������ָ���Ӧ�ĺ����Լ��жϺ���

void chooselevel(int num);
bool checklevel(int selected,int num);
vector<Level> load();
void save(vector<Level>& levels);//����ؿ�״̬
void renew(vector<Level>& levels);//���ùؿ�״̬

//������ѡ��ؿ������õ��ĺ��� 

bool checkInstruction(int n, string s);
bool parameter(string s);
void inputInstruction(string instruction[]);//ʵ�ֶ���ָ�� 
void printInstruction(string instruction[]);//��ʾָ�� 
void printRequest(int a[], int d[], int n, int p, int q, int space, string inst);
void currentinstruction(int n);
bool checkInstructionn(string s, string inst);
void clearcurrent(int n);//�����ǰָ���ָʾ
bool checklevel2(string s, string inst[], int len);
bool checkInstruction2(string s, string inst[], int len);
//��������ָ���йصĺ��� 

bool integral(string s, int start);
bool space(string s, int start);
#endif
