module;

#include <iostream>
#include <fstream>
#include <chrono>
#include <string>

export import Library;
export import Manuscript;

export module Temple;

export using uint = unsigned int;

export class Temple
{
private:
	std::string monk_name{};
	std::string temple_name{};
	uint diligence{};
	Library<Manuscript> library{};
public:
	Temple() {};
	Temple(std::string monk_name, std::string temple_name, uint diligence, const Library<Manuscript>& library)
		: monk_name(monk_name), temple_name(temple_name), diligence(diligence), library(library)
	{}

    uint get_diligence() const { return diligence; }

    friend std::ostream& operator<<(std::ostream& out, Temple& temple)
    {
        out << temple.temple_name << '\n'
            << temple.monk_name << '\n'
            << temple.diligence << '\n' << '\n'
            << temple.library
            << "========================================\n";
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Temple& temple)
    {
        Temple tmp;
        std::string delim_line{};

        std::getline(in, tmp.temple_name);
        std::getline(in, tmp.monk_name);
        if (!(in >> tmp.diligence) && tmp.diligence > 100)
            throw std::invalid_argument("Недопустимое значение усердности\n");
        in.ignore(1, '\n');
        std::getline(in, delim_line);
        in >> tmp.library;
        in.clear();

        temple = tmp;
        return in;
    }
};