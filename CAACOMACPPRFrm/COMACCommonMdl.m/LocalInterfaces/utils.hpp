#ifndef GLAWAY_CAA_UTILS_H
#define GLAWAY_CAA_UTILS_H

#include <windows.h>
#include <iostream>
#include <string>
#include <map>

static HMODULE g_dll(NULL);

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		g_dll = hModule;
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		g_dll = NULL;
		break;
	}
	return TRUE;
}

namespace logfile ///< namespace of logfile
{
const static char *endl = "\n";
class LogSystem
{
public:
	static LogSystem * GetInstance();
	static void Release();
	~LogSystem();
	/**
	 * \brief Log CP_ACP message
	 */
	void LogMessage(const char *msg);

	/**
	 * \brief log message
	 */
	void LogMessage(const wchar_t *msg);

	/**
	 * \brief operator <<
	 */
	LogSystem& operator <<(const char *msg)
	{
		LogMessage(msg);
		return *this;
	}
	LogSystem& operator <<(const std::string &msg)
	{
		LogMessage(msg.c_str());
		return *this;
	}
	LogSystem& operator <<(const wchar_t *msg)
	{
		LogMessage(msg);
		return *this;
	}
	LogSystem& operator <<(const std::wstring &msg)
	{
		LogMessage(msg.c_str());
		return *this;
	}

	LogSystem& operator <<(long msg)
	{
		wchar_t buf[32];
		swprintf_s(buf, L"%ld", msg);
		LogMessage(buf);
		return *this;
	}

#ifdef DASSAULT_CAA_CODE
	LogSystem& operator <<(const CATUnicodeString &msg)
	{
		int len = msg.GetLengthInChar() * 2 + 1;
		wchar_t *buf = new wchar_t[len];
		msg.ConvertToWChar(buf);
		LogMessage(buf);
		delete[] buf;
		return *this;
	}
	LogSystem& operator <<(const CATString &msg)
	{
		LogMessage(msg.ConvertToChar());
		return *this;
	}
#endif

	/**
	 * \brief Convert unicode to char
	 */
	static std::string Unicode2Char(const wchar_t *str, DWORD code_page, DWORD flag);

	/**
	 * \brief convert char to unicode
	 */
	static std::wstring Char2Unicode(const char *str, DWORD code_page, DWORD flag);
protected:
	/**
	 * \brief Create log file if not exist
	 */
	int CreateLogFile();
	LogSystem() : file_(NULL){}
protected:
	FILE *file_;
	static LogSystem *inst_;
};

inline void LogSystem::LogMessage(const char *msg)
{
	CreateLogFile();
	std::wstring str_unicode = Char2Unicode(msg, CP_ACP, 0);
	std::string str_utf8 = Unicode2Char(str_unicode.c_str(), 0, CP_UTF8);
	std::cout << msg;
	if (!file_)
		return;
	fwrite(str_utf8.c_str(), sizeof(char), str_utf8.size(), file_);
}

inline void LogSystem::LogMessage(const wchar_t *msg)
{
	CreateLogFile();
	std::string str_acp = Unicode2Char(msg, 0, CP_ACP);
	std::cout << str_acp;
	if (!file_)
		return;
	std::string str_msg = Unicode2Char(msg, CP_UTF8, 0);
	fwrite(str_msg.c_str(), sizeof(char), str_msg.size(), file_);
}

inline int LogSystem::CreateLogFile()
{
	if (file_)
		return 0;
	DWORD pid = ::GetCurrentProcessId();
	wchar_t log_dir[MAX_PATH];
	::GetModuleFileName(g_dll, log_dir, MAX_PATH);
	int len = static_cast<int>(wcslen(log_dir));
	int size_seg(0);
	for (int index = len-1; index >= 0; --index)
	{
		if (L'\\'== log_dir[index] || L'/' == log_dir[index])
			++size_seg;
		if (3 == size_seg)
		{
			log_dir[index + 1] = L'\0';
			break;
		}
	}
	wcscat_s(log_dir, L"log\\");
	::CreateDirectory(log_dir, NULL); ///< Create log directory
	wchar_t log_file_path[MAX_PATH];
	swprintf_s(log_file_path, L"%s%d.log", log_dir, pid);
	if (_wfopen_s(&file_, log_file_path, L"w+"))
	{
		file_ = NULL;
		std::wcout << L"open log file: " << log_file_path << L" fail" << std::endl;
		return -1;
	}
	return 0;
}

inline LogSystem::~LogSystem()
{
	if (file_)
		fclose(file_);
	file_ = NULL;
}

inline std::string LogSystem::Unicode2Char(const wchar_t *str, DWORD code_page, DWORD flag)
{
	int buf_size = ::WideCharToMultiByte(code_page, flag, str, -1, NULL, 0, NULL, NULL) + 1;
	if (buf_size <= 1)
		return std::string();
	char *buf = new char[buf_size];
	::WideCharToMultiByte(code_page, flag, str, -1, buf, buf_size, NULL, NULL);
	std::string ret = buf;
	delete[] buf;
	return ret;
}

inline std::wstring LogSystem::Char2Unicode(const char *str, DWORD code_page, DWORD flag)
{
	int buf_size = ::MultiByteToWideChar(code_page, flag, str, -1, NULL, 0) + 1;
	if (buf_size <= 1)
		return std::wstring();
	wchar_t *buf = new wchar_t[buf_size];
	::MultiByteToWideChar(code_page, flag, str, -1, buf, buf_size);
	std::wstring ret = buf;
	delete[] buf;
	return ret;
}

logfile::LogSystem * LogSystem::GetInstance()
{
	if (!inst_)
		inst_ = new LogSystem;
	return inst_;
}

void LogSystem::Release()
{
	if (inst_)
		delete inst_;
	inst_ = NULL;
}

}

