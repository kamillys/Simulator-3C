#pragma once

#include <QIODevice>
#include "commands.h"

namespace CNCParser
{

CNCCommandList parse(QIODevice& file);

}
