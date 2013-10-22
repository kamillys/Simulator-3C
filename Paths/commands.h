#pragma once
#include <string>
#include <VTF/Math>
#include <vector>

enum class CNCType {
    Move,
    None
};

struct CNCCommand
{
    std::string command;
    CNCType type;
    glm::dvec3 data;
    CNCCommand(CNCType _type = CNCType::None, glm::dvec3 _data = glm::vec3(), std::string _command = "");
};

typedef std::vector<CNCCommand> CNCCommandList;
