#include <fstream>
#include<string>

int main()
{
	std::fstream fin("test.txt", std::ios::in);
	std::fstream fout("result.txt", std::ios::out);

	bool double_slash = 0;

	bool slash_star = 0;

	bool string_literal = 0;

	std::string line;

	while (std::getline(fin, line))
	{
		double_slash = 0;

		for (auto i =0; i < line.length();++i)
		{

			if (!double_slash)
			{

				if (line[i] == '"' && (i == 0 or line[i - 1] != '\\'))
				{
					string_literal = !string_literal;
				}

				if (!string_literal)
				{
					if (line[i] == '/' && i < line.length() - 1 && !slash_star)
					{
						++i;

						if (line[i] == '/')
						{
							double_slash = 1;
						}
						else
						{
							if (line[i] == '*')
							{
								slash_star = 1;
							}

							else
							{		
								fout << '/' << line[i];
								continue;

							}

						}
					}
					else
					{

						if (line[i] == '*' && slash_star && i < line.length() - 1)
						{
							++i;

							if (line[i] == '/')
							{
								slash_star = 0;

								continue;
							}
						}
					}
				}
			}
			
			if (!slash_star && !double_slash)
			{
				fout << line[i];
			}

		}
			

		fout << '\n';

	}

	return 0;
}
