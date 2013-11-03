#include "cutterlogic.h"
#include <QDebug>

using namespace glm;

CutterLogic::CutterLogic()
{
}

void CutterLogic::initL()
{
    time = 0;
    move = 0;
    lineidx = 0;
    cutterPosition.z = 1000000000;
    currentLine.clear();
}

bool CutterLogic::stepForRound(bool *stopped)
{
    bool changed = false;

/* For debugging purposes
    //stopped = true;
    //changed = true;

    //cutterPosition = dvec3(0,0,0);
    //cutRound();
*/

    //Move
    if (move +1 >= path.size())
        *stopped = true;
    else {
        //Generate line
        if (currentLine.size() == 0)
        currentLine = generateLine(path[move], path[move+1]);
        cutterPosition = currentLine[lineidx];

        changed = cutRound();

        lineidx++;
        if(lineidx >= (signed)currentLine.size()) {
            currentLine.clear();
            move++;
            lineidx = 0;
        }
    }
    return changed;
}

bool CutterLogic::stepForFlat(bool *stopped)
{
    bool changed = false;
    //Move
    if (move +1 >= path.size())
        *stopped = true;
    else {
        //Generate line
        if (currentLine.size() == 0)
        currentLine = generateLine(path[move], path[move+1]);
        cutterPosition = currentLine[lineidx];

        changed = cutFlat();

        lineidx++;
        if(lineidx >= (signed)currentLine.size()) {
            currentLine.clear();
            move++;
            lineidx = 0;
        }
    }
    return changed;
}

bool CutterLogic::step(bool *stop, int steps)
{
    bool changed = false;
    bool stopped = false;

    if (skip) {
        if (Round) {
            while (!stopped)
                changed |= stepForRound(&stopped);
        }
        else {
            while (!stopped)
                changed |= stepForFlat(&stopped);
        }
    } else {
        if (Round)
            for (int i=0;(i<steps) && !stopped;++i)
                changed |= stepForRound(&stopped);
        else
            for (int i=0;(i<steps) && !stopped;++i)
                changed |= stepForFlat(&stopped);
    }

    emit moveCutter(glm::vec3(cutterPosition));

    if (stop)
        *stop = stopped;
    return changed;
}

bool CutterLogic::cutFlat()
{
    bool changed = false;
    dvec2 cp (cutterPosition);
    dvec2 minpos = cp - dvec2(cutterDiameter+3,cutterDiameter+3);
    dvec2 maxpos = cp + dvec2(cutterDiameter+3,cutterDiameter+3);

    ivec2 minidx(vec3(grid, 0) * ((vec3(minpos,0) - origin)/size));
    ivec2 maxidx(vec3(grid, 0) * ((vec3(maxpos,0) - origin)/size));

    minidx = clamp(minidx, 0, grid.x);
    maxidx = clamp(maxidx, 0, grid.x);

    for(int i=minidx.x;i<maxidx.x;++i)
        for(int j=minidx.y;j<maxidx.y;++j)
        {
            dvec2 pos(origin.x + size.x * double(i)/grid.x,
                      origin.y + size.y * double(j)/grid.y);

            float& height = heightMap[i*grid.y+j];
            float cutterHeight = cutterPosition.z - origin.z;
            double dist = distance(cp, pos);
            if (dist <= cutterDiameter*0.5 && height > cutterHeight)
            {
                height = cutterHeight; changed = true;
                if (height < 0)
                    problemMap[i*grid.y+j] = 1;
            }
            //height = -11; changed = true;
        }

    return changed;
}

bool CutterLogic::cutRound()
{
    bool changed = false;
    dvec2 cp (cutterPosition);
    dvec2 minpos = cp - dvec2(cutterDiameter+3,cutterDiameter+3);
    dvec2 maxpos = cp + dvec2(cutterDiameter+3,cutterDiameter+3);

    ivec2 minidx(vec3(grid, 0) * ((vec3(minpos,0) - origin)/size));
    ivec2 maxidx(vec3(grid, 0) * ((vec3(maxpos,0) - origin)/size));

    minidx = clamp(minidx, 0, grid.x);
    maxidx = clamp(maxidx, 0, grid.x);

    for(int i=minidx.x;i<maxidx.x;++i)
        for(int j=minidx.y;j<maxidx.y;++j)
        {
            dvec2 pos(origin.x + size.x * double(i)/grid.x,
                      origin.y + size.y * double(j)/grid.y);

            float& height = heightMap[i*grid.y+j];
            double dist = distance(cp, pos);

            double R = cutterDiameter * 0.5;
            //TODO: Change
            float cutterHeight = cutterPosition.z + R - sqrt(abs(R*R-dist*dist)) - origin.z;
            if (dist <= cutterDiameter*0.5 && height > cutterHeight)
            {
                height = cutterHeight; changed = true;
                if (height < 0)
                    problemMap[i*grid.y+j] = 1;
            }
        }

    return changed;
}

std::vector<dvec3> CutterLogic::generateLine(dvec3 s, dvec3 e)
{
    ivec2 minidx(dvec3(grid, 0) * ((s - dvec3(origin))/dvec3(size)));
    ivec2 maxidx(dvec3(grid, 0) * ((e - dvec3(origin))/dvec3(size)));

    std::vector<dvec3> retval;
    //Draw line
    //Store points in retval
    int cnt = glm::ceil(1.75*distance(vec2(maxidx),vec2(minidx)));
    for(int i=0;i<=cnt;++i) {
        double A = 1.0-i/double(cnt);
        retval.push_back(A*s+(1-A)*e);
    }

    return retval;
}
