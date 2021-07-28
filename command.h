#ifndef COMMAND_H
#define COMMAND_H
#include <string>
#include <vector>

enum Errors
{
    NO_SOURCE_FILES = -1,
};

class Command
{
    std::string includePath, libPath, optimization,
                standard, outputName;
    std::vector<std::string> libraries, sourceFiles;

public:
    Command();

    void setSourceFiles(const std::string& files);
    void setIncludePath(const std::string& path);
    void setLibPath(const std::string& path);
    void setLibraries(const std::string& libs);

    void setOptimization(const std::string& optimization);
    void setStandard(const std::string& standard);
    void setOutputName(const std::string& name);

    std::string get() const;
    std::string getSourceFiles() const;
};

#endif // COMMAND_H
