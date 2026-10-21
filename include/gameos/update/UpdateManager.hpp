#pragma once
#include <cstdint>
#include <string>
#include <vector>
namespace gameos::update{struct FilePatch{std::string path;std::string sha256;std::uint64_t size{};};struct UpdateManifest{std::string id;std::string version;std::string minimumVersion;std::string channel{"stable"};std::vector<FilePatch>files;};class UpdateManager{public:bool validate(const UpdateManifest&,std::string*error=nullptr)const;bool stage(const UpdateManifest&,const std::string&,std::string*error=nullptr);bool apply(const std::string&,const std::string&,std::string*error=nullptr);bool rollback(const std::string&,const std::string&,std::string*error=nullptr);};}
