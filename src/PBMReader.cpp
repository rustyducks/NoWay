#include "PBMReader.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "TableParams.hpp"

using namespace noway;
using namespace std;

const vector<string> PBMReader::MAGICNUMBERS = {"P1", "P2", "P3", "P4", "P5"};

PBMReader::PBMReader(){

}

std::string PBMReader::parseMagicNumber(const std::string& line){
    for (auto mn: PBMReader::MAGICNUMBERS){
        if (line == mn){
            return mn;
        }
    }
    std::cout << "Unable to parse PBM magic number" << std::endl;
    return "";
}

TableSize PBMReader::parseGraphSize(const std::string& line){
    std::istringstream iss(line);
    unsigned int width, height;
    if (!(iss >> width >> height)) { 
        std::cout << "Could not parse width and height" << std::endl;
        return {0, 0};
    } // error
    std::cout << "Graph size : " << width << "x" << height << std::endl;
    return {width, height};
}

int PBMReader::parseLine(const std::string& line, GraphPtr graph, const unsigned int lineNumber){
    for (size_t i=0; i < line.length(); i++){
        const char c = line[i];
        graph->at(i).push_back(make_shared<Node>(c == '0', i, lineNumber));
    }
    return 0;
}

int PBMReader::readFile(std::string fileName, GraphPtr graph, double* graphTableRatio){
    for (auto row: *graph){
        row.clear();
    }
    graph->clear();

    std::fstream infile(fileName);
    if (!infile.good()){
        std::cerr << "Could not open file : " << fileName << std::endl;
        return -3;
    }
    std::string line = "";
    std::string magicNumber = "";
    TableSize graphSize = {0, 0};
    unsigned int lineNumber = 0;
    while (std::getline(infile, line))
    {
        // Comments handling
        if (line.rfind("#", 0) == 0){
            continue;
        }

        // Magic number parsing
        if (magicNumber.empty()){
            magicNumber = parseMagicNumber(line);
            continue;
        }else{
            // Graph size parsing
            if ((graphSize.width == 0) && (graphSize.height == 0)){
                graphSize = parseGraphSize(line);
                if ((graphSize.width == 0) && (graphSize.height == 0)){
                    return -1;
                }
                graph->resize(graphSize.width);
                // for (size_t i=0; i<graphSize.width; i++){
                //     (*graph)[i].resize(graphSize.height);
                // }
                *graphTableRatio = (double)graphSize.width / REAL_SIZE.width;
                if (*graphTableRatio != (double)graphSize.height / REAL_SIZE.height){
                    std::cout << "Graph table ratios do not match on both dimensions" << std::endl;
                    return -4;
                }
                continue;
            }
            // Actual graph parsing
            if (parseLine(line, graph, lineNumber) != 0){
                std::cout << "Error during graph line parsing" << std::endl;
                return -2;
            }
            lineNumber++;
        }
    }
    std::cout << "Graph successfully parsed" << std::endl;
    return 0;
}