//logfile::LogSystem * logfile::LogSystem::inst_ = NULL; ///< place source code using this class

namespace conf  //< namespace start
{
/**
 * \brief utility class for reading configure, replace of CATMsgCatalog in CAA
 */
class ConfReader
{
public:
	ConfReader();

	/**
	 * \brief Load configure
	 */
	int LoadConf(const wchar_t *name);

	/**
	 * \brief Get configure entity
	 */
	std::wstring GetConfig(const wchar_t *conf_name);
#ifdef DASSAULT_CAA_CODE
	/**
	 * \brief 
	 */
	CATUnicodeString CATGetConfig(const wchar_t *conf_name);
#endif
	/**
	 * \brief utility for split string
	 */
	static std::vector<std::wstring> SplitString(const std::wstring &input, const std::wstring &seg);

	/**
	 * \brief trim space and tab
	 */
	static void TrimString(std::wstring &value);
protected:
	int LoadConfig();
	
private:
	std::wstring name_;
	std::map<std::wstring, std::wstring> entities_;
};

ConfReader::ConfReader()
{
	
}
inline int ConfReader::LoadConf(const wchar_t *name)
{
	name_ = name;
	LoadConfig();
	return 0;
}
inline int ConfReader::LoadConfig()
{
	entities_.clear();
	if (name_.empty())
		return -1;
	//Get path of configure file
	wchar_t conf_path[MAX_PATH];
	::GetModuleFileName(g_dll, conf_path, MAX_PATH);
	int len = static_cast<int>(wcslen(conf_path));
	int size_parent_folder(0);
	for (int index = len-1; index >= 0; --index)
	{
		if (L'\\'== conf_path[index] || L'/' == conf_path[index])
			++size_parent_folder;
		if (3 == size_parent_folder)
		{
			conf_path[index + 1] = L'\0';
			break;
		}
	}
	wcscat_s(conf_path, L"resources\\msgcatalog\\");
	wcscat_s(conf_path, name_.c_str());
	wcscat_s(conf_path, L".txt");
	std::wstring log_msg = L"Full config path:";
	log_msg += conf_path;
	logfile::LogSystem::GetInstance()->LogMessage(log_msg.c_str());
	fstream file_conf;
	file_conf.open(conf_path, std::ios_base::in);
	if (file_conf.fail() || file_conf.bad())
	{
		log_msg = L"open config file:";
		log_msg += conf_path;
		log_msg += L" fail!";
		logfile::LogSystem::GetInstance()->LogMessage(log_msg.c_str());
		return -1;
	}
	std::string str_line;
	while (std::getline(file_conf, str_line))
	{
		if (str_line.empty()) ///< empty line, ignore
			continue;
		//convert to wchar_t using UTF-8, MUST encoding using UTF-8!
		int buf_size = ::MultiByteToWideChar(CP_UTF8, 0, str_line.c_str(), -1, NULL, 0) + 1;
		if (buf_size <= 1)
			continue;
		wchar_t *buf = new wchar_t[buf_size];
		::MultiByteToWideChar(CP_UTF8, 0, str_line.c_str(), -1, buf, buf_size);
		std::wstring wcs_line = buf;
		delete[] buf;
		size_t index_equal = wcs_line.find(L'=');
		if (wcs_line.npos == index_equal) ///< invalid configure entity, ignore
			continue;
		std::wstring key = wcs_line.substr(0, index_equal);
		std::wstring value = wcs_line.substr(index_equal + 1);
		TrimString(key);
		TrimString(value);
		if (!value.empty() && L';' == value[value.size() - 1])
			value.erase(value.begin() + value.size() -1);
		if (value.size() >= 2 && L'\"' == value[0] && L'\"' == value[value.size() -1])
		{
			value.erase(value.begin());
			value.erase(value.begin() + value.size() -1);
		}
		if (!value.empty() && !key.empty())
			entities_[key] = value;
	}
	file_conf.close();
	return 0;
}

inline void ConfReader::TrimString(std::wstring &value)
{
	size_t index_start = value.find_first_not_of(L"\t\x20");
	if (value.npos == index_start)
	{
		value.clear();
		return;
	}
	size_t index_end = value.find_last_not_of(L"\t\x20");
	if (value.npos != index_end)
		value = value.substr(index_start, index_end + 1);
	else
		value.clear();
}

inline std::wstring ConfReader::GetConfig(const wchar_t *conf_name)
{
	std::wstring log_msg;
	std::map<std::wstring, std::wstring>::const_iterator iter = entities_.find(conf_name);
	if (entities_.end() == iter)
	{
		log_msg = L"configure with entity:";
		log_msg += conf_name;
		log_msg += L" not found";
		logfile::LogSystem::GetInstance()->LogMessage(log_msg.c_str());
		return std::wstring();
	}
	else
	{
		return iter->second;
	}
}

inline std::vector<std::wstring> ConfReader::SplitString(const std::wstring &input, const std::wstring &seg)
{
	std::vector<std::wstring> words;
	size_t index_word_start(0);
	size_t index_word_end(0);
	index_word_end = input.find_first_of(seg, index_word_start);
	do
	{
		std::wstring word = input.substr(index_word_start, index_word_end);
		index_word_start = index_word_end;
		TrimString(word);
		words.push_back(word);
	} while(input.npos != (index_word_end = input.find_first_of(seg, index_word_start)));
	return words;
}
#ifdef DASSAULT_CAA_CODE
CATUnicodeString ConfReader::CATGetConfig(const wchar_t *conf_name)
{
	CATUnicodeString ret;
	std::wstring value = GetConfig(conf_name);
	if (value.empty())
		return ret;
	ret.BuildFromWChar(value.c_str());
	return ret;
}
#endif
} //< namespace end


#endif