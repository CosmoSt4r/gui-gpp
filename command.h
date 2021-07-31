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
public:
    Command();

    std::string includePath, libPath, optimization,
                standard, outputName, outputPath,
                templateName;
    std::vector<std::string> libraries, sourceFiles;

    void addSourceFiles(const std::vector<std::string>& files);
    void clearSourceFiles();
    void setLibraries(const std::string& libs);

    std::string get() const;
    std::string getSourceFiles() const;
    std::string getFilePath() const;

    bool operator==(const Command& rhs);
    bool operator!=(const Command& rhs);
};

#endif // COMMAND_H
