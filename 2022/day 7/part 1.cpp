#include <iostream>
#include <fstream>
#include <unordered_map>

unsigned totalSize = 0;

class Dir
{
	public:
		Dir* getParent() { return parentDir; }
		Dir* getSubDir(const std::string & name) { return subDirs.at(name); }
		unsigned getTotalSize();

		void ls(std::ifstream & input);
		void dir(const std::string & name);

	private:
		std::unordered_map<std::string, Dir*> subDirs;
		Dir *parentDir;
		unsigned size = 0;
};

unsigned Dir::getTotalSize()
{
	unsigned size = this->size;
	
	for (auto & it : subDirs)
	{
		unsigned s = it.second->getTotalSize();
		if (s <= 100000)
			totalSize += s;
		size += s;
	}
	
	if (size == this->size)
		return size;
		
	return size;
}

void Dir::ls(std::ifstream & input)
{
	std::string line;

	while (input.peek() != EOF && input.peek() != '$')
	{
		std::getline(input, line);

		if (line.substr(0, 3) == "dir")
			dir(line.substr(4));
		else
			size += std::stoi(line.substr(0, line.find(' ')));
	}
}

void Dir::dir(const std::string & name)
{
	subDirs[name] = new Dir;
	subDirs.at(name)->parentDir = this;
}

void cd(Dir** currentDir, const std::string & dstDir);

int main()
{
	std::ifstream input("input.txt");
	std::string line;
	
	Dir root;
	
	Dir* currentDir = &root;
	
	getline(input, line);
	
	while (getline(input, line))
	{
		std::string command = line.substr(0,4);

		if (command == "$ cd")
			cd(&currentDir, line.substr(5));
		else if(command == "$ ls")
			currentDir->ls(input);
	}
	
	root.getTotalSize();
	
	std::cout << totalSize << "\n";
	
	return 0;
}

void cd(Dir** currentDir, const std::string & dstDir)
{
	if (dstDir == "..")
		*currentDir = (*currentDir)->getParent();
	else
		*currentDir = (*currentDir)->getSubDir(dstDir);
	
	// currentDir = dstDir == ".." ? currentDir->parentDir : currentDir->subDirs.at(dstDir);
}
