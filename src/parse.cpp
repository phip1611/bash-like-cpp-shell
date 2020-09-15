#include "parse.hpp"

ParsedInputData parse(std::string const * const normalized_input) {
    ParsedInputData data;
    if (*normalized_input == "exit") {
        data.setType(InputKind::EXIT);
    } else if (normalized_input->empty()) {
        data.setType(InputKind::EMPTY);
    } else {
        data.setType(InputKind::UNKNOWN);
    }
    return data;
}
