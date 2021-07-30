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

    if (word != "")
        result.push_back(word);

    return result;
}

Command::Command()
{ ; }

void
Command::addSourceFiles(const std::vector<std::string>& files)
{
    for (const std::string& file : files)
        this->sourceFiles.push_back(file);
}

void
Command::clearSourceFiles()
{ this->sourceFiles.clear(); }

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

void
Command::setTemplateName(const std::string& name)
{ this->templateName = name; }

void
Command::setOutputPath(const std::string& path)
{ this->outputPath = path; }

std::string
Command::get() const
{
    std::string command = "g++ ";

    if (this->sourceFiles.size() == 0)
    { throw Errors::NO_SOURCE_FILES; }

    for (const std::string& file : this->sourceFiles)
    { command += '"' + file + "\" "; }

    for (const std::string& lib : this->libraries)
    { command += "-l" + lib + " "; }

    if (this->includePath != "")
    { command += "-I\"" + this->includePath + "\" "; }

    if (this->libPath != "")
    { command += "-L\"" + this->libPath + "\" "; }

    if (this->optimization != "")
    { command += "-O" + this->optimization + " "; }

    if (this->standard != "")
    { command += "-std=" + this->standard + " "; }

    if (this->outputName == "")
        command += "-o \"" + this->outputPath + "output.exe\"";
    else
        command += "-o \"" + this->outputPath + this->outputName + ".exe\"";

    return command;
}

std::string
Command::getSourceFiles() const
{
    std::string result = "";
    for (int i = 0; i < this->sourceFiles.size(); ++i)
    {
        for (int j = sourceFiles[i].size() - 1; j >= 0; --j)
        {
            if (sourceFiles[i][j] == '/' || sourceFiles[i][j] == '\\')
                break;
            result = sourceFiles[i][j] + result;
        }
        result = " " + result;
    }

    return result;
}

std::string
Command::getFilePath() const
{
    return this->outputPath + this->outputName + ".exe";
}

bool
Command::operator==(const Command& rhs)
{ return this->get() == rhs.get(); }

bool
Command::operator!=(const Command& rhs)
{ return this->get() != rhs.get(); }
