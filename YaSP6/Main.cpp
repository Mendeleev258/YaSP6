#include <iostream>
#include <fstream>
#include <chrono>
#include "Windows.h"
#include "IOlib.h"

import Manuscript;
import Library;
import Temple;
import TempleList;


constexpr const char* SOURCE_MENU_TEXT = "\n1. ��������� ������ �� �����\n"
										"2. ��������� ������ �� �������\n"
										"3. ���������� � �������� �������\n"
										"4. �����\n";

constexpr const char* MAIN_MENU_TEXT = "\n1. ����������� �� �����\n"
										"2. ��������� � ����\n"
										"3. �������� ����\n"
										"4. ������� ���� �� ��������\n"
										"5. ����� ���� �� �������� (�����������)\n"
										"6. ������������� ����\n"
										"7. ����������� ��������\n"
										"8. ����� ��� �������� ����������\n"
										"9. �����\n";

constexpr const char* TEMPLE_MENU_TEXT = "\n1. �������� �������� �����\n"
											"2. ������� ������\n"
											"3. �������� ��������\n"
											"4. ������� ��������\n"
											"5. �������� ��������\n"
											"6. ������� ���������\n"
											"7. �����\n";


void read_from_file(TempleList& temples);
void read_from_console(TempleList& temples);

void show_manuscript_sample();
void show_temple_sample();

void lib_selection_symbols(Library<Manuscript>& lib);
void lib_selection_date(Library<Manuscript>& lib);
void lib_selection_author(Library<Manuscript>& lib);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	TempleList temples;
	ushort source_choice{};
	do
	{
		source_choice = menu(SOURCE_MENU_TEXT, 4);
		switch (source_choice)
		{
		case 1:
			read_from_file(temples);
			break;
		case 2:
			read_from_console(temples);
			break;
		default:
			break;
		}

		if (source_choice != 4)
		{
			ushort main_menu_choice{};
			do
			{
				main_menu_choice = menu(MAIN_MENU_TEXT, 9);
				try
				{
					switch (main_menu_choice)
					{
					case 1:
						std::cout << temples << '\n';
						break;
					case 2:
					{
						std::string out_file_name = input("������� ��� ����� ��� ������\n");
						std::ofstream file(out_file_name);
						file << temples;
						std::cout << "������ ������� �������� � " << out_file_name << '\n';
						break;
					}
					case 3:
					{
						std::cout << "������� ������ �� �������\n\n";
						show_temple_sample();
						std::cin.ignore(std::cin.rdbuf()->in_avail());
						Temple newTemple;
						std::cin >> newTemple;
						temples.add(newTemple);
						break;
					}
					case 4:
						temples.remove(input("������� �������� �����"));
						break;
					case 5:
					{
						const Temple& temple = temples.get_temple_ref(input("������� �������� �����"));
						std::cout << temple << '\n';
						break;
					}
					case 6:
					{
						ushort temple_menu_choice{};
						do
						{
							temple_menu_choice = menu(TEMPLE_MENU_TEXT, 7);
							if (temple_menu_choice != 7)
							{
								std::string temple_name = input("������� �������� ����� ��� ��������������");
								Library<Manuscript>& library = temples.get_temple_ref(temple_name).get_library();

								switch (temple_menu_choice)
								{
								case 1:
									temples.change(temple_name, input("������� ����� �������� �����"));
									break;
								case 2:
								{
									std::string new_monk_name = input("������� ��� ������ ������");
									uint new_diligence{};
									validation(new_diligence, [](uint x) {return x > 0 && x <= 100; }, "������� ����������, %");
									temples.change(temple_name, new_monk_name, new_diligence);
									break;
								}
								case 3:
								{
									std::cout << "������� ������ �� �������\n\n";
									show_manuscript_sample();
									std::cin.ignore(std::cin.rdbuf()->in_avail());
									Manuscript new_manuscript;
									std::cin >> new_manuscript;
									ushort c = menu("���� �������� ��������?\n1. ����� �� ������\n2.������ �� ������\n", 2);
									c == 1 ? library.add_left(new_manuscript) : library.add_right(new_manuscript);
									break;
								}
								case 4:
								{
									ushort c = menu("��� ������� ��������?\n1. ����� �� ������\n2. ������ �� ������\n", 2);
									c == 1 ? library.remove_left() : library.remove_right();
									break;
								}
								case 5:
								{
									ushort c = menu("��� �������� ��������?\n1. ����� �� ������\n2. ������ �� ������\n", 2);
									std::cout << "������� ������ �� �������\n\n";
									show_manuscript_sample();
									std::cin.ignore(std::cin.rdbuf()->in_avail());
									Manuscript new_manuscript;
									std::cin >> new_manuscript;
									c == 1 ? library.change_left(new_manuscript) : library.change_right(new_manuscript);
									break;
								}
								case 6:
								{
									ushort c = menu("�������� �������� ��� �������\n1. �� ���������� ��������\n2. �� ����\n 3. �� ������\n");
									switch (c)
									{
									case 1:
									{
										lib_selection_symbols(library);
										break;
									}
									case 2:
									{
										lib_selection_date(library);
										break;
									}
									case 3:
									{
										lib_selection_author(library);
										break;
									}
									}
									break;
								}
								default:
									break;
								}
							}
						} while (temple_menu_choice != 7);
						break;
					}
					case 7:
					{
						std::string from_temple_name = input("������� �������� ����� �� �������� �����������");
						std::string to_temple_name = input("������� �������� ����� � ������� �����������");
						bool from_side{}, to_side{};
						from_side = menu("������ ����� ��������:\n1.�����\n2.������\n", 2) - 1;
						to_side = menu("��� �������� ��������:\n1.�����\n2.������\n", 2) - 1;
						temples.move(from_temple_name, from_side, to_temple_name, to_side);
						std::cout << "1:\n" << temples.get_temple_ref(from_temple_name) << "2:\n" <<
							temples.get_temple_ref(to_temple_name) << '\n';
						break;
					}
					case 8:
						temples.about(std::cout);
						break;
					case 9:
						break;
					}
				}
				catch (std::exception exception)
				{
					std::cout << "������: " << exception.what() << '\n';
				}
				
			} while (main_menu_choice != 9);
		}
	} while (source_choice != 4);

}


