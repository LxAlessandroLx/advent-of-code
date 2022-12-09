#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

#define MAX_STORAGE 70000000
#define MINIMUM_FREE_SPACE 30000000

unsigned min = -1;

class Dir
{
	public:
		Dir* getParent() { return parentDir; }
		Dir* getSubDir(const std::string & name) { return subDirs.at(name); }
		unsigned getTotalSize(unsigned totalSize);
		unsigned getSize() { return size; }

		void ls(std::ifstream & input);
		void dir(const std::string & name);

	private:
		std::unordered_map<std::string, Dir*> subDirs;
		Dir *parentDir = nullptr;
		unsigned size = 0;
};

unsigned Dir::getTotalSize(unsigned totalSize)
{
    unsigned t = MINIMUM_FREE_SPACE-(MAX_STORAGE-totalSize);
	unsigned size = this->size;
	
	for (const auto & it : subDirs)
	{
		unsigned s = it.second->getTotalSize(totalSize);
		if (s >= t && min > s)
			min = s;
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

	unsigned ts = 0;
	
	getline(input, line);
	
	while (getline(input, line))
	{
		std::string command = line.substr(0,4);

		if (command == "$ cd")
		{
			cd(&currentDir, line.substr(5));
		}
		else if(command == "$ ls")
		{
			currentDir->ls(input);
			ts += currentDir->getSize();
		}
	}
	
	root.getTotalSize(ts);
	
	std::cout << min << "\n";
	
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
