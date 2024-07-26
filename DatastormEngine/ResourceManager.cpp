#include "ResourceManager.h"
#include <iostream>
#if __cplusplus <= 201402L 
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#endif

#if __cplusplus >= 201703L
#include <filesystem>
#endif

ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}

ResourcePtr ResourceManager::createResourceFromFile(const wchar_t* file_path)
{

    std::wstring full_path = L"";  // Default initialization

#if (_MSC_VER >= 1900 && _MSC_VER <= 1916)  || ( _MSC_VER >= 1920 && __cplusplus <= 201402L) 
    full_path = std::experimental::filesystem::absolute(file_path);
#endif

#if _MSC_VER >= 1920 && __cplusplus > 201402L 
    full_path = std::filesystem::absolute(file_path);
#endif

    auto it = m_map_resources.find(full_path);

    if (it != m_map_resources.end())
    {
        std::cout << "Mesh found in the map!" << std::endl;
        return it->second;
    }

    Resource* raw_res = this->createResourceFromFileConcrete(full_path.c_str());

    if (raw_res)
    {
        ResourcePtr res(raw_res);
        m_map_resources[full_path] = res;
        std::wcout << L"Resource loaded for path: " << full_path << std::endl;
        return res;
    }
    else
    {
        // Use std::wcout for wide strings
        std::wcout << L"Resource not found for path: " << full_path << std::endl;
    }

	return nullptr;
}