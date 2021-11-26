#include <iostream>
#include <vector>

struct SinkInfo {
    unsigned id;
    std::string name;
    SinkInfo(unsigned id) : id(id) {};
    SinkInfo(std::string name) : id(id), name(name){};
    SinkInfo(unsigned id, std::string name) : id(id), name(name) {};
};

int main(int argc, char *argv[]) {
    std::cout << "emplace back" << std::endl;
    std::vector<SinkInfo> sinkInfo;
    sinkInfo.emplace_back("alsa");
    sinkInfo.emplace_back(1);
    sinkInfo.emplace_back(2, "lsy");

    return 0;
}