#ifndef CUTTERLOGIC_H
#define CUTTERLOGIC_H

#include <QObject>
#include <VTF/Math>
#include <QVector>

class CutterLogic : public QObject
{
    Q_OBJECT
public:
    double cutterDiameter = 14.0;
    glm::vec3 cutterPosition;
    glm::vec3 tpos;
    glm::vec3 size;
    glm::vec3 origin;
    glm::ivec2 grid;

    int steps = 1;

    bool skip = false;
    bool Round = false;

    std::vector<int> problemMap;
    std::vector<float> heightMap;
    QVector<glm::dvec3> path;
    std::vector<glm::dvec3> currentLine;

    CutterLogic();

    void resizeHM(int w, int h)
    {
        grid = glm::ivec2(w,h);
        heightMap.assign(w*h, size.z);
        problemMap.assign(w*h, 0);
        //heightMap.fill(QVector<double>(h, size.z), w);
    }

    qreal time = 0;
    int move = 0;
    int lineidx = 0;
    void initL();
    bool step(bool* stop, int steps);


    std::vector<glm::dvec3> generateLine(glm::dvec3 s, glm::dvec3 e);

private:
    bool cutFlat();
    bool cutRound();
    bool stepForFlat(bool *stopped);
    bool stepForRound(bool *stopped);

signals:
    void moveCutter(glm::vec3 pos);
};

#endif // CUTTERLOGIC_H
