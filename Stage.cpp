#include "Stage.h"
#include <cassert>
#include <fstream>
#include <string>
#include <sstream>

void Stage::LoadStage(const std::string& csv)
{
    std::ifstream ifs{csv};

    uint32_t x{}, y{}, z{};

    std::string line, tmp;

    if (state_ == Dimension::TWO) {
        while (std::getline(ifs, line)) {
            std::istringstream line_stream{ line };

            while (std::getline(line_stream, tmp, ',')) {
                fieldArray_.field2d_[y][x] = std::stoi(tmp);
                x++;
            }

            y++;
        }
    }
    else {

    }
}

void Stage::Draw(void)
{
    if (state_ == Dimension::TWO) {
        for (size_t y = 0; y < lengthY_; y++) {
            for (size_t x = 0; x < lengthX_; x++) {
                
            }
        }
    }
}
