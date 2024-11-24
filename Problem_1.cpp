#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cctype>
using namespace std;
string trim_Punc( string& word)    //该函数用来去除所读文件中的标点符号和其他字符（转换成空格）
{
	string trimmed;
	for (char ch : word)    //遍历每一个字符
	{
		if (isalpha(ch))    //是字母的话
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
	ifstream file(file_name);    //打开文件
	if (!file.is_open())    //错误提示并返回
	{
		cerr << "无效的文件名：" << file_name << endl;
		return -1;
	}
	int num = 0;    //num用来记录次数
	string word,line;
	while (getline(file, line))    //分行处理
	{
		stringstream str_s(line);
		while (str_s >> word)    //遍历每一个单词
		{
			word = trim_Punc(word);
			if (word == "that"||word=="That") 
			{
				num++;
			}
		}
	}
	file.close();    //关闭文件！
	return num;
}
int main()
{
	string file_name;
	cout << "请输入文件名：";
	cin >> file_name;
	int num = count_num(file_name);
	if (num != -1)
		cout << "文件" << file_name << "中that/That共出现了" << num << "次" << endl;
	return 0;
}
