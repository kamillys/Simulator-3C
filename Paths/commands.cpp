#include "commands.h"


CNCCommand::CNCCommand(CNCType _type, glm::dvec3 _data, std::string _command)
    :command(_command),
      type(_type),
      data(_data){}
