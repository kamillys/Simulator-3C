#include "parser.h"
#include <VTF/Exception>
#include <QDebug>
#include <QtCore>

CNCCommandList CNCParser::parse(QIODevice &file)
{
    CNCCommandList commands;
    glm::dvec3 boundMinBox;
    glm::dvec3 boundMaxBox;
    while(!file.atEnd()) {
        QString line = file.readLine();
        line.remove("\n");
        if (line.isNull() || line.isEmpty() || line.length() == 0)
            continue;
        int offset = 0;
        glm::dvec3 lastPosition;

        QRegExp InstructionNumberRE("N\\d+");
        QRegExp GCodeRE("G\\d+");//("[A-Za-z]\\d+");
        QRegExp PositionRE;
        int pos = 0;
        {
            QString number ("(-?\\d+\\.\\d\\d\\d)");
            PositionRE.setPattern("X"+number+"Y"+number+"Z"+number);
        }

        if(offset != (pos=InstructionNumberRE.indexIn(line, offset)))
        {
            qWarning() << "Cannot find instruction number";
            continue;
        }
        offset += InstructionNumberRE.matchedLength();
        //qDebug() << pos << InstructionNumberRE.matchedLength() << InstructionNumberRE.cap();
        if(offset != (pos=GCodeRE.indexIn(line, offset)))
        {
            qWarning() << "Not G-Code?";
            continue;
        }
        offset += GCodeRE.matchedLength();
        //qDebug() << pos << GCodeRE.matchedLength() << GCodeRE.cap();
        if (GCodeRE.cap() == "G01") //Move instruction
        {
            if(offset != (pos=PositionRE.indexIn(line, offset)))
            {
                qWarning() << "Bad position for " << line;
                continue;
            }
            //Valid position data. Try to extract

            lastPosition.x = PositionRE.cap(1).toDouble();
            lastPosition.y = PositionRE.cap(2).toDouble();
            lastPosition.z = PositionRE.cap(3).toDouble();
            boundMaxBox = glm::max(boundMaxBox, lastPosition);
            boundMinBox = glm::min(boundMinBox, lastPosition);
            commands.push_back(CNCCommand(CNCType::Move, lastPosition, line.toStdString()));
        }

//Qt5 Code. Because fucking awesome.
        /*QRegularExpressionMatch result = InstructionNumberRE.match(line, offset);
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
        }*/
    }
    return commands;
}
