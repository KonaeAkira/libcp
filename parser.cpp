#include <iostream>
#include <fstream>
#include <set>
std::set<std::string> std_includes, libcp_includes;
std::string libcp_body, main_body;

void parse_file(std::string name, std::string &body, bool indent = false)
{
	std::fstream src(name, std::ios::in);
	std::string line;
	while (std::getline(src, line))
		if (line.substr(0, 8) == "#include")
		{
			std::string name = line.substr(10, line.size() - 11);
			if (line[9] == '<')
				std_includes.insert(name);
			else if (!libcp_includes.count(name))
			{
				libcp_includes.insert(name);
				parse_file("include/" + name, libcp_body, true);
			}
		}
		else
		{
			if (indent) body.push_back('	');	
			body += line + '\n';
		}
	body.push_back('\n');
	src.close();
}

int main()
{
	parse_file("main.cpp", main_body);

	std::fstream tar("final.cpp", std::ios::out);
	for (std::string name : std_includes)
		tar << "#include <" << name << ">\n";
	if (!libcp_body.empty())
	{
		libcp_body.pop_back();
		tar << "\nnamespace libcp\n{\n" << libcp_body << "}\n";
	}
	tar << main_body;
	tar.close();
}
