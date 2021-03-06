#pragma once
#include "Util/FileClasses.h"

class AssemblerFile;

struct SymDataSymbol
{
	std::wstring name;
	int address;
	
	bool operator<(const SymDataSymbol& other) const
	{
		return address < other.address;
	}
};

struct SymDataAddressInfo
{
	int address;
	int fileIndex;
	int lineNumber;
	
	bool operator<(const SymDataAddressInfo& other) const
	{
		return address < other.address;
	}
};

struct SymDataFunction
{
	int address;
	int size;
	
	bool operator<(const SymDataFunction& other) const
	{
		return address < other.address;
	}
};

struct SymDataData
{
	int address;
	int size;
	int type;
	
	bool operator<(const SymDataData& other) const
	{
		return address < other.address;
	}
};

struct SymDataModule
{
	AssemblerFile* file;
	std::vector<SymDataAddressInfo> addressInfo;
	std::vector<SymDataSymbol> symbols;
	std::vector<SymDataFunction> functions;
	std::vector<SymDataData> data;
};

struct SymDataModuleInfo
{
	unsigned int crc32;
};

class SymbolData
{
public:
	enum DataType { Data8, Data16, Data32, DataAscii };

	SymbolData();
	void clear();
	void setNocashSymFileName(const std::wstring& name, int version) { nocashSymFileName = name; nocashSymVersion = version; };
	void setExSymFileName(const std::wstring& name) { exSymFileName = name; };
	void write();
	void setEnabled(bool b) { enabled = b; };

	void addLabel(int address, const std::wstring& name);
	void addData(int address, int size, DataType type);
	void startModule(AssemblerFile* file);
	void endModule(AssemblerFile* file);
	void startFunction(int address);
	void endFunction(int address);
private:
	void writeNocashSym();
	void writeExSym();
	int addAddress(int address);
	int addFileName(const std::string& fileName);

	std::wstring nocashSymFileName;
	std::wstring exSymFileName;
	bool enabled;
	int nocashSymVersion;

	// entry 0 is for data without parent modules
	std::vector<SymDataModule> modules;
	std::vector<std::string> files;
	int currentModule;
	int currentFunction;
};
