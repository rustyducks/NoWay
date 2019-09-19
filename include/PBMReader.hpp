#include <string>

#include "Node.hpp"
#include "TableParams.hpp"

namespace noway{

class PBMReader{
    public:
    PBMReader();
    int readFile(std::string fileName, Graph* graph);

    protected:
    static const std::vector<std::string> MAGICNUMBERS;

    std::string parseMagicNumber(const std::string& line);
    TableSize parseGraphSize(const std::string& line);
    int parseLine(const std::string& line, Graph& graph, const unsigned int lineNumber);

};

} //namespace noway