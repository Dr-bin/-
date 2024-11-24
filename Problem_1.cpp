#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cctype>
using namespace std;
string trim_Punc( string& word)    //�ú�������ȥ�������ļ��еı����ź������ַ���ת���ɿո�
{
	string trimmed;
	for (char ch : word)    //����ÿһ���ַ�
	{
		if (isalpha(ch))    //����ĸ�Ļ�
		{ 
			trimmed += ch;
		}
		else
		{
			trimmed += " ";
		}
	}
	return trimmed;
}
int count_num(string& file_name)
{
	ifstream file(file_name);    //���ļ�
	if (!file.is_open())    //������ʾ������
	{
		cerr << "��Ч���ļ�����" << file_name << endl;
		return -1;
	}
	int num = 0;    //num������¼����
	string word,line;
	while (getline(file, line))    //���д���
	{
		stringstream str_s(line);
		while (str_s >> word)    //����ÿһ������
		{
			word = trim_Punc(word);
			if (word == "that"||word=="That") 
			{
				num++;
			}
		}
	}
	file.close();    //�ر��ļ���
	return num;
}
int main()
{
	string file_name;
	cout << "�������ļ�����";
	cin >> file_name;
	int num = count_num(file_name);
	if (num != -1)
		cout << "�ļ�" << file_name << "��that/That��������" << num << "��" << endl;
	return 0;
}
