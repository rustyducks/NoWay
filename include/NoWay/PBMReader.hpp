#include <string>

#include "NoWay/Node.hpp"
#include "NoWay/TableParams.hpp"

namespace noway{

class PBMReader{
    public:
    PBMReader();
    int readFile(std::string fileName, GraphPtr graph, double* graphTableRatio);

    protected:
    static const std::vector<std::string> MAGICNUMBERS;

    std::string parseMagicNumber(const std::string& line);
    TableSize parseGraphSize(const std::string& line);
    int parseLine(const std::string& line, GraphPtr graph, const unsigned int lineNumber);

};

} //namespace noway