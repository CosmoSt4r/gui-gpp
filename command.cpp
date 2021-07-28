#include "command.h"

Command::Command()
{ ; }

void
Command::setSourceFiles(const std::string& files)
{
    std::string file = "";
    for (const char& c : files)
    {
        if (c == ' ' && file != "")
        {
            this->sourceFiles.push_back(file);
            file = "";
        }
        file += c;
    }
}

void
Command::setIncludePath(const std::string& path)
{ this->includePath = path; }

void
Command::setLibPath(const std::string& path)
{ this->libPath = path; }

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

    if (!this->sourceFiles.size())
    { throw Errors::NO_SOURCE_FILES; }

    for (const std::string& file : this->sourceFiles)
    { command += file + " "; }

    if (this->includePath != "")
    { command += "-I" + includePath + " "; }

    if (this->libPath != "")
    { command += "-L" + libPath + " "; }

    return command;
}