void read_from_file(TempleList& temples)
{
	short file_status{};
	while (file_status != 1)
	{
		std::string filename = input("������� ��� �����");
		std::fstream file(filename, std::fstream::in);
		switch (file_status = check_file(file))
		{
		case -1:
			std::cout << filename << " �� ������\n";
			break;
		case 0:
			std::cout << filename << " ����\n";
			break;
		case 1:
			try
			{
				file >> temples;
				std::cout << filename << " ������� ��������\n";
			}
			catch (std::exception& exception)
			{
				file_status = -1;
				std::cout << "������ ������ �����: \n" << exception.what() << '\n';
			}
			break;
		}
		file.close();
	}
}

void read_from_console(TempleList& temples)
{
	std::cout << "������� ������ �� �������\n\n";
	show_temple_sample();
	try
	{
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cin >> temples;
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
	}
	catch (std::invalid_argument exception)
	{
		std::cout << "������ ������! " << exception.what() << '\n';
	}

}

void show_manuscript_sample()
{
	std::cout << "��������\n��� ������\n1890-05-21\n�����\n" <<
		"������ �������� ����� ����� ����: ���������, ������ ��� �����\n\n";
}

void show_temple_sample()
{
	std::cout << "�������� �����\n��� ������\n20(����������)\n\n����� (������, ���������, ��������)"
		"\n����� �����\n1866-11-16\n�����\n\n========================================\n";
}

void lib_selection_symbols(Library<Manuscript>& library)
{
	uint left{}, right{};
	validation(left, [](uint x) {return x > 0; }, "������� ����������� ���������� ��������");
	validation(right, [left](uint x) {return x > 0 && x < left; }, "������� ������������ ���������� ��������");
	auto res = library.selection([left, right](const Manuscript& elem) {return right > elem.get_text().size() && left <= elem.get_text().size(); });
	std::cout << res << '\n';
}

void lib_selection_date(Library<Manuscript>& library)
{
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cout << "������� ���� �� �������: 1980-05-01\n";
	std::chrono::year_month_day date1{}, date2{};
	bool fl{ false };
	while (!fl)
	{
		std::cout << "������� ����� �������� ��������� ����\n";
		std::chrono::from_stream(std::cin, "%F", date1);
		std::cin.ignore();
		if (std::cin.fail())
			throw std::invalid_argument("������������ �������� ����\n");
		std::cout << "������� ������ �������� ��������� ����\n";
		std::chrono::from_stream(std::cin, "%F", date2);
		if (std::cin.fail())
			throw std::invalid_argument("������������ �������� ����\n");
		if (date1 < date2)
			fl = true;
		else
			std::cout << "������ ������� �� ������ ���� ������ �����.\n";
	}
	auto res = library.selection([date1, date2](const Manuscript& elem) {return date2 > elem.get_date() && date1 <= elem.get_date(); });
	std::cout << res << '\n';
}

void lib_selection_author(Library<Manuscript>& library)
{
	std::string author = input("������� ��� ������");
	auto res = library.selection([author](const Manuscript& elem) {return author == elem.get_author(); });
	std::cout << res << '\n';
}
