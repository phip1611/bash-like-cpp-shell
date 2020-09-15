#include <cassert>
#include <sstream>
#include "properties.hpp"


InputKind ParsedInputData::getType() const {
    return type;
}

void ParsedInputData::setType(InputKind new_type) {
    ParsedInputData::type = new_type;
}

std::string *ParsedInputData::getDataCdDir() {
    assert(this->type == InputKind::CD);
    assert(this->dataCdDir.has_value());
    return &this->dataCdDir.value();
}

CommandChain *ParsedInputData::getDataCommandChain() {
    assert(this->type == InputKind::COMMAND);
    assert(this->dataCommandChain.has_value());
    return &this->dataCommandChain.value();
}

std::string *ParsedInputData::getDataAliasName() {
    assert(this->type == InputKind::GET_ALIAS || this->type == InputKind::UN_ALIAS);
    assert(this->dataAliasName.has_value());
    return &this->dataAliasName.value();
}

std::string *ParsedInputData::getDataAliasValue() {
    assert(this->type == InputKind::SET_ALIAS);
    assert(this->dataAliasValue.has_value());
    return &this->dataAliasValue.value();
}

std::string ParsedInputData::toString() {
    std::ostringstream stringStream;
    stringStream << "ParsedInputData {\n";
    stringStream << "  type: " << input_kind_to_string(this->type) << "\n";

    stringStream << "  dataCdDir: ";
    if (this->dataCdDir.has_value()) {
        stringStream << this->dataCdDir.value();
    } else {
        stringStream << "<none>\n";
    }

    stringStream << "  dataCommandChain: ";
    if (this->dataCommandChain.has_value()) {
        stringStream << this->dataCommandChain->toString();
    } else {
        stringStream << "<none>\n";
    }


    stringStream << "  dataAliasName: ";
    if (this->dataAliasName.has_value()) {
        stringStream << this->dataAliasName.value();
    } else {
        stringStream << "<none>\n";
    }

    stringStream << "  dataAliasValue: ";
    if (this->dataAliasValue.has_value()) {
        stringStream << this->dataAliasValue.value();
    } else {
        stringStream << "<none>\n";
    }

    stringStream << "}";

    return stringStream.str(); // creates a copy
}

std::string CommandChain::toString() {
    std::ostringstream stringStream;
    stringStream << "CommandChain {\n";
    stringStream << "}";

    return stringStream.str(); // creates a copy
}

std::string input_kind_to_string(InputKind const ik) {
    switch (ik) {
        case EMPTY:
            return "EMPTY";
        case CD:
            return "CD";
        case EXIT:
            return "EXIT";
        case COMMAND:
            return "COMMAND";
        case SET_ALIAS:
            return "SET_ALIAS";
        case GET_ALIAS:
            return "GET_ALIAS";
        case UN_ALIAS:
            return "UN_ALIAS";
        case UNKNOWN:
        default:
            return "UNKNOWN";
    }
}
