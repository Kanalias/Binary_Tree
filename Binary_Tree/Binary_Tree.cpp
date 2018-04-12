// Binary_Tree.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <string>
#include <windows.h>

using namespace std;

struct BstNode{
	int data_int;
	char data_ch;
	BstNode *left;
	BstNode *right;
};

BstNode* get_new_node(const int value_int, const char value_ch)
{
	BstNode* new_node = (BstNode*)malloc(sizeof(BstNode));
	new_node->data_int = value_int;
	new_node->data_ch = value_ch;
	new_node->left = new_node->right = nullptr;
	return new_node;
}

BstNode* insert_values(BstNode *root, const int  value_int, const char value_ch) {
	if (root == nullptr)
	{
		root = get_new_node(value_int, value_ch);
	}
	else if(value_int < root->data_int)
	{
		root->left = insert_values(root->left, value_int, value_ch);
	} 
	else if (value_int > root->data_int)
	{
		root->right = insert_values(root->right, value_int, value_ch);
	}
	else
	{
		if(value_ch < root->data_ch)
		{
			root->left = insert_values(root->left, value_int, value_ch);
		} else
		{
			root->right = insert_values(root->right, value_int, value_ch);
		}
	}
	return root;
}

bool search_values(BstNode* root, const int value_int, const char value_ch)
{
	if(root == nullptr)
	{
		return false;
	} 
	else if(root->data_int == value_int && root->data_ch == value_ch)
	{
		return true;
	}
	else if(value_int < root->data_int)
	{
		search_values(root->left, value_int, value_ch);
	}
	else if (value_int > root->data_int)
	{
		search_values(root->right, value_int, value_ch);
	}
	else if (value_int == root->data_int)
	{
		if(value_ch < root->data_ch)
		{
			search_values(root->left, value_int, value_ch);
		} else
		{
			search_values(root->right, value_int, value_ch);
		}
	}
}

BstNode* find_min(BstNode *root)
{
	if (root->left == nullptr)
	{
		return root;
	}
	return find_min(root->left);
}

BstNode* delete_values(BstNode* root, const int value_int, const char value_char)
{
	if(root == nullptr)
	{
		return root;
	}
	else if (value_int < root->data_int)
	{
		root->left = delete_values(root->left, value_int, value_char);
	} 
	else if (value_int > root->data_int)
	{
		root->right = delete_values(root->right, value_int, value_char);
	}
	else
	{
		if(root->left == nullptr && root->right == nullptr) //нет детей
		{
			free(root);
			root = nullptr;
		}
		else if (root->left == nullptr) //1 ребенок
		{
			BstNode *temp = root;
			root = root->right;
			free(temp);
			return root;
		}
		else if (root->right == nullptr) //1 ребенок
		{
			BstNode *temp = root;
			root = root->left;
			free(temp);
			return root;
		}
		else
		{
			BstNode* temp = find_min(root->right);
			root->data_int = temp->data_int;
			root->data_ch = temp->data_ch;
			root->right = delete_values(root->right, temp->data_int, temp->data_ch);
		}
	}
	return root;
}


BstNode* clear_descendant(BstNode* root)
{
	if (root != nullptr)
	{
		clear_descendant(root->left);
		clear_descendant(root->right);
		free(root);
	}
	return root;
}

BstNode* clear_tree(BstNode* root)
{
	root = clear_descendant(root);
	root = nullptr;
	return root;
}

int print_tree(BstNode *root, const char *dir, const int level) {
	if (root != nullptr) {
		printf("lvl %d %s = %d | %c\n", level, dir, root->data_int, root->data_ch);
		print_tree(root->left, "left", level + 1);
		print_tree(root->right, "right", level + 1);
	}
	return 0;
}

int check_correctness_int()
{
	bool check = true;
	int input;
	do
	{
		check = true;
		cout << "Введите число: ";
		cin >> input;
		if (!cin.good())
		{
			cin.ignore(255, '\n');
			check = false;
		}
		cin.clear();
		if (cin.peek() != 32 && cin.peek() != '\n') {
			cin.ignore(255, '\n');
			check = false;
		}
		else cin.ignore(255, '\n');
	} while (!check); 
	cin.clear();
	return input;
}

char check_correctness_char()
{
	cout << "Введите один символ или больше (занесется ТОЛЬКО ПЕРВЫЙ символ): ";
	string input;
	cin.clear();
	cin >> input;
	while (cin.get() != '\n'); //clear
	return input[0];
}

int print_menu_text()
{
	system("cls");
	cout << "Бинарное дерево поиска:\n" <<
		"1. Вставить элементы\n" <<
		"2. Удалить элемент\n" <<
		"3. Вывести элементы дерева\n" <<
		"4. Очистить дерево\n" << endl;
	return 0;
}

int print_menu() {
	BstNode* root = nullptr;
	do {
		auto flag = true, flag_insert = false, flag_delete = false, flag_print = false, flag_clear = false;
		print_menu_text();
		while (flag)
		{
			const char point = _getch();
			switch (point)
			{
			case ('1'):
				flag = false;
				flag_insert = true;
				break;
			case ('2'):
				flag = false;
				flag_delete = true;
				break;
			case ('3'):
				flag = false;
				flag_print = true;
				break;
			case ('4'):
				flag = false;
				flag_clear = true;
			}
		}
		if (flag_insert)
		{
			system("cls");
			const int val_int = check_correctness_int();
			const char val_ch = check_correctness_char();
			root = insert_values(root, val_int, val_ch);
			flag_insert = false;
			system("pause");
		}
		else if (flag_delete)
		{
			system("cls");
			if (root)
			{
				const int val_int = check_correctness_int();
				const char val_ch = check_correctness_char();
				if (search_values(root, val_int, val_ch))
				{
					root = delete_values(root, val_int, val_ch);
				}
				else
				{
					cout << "Элемент не найден" << endl;
				}
			}
			else
			{
				cout << "Дерево не заполнено" << endl;
			}
			flag_delete = false;
			system("pause");
			
		}
		else if (flag_print)
		{
			system("cls");
			if (root)
			{
				print_tree(root, "root", 0);
			}
			else
			{
				cout << "Дерево пустое" << endl;
			}
			system("pause");
			flag_print = false;
		}
		else if (flag_clear)
		{
			system("cls");
			if (root)
			{
				root = clear_tree(root);
				cout << "Дерево удалено" << endl;
			}
			else
			{
				cout << "Дерево не заполнено. Его нельзя удалить" << endl;
			}
			flag_delete = false;
			system("pause");
		}
	} while (true);
	return 0;
}

int main()
{
	SetConsoleCP(1251); // Ввод с консоли в кодировке 1251
	SetConsoleOutputCP(1251);
	print_menu();
    return 0;
}
