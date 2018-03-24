// Binary_Tree.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <clocale>
#include <string>

using namespace std;

struct Tree{
	int data_int;
	char data_ch;
	struct Tree *parent;
	struct Tree *left;
	struct Tree *right;
};

Tree* get_memory_tree(Tree *parent, const int value_int, const char value_ch)
{
	Tree* buf = (Tree*)malloc(sizeof(Tree));
	buf->left = buf->right = nullptr;
	buf->data_int = value_int; 
	buf->data_ch = value_ch;
	buf->parent = parent;
	return buf;
}

int insert_tree(Tree **head, const int  value_int, const char value_ch){
	Tree *buf = nullptr;
	Tree *ins_val = nullptr;
	if (*head == nullptr){
		*head = get_memory_tree(nullptr, value_int, value_ch);
		return 0;
	}
	buf = *head;
	while (buf) {
		if (value_int < buf->data_int || value_ch < buf->data_ch) {
			if (buf->left) {
				buf = buf->left;
				continue;
			}
			else {
				buf->left = get_memory_tree(buf, value_int, value_ch);
				return 0;
			}
		}
		else if (value_int > buf->data_int || value_ch > buf->data_ch ) {
			if (buf->right) {
				buf = buf->right;
				continue;
			}
			else {
				buf->right = get_memory_tree(buf, value_int, value_ch);
				return 0;
			}
		}
		else {
			exit(2);
		}
	}
	return 0;
}

Tree* get_by_value(Tree *serch, const int value_int, const char value_ch){
	while(serch)
	{
			if (serch->data_int > value_int && serch->data_ch > value_ch )
			{
				serch = serch->left;
				continue;
			}
			else if (serch->data_int < value_int && serch->data_ch < value_ch)
			{
				serch = serch->right;
				continue;
			}
			else
			{
				return serch;
			}
	}
	return nullptr;
}

Tree* get_max_node(Tree *root) {
	while (root->right) {
		root = root->right;
	}
	return root;
}

int remove_node_by_ptr_int(Tree *target) {
	if (target->left && target->right) {
		Tree *local_max = get_max_node(target->left);
		target->data_int = local_max->data_int;
		target->data_ch = local_max->data_ch;
		remove_node_by_ptr_int(local_max);
		return 0;
	}
	else if (target->left) {
		if (target == target->parent->left) {
			target->parent->left = target->left;
		}
		else {
			target->parent->right = target->left;
		}
	}
	else if (target->right) {
		if (target == target->parent->right) {
			target->parent->right = target->right;
		}
		else {
			target->parent->left = target->right;
		}
	}
	else {
		if (target == target->parent->left) {
			target->parent->left = nullptr;
		}
		else {
			target->parent->right = nullptr;
		}
	}
	free(target);
	return 0;
}

int delete_value(Tree *root, const int value_int, const char value_ch) {
	Tree *target = get_by_value(root, value_int, value_ch);
	if(target != nullptr)
	{
		remove_node_by_ptr_int(target);
		cout << "Элемент удален" << endl;
	}
	else
	{
		cout << "Такого элемента нет" << endl;
	}
	return 0;
}

int clear_descendant(Tree *&root)
{
	if (root != nullptr)
	{
		clear_descendant(root->left);
		clear_descendant(root->right);
		free(root);
	}
	return 0;
}

int clear_tree(Tree* &root)
{
	clear_descendant(root);
	root = nullptr;
	return 0;
}

int print_tree(Tree *root, const char *dir, const int level) {
	if (root != nullptr) {
		printf("lvl %d %s = %d | %c\n", level, dir, root->data_int, root->data_ch);
		if(root-> left != nullptr)
		{
			print_tree(root->left, "left", level + 1);
		}
		if(root->right != nullptr)
		{
			print_tree(root->right, "right", level + 1);
		}
	} else
	{
		cout << "Дерево пустое" << endl;
	}
	return 0;
}

int check_correctness_int()
{
	auto n = 0;
	cout << "Введите целолое число от (-1000; 1000](целое число): ";
	string input;
	do {
		cin.clear();
		cin >> input;
		for (auto i : input)
		{
			if (isalpha(i))
			{
				n = -1001;
				break;
			}
			else
			{
				n = atoi(input.c_str());
			}
		}
		if (n < -999 || n > 1000)
		{
			cout << "Введите целолое число от (-1000; 1000](целое число): ";
		}
		while (cin.get() != '\n'); //clear
	} while (n < -999 || n > 1000);
	return n;
}

char check_correctness_char()
{
	cout << "Введите один символ: ";
	string input;
	do {
		cin.clear();
		cin >> input;
		if (input.length() != 1)
		{
			cout << "Введите один символ: ";
		}
		else {
			return input[0];
		}
		while (cin.get() != '\n'); //clear
	} while (input.length() != 1);
	return 0;
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
	Tree *root = nullptr;
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
			insert_tree(&root, val_int, val_ch);
			flag_insert = false;
			system("pause");
		}
		else if (flag_delete)
		{
			system("cls");
			const int val_int = check_correctness_int();
			const char val_ch = check_correctness_char();
			delete_value(root, val_int, val_ch);
			flag_delete = false;
			system("pause");
			
		}
		else if (flag_print)
		{
			system("cls");
			print_tree(root, "root", 0);
			system("pause");
			flag_print = false;
		}
		else if (flag_clear)
		{
			clear_tree(root);
			system("cls");
			cout << "Дерево удалено" << endl;
			flag_delete = false;
			system("pause");
		}
	} while (true);
	return 0;
}

int main()
{
	setlocale(LC_ALL, "");
	print_menu();
    return 0;
}
