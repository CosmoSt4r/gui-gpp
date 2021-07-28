#include "command.h"

std::vector<std::string> stringSplit(const std::string& str)
{
    std::vector<std::string> result;
    std::string word = "";
    for (const char& c : str)
    {
        if (c == ',')
            continue;

        if (c == ' ' && word != "")
        {
            result.push_back(word);
            word = "";
        }
        else
            word += c;
    }
    return result;
}

Command::Command()
{ ; }

void
Command::setSourceFiles(const std::string& files)
{ this->sourceFiles = stringSplit(files); }

void
Command::setIncludePath(const std::string& path)
{ this->includePath = path; }

void
Command::setLibPath(const std::string& path)
{ this->libPath = path; }

void
Command::setLibraries(const std::string& libs)
{ this->libraries = stringSplit(libs); }

void
Command::setOptimization(const std::string& optimization)
{ this->optimization = optimization; }

void
Command::setStandard(const std::string& standard)
{ this->standard = standard; }

void
Command::setOutputName(const std::string& name)
{ this->outputName = name; }

std::string
Command::get() const
{
    std::string command = "g++ ";

    if (this->sourceFiles.size() == 0)
    { throw Errors::NO_SOURCE_FILES; }

    for (const std::string& file : this->sourceFiles)
    { command += file + " "; }

    for (const std::string& lib : this->libraries)
    { command += "-l" + lib + " "; }

    if (this->includePath != "")
    { command += "-I" + includePath + " "; }

    if (this->libPath != "")
    { command += "-L" + libPath + " "; }

    if (this->optimization != "")
    { command += "-O"; }

    if (this->standard != "")
    { command += "-std="; }

    return command;
}

std::string
Command::getSourceFiles() const
{
    std::string result = "";
    for (const std::string& filepath : this->sourceFiles)
    {
        for (int i = filepath.size() - 1; i >= 0; --i)
        {
            if (filepath[i] == '/' || filepath == "\\")
                break;
            result = filepath[i] + result;
        }
        result = " " + result;
    }

    return result;
}
