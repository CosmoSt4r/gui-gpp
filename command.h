#ifndef COMMAND_H
#define COMMAND_H
#include <string>
#include <vector>

enum Errors
{
    NO_SOURCE_FILES
};

class Command
{
    std::string includePath, libPath, optimization,
                standard, outputName, outputPath;
    std::vector<std::string> libraries, sourceFiles;

public:
    Command();

    void addSourceFiles(const std::vector<std::string>& files);
    void clearSourceFiles();
    void setIncludePath(const std::string& path);
    void setLibPath(const std::string& path);
    void setLibraries(const std::string& libs);
    void setOutputPath(const std::string& path);

    void setOptimization(const std::string& optimization);
    void setStandard(const std::string& standard);
    void setOutputName(const std::string& name);

    std::string get() const;
    std::string getSourceFiles() const;
    std::string getFilePath() const;

    bool operator==(const Command& rhs);
};

#endif // COMMAND_H
