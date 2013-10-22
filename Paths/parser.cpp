#include "parser.h"
#include <VTF/Exception>
#include <QDebug>
#include <QtCore>

CNCCommandList CNCParser::parse(QIODevice &file)
{
    CNCCommandList commands;
    while(!file.atEnd()) {
        QString line = file.readLine();
        line.remove("\n");
        if (line.isNull() || line.isEmpty() || line.length() == 0)
            continue;
        size_t offset = 0;
        glm::dvec3 lastPosition;

        QRegularExpression InstructionNumberRE("N\\d+");
        QRegularExpression GCodeRE("[A-Za-z]\\d+");
        QRegularExpression PositionRE;
        {
            QString number ("(-?\\d+\\.\\d\\d\\d)");
            PositionRE.setPattern("X"+number+"Y"+number+"Z"+number);
        }

        QRegularExpressionMatch result = InstructionNumberRE.match(line, offset);
        if (!result.hasMatch()) {
            qWarning() << "Invalid instruction number";
        } else {
            offset = result.capturedEnd();
        }
        result = GCodeRE.match(line, offset);
        if (result.hasMatch()) {
            offset = result.capturedLength();
            QString OP = result.captured();
            if (OP == "G01") {
                result = PositionRE.match(line, offset);
                if (result.hasMatch()) {
//                    qDebug() << line;
//                    qDebug() << "       "+result.captured();

                    lastPosition.x = result.captured(1).toDouble();
                    lastPosition.y = result.captured(2).toDouble();
                    lastPosition.z = result.captured(3).toDouble();
//                    qDebug() << lastPosition.x << lastPosition.y << lastPosition.z;
                    commands.push_back(CNCCommand(CNCType::Move, lastPosition, line.toStdString()));
                } else {
                    qDebug() << "Bad position match for line";
                    qDebug() << line;
                    break;
                }
            } else {
                qDebug() << "INumber:" << result.captured();
                qDebug() << line;
            }
        }
    }
    return commands;
}
