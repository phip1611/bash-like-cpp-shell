#include <zconf.h>
#include <cstring>
#include "action.hpp"

void action_cd(ParsedInputData *data) {
    int res = chdir(data->getDataCdDir().c_str());
    if (res == -1) {
        std::cerr << "Failed to cd to '" << data->getDataCdDir() << "', "
                  << "error code is: '" << strerror(errno) << "'" << std::endl;
    }
}

void action_command(ParsedInputData *data) {

}

void action_alias(ParsedInputData *data, InputKind aliasKind) {
    // TODO
}
