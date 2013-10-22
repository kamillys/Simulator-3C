#include "Object3D.h"

using namespace VTF;
using namespace VBGL;

static long _objectCount = 0;

Object3D::Object3D() :
    _id(_objectCount++),
    _parent(NULL),
    _up(0,1,0),
    _scale(1,1,1),
    _rotationAutoUpdate(true),
    _matrixAutoUpdate(true),
    _matrixWorldNeedsUpdate(true),
    _visible(true),
    _castShadow(false),
    _receiveShadow(false),
    _frustumCulled(true),
    _userData(NULL)
{
}

Object3D::~Object3D()
{
    if(_parent)
        _parent->remove(this);
}

//void Object3D::applyMatrix(const glm::mat4 &mat)
//{
//    _matrix = mat * _matrix;
//    _position = positionFromMatrix(_matrix);
//    _scale = scaleFromMatrix(_matrix);
//    glm::mat4 rotationMat = _matrix;
//    _quaternion = quatFromRotationMatrix(rotationMat);
//}

void Object3D::setRotationFromAxisAngle(const glm::vec3 &axis, const float &angle)
{
    setQuaternion(glm::quat(angle, axis));
}

void Object3D::setRotationFromMatrix(const glm::mat4 &m)
{
    setQuaternion(glm::quat(m));
}

void Object3D::setRotationFromQuaternion(const glm::quat &q)
{
    setQuaternion(q);
}

void Object3D::rotateOnAxis(const glm::vec3 &axis, const float &angle)
{
    glm::quat q1(angle, axis);
    setQuaternion(quaternion() * q1);
}

void Object3D::rotateX(const float &angle)
{
    rotateOnAxis(glm::vec3(1,0,0), angle);
}

void Object3D::rotateY(const float &angle)
{
    rotateOnAxis(glm::vec3(0,1,0), angle);
}

void Object3D::rotateZ(const float &angle)
{
    rotateOnAxis(glm::vec3(0,0,1), angle);
}

void Object3D::translateOnAxis(const glm::vec3 &axis, const float &distance)
{
    glm::vec3 v = axis;
    v = v * _quaternion;
    setPosition(position()+v*distance);
}

void Object3D::translateX(const float &distance)
{
    return translateOnAxis(glm::vec3(1,0,0), distance);
}

void Object3D::translateY(const float &distance)
{
    return translateOnAxis(glm::vec3(0,1,0), distance);
}

void Object3D::translateZ(const float &distance)
{
    return translateOnAxis(glm::vec3(0,0,1), distance);
}

void Object3D::translate(const glm::vec3 &distance)
{
    translateX(distance.x);
    translateY(distance.y);
    translateZ(distance.z);
}

glm::vec4 Object3D::localToWorld(const glm::vec4 &vector) const
{
    return _matrix * vector;
}

glm::vec4 Object3D::worldToLocal(const glm::vec4 &vector) const
{
    return glm::inverse(_matrix) * vector;
}

void Object3D::lookAt(const glm::vec3 &vector)
{
    glm::mat4 m = glm::lookAt(vector, _position, _up);
    setQuaternion(quatFromRotationMatrix(m));
}

void Object3D::updateMatrix()
{
    _matrix = glm::toMat4(_quaternion);
    _matrix = glm::translate(_matrix, _position);
    _matrix = glm::scale(_matrix, _scale);
    _matrixWorldNeedsUpdate = true;
}

void Object3D::updateMatrixWorld(bool force)
{
    //if ( _matrixAutoUpdate )
    //    updateMatrix();

    if ( _matrixWorldNeedsUpdate  || force ) {
        if ( !_parent ) {
            _matrixWorld = _matrix;
        } else {
            _matrixWorld = _parent->_matrixWorld * _matrix;
        }

        _matrixWorldNeedsUpdate = false;

        force = true;
    }

    for(ChildrenSet::iterator ch = _children.begin(); ch != _children.end(); ch++)
    {
        const_cast<Object3D*>((*ch).get())->updateMatrixWorld(force);
    }
}

void Object3D::add(Object3D *object)
{
    if(object == NULL)
        return;
    Object3D* tmp = object;
    while(tmp != NULL){
        if(tmp == this)
            return;
        tmp = tmp->parent();
    }

    _children.insert(VTF::RefPointer<Object3D>(object));
    object->setParent(this);

    //TODO: Add to scene
}

void Object3D::remove(Object3D *object)
{
    _children.erase(object);
    object->setParent(NULL);
}

void Object3D::traverse(std::function<void (Object3D*)> func)
{
    func(this);
    for(auto ch = _children.begin(); ch != _children.end(); ch++)
        func(const_cast<Object3D*>(ch->get()));
    for(auto ch = _children.begin(); ch != _children.end(); ch++)
        const_cast<Object3D*>(ch->get())->traverse(func);
}

Object3D *Object3D::getObjectByName(const std::string &name, bool recursive) const
{
    if(_name == name)
        return const_cast<Object3D*>(this);

    if (!recursive)
        return NULL;

    for(auto ch = _children.begin(); ch != _children.end(); ch++) {
        Object3D* tmp = (*ch)->getObjectByName(name, recursive);
        if (tmp)
            return tmp;
    }

    return NULL;
}

/****************************************
 *
 *   Properties getters and setters
 *
 ****************************************/

std::string Object3D::name() const
{
    return _name;
}

void Object3D::setName(const std::string &name)
{
    _name = name;
}

Object3D *Object3D::parent() const
{
    return _parent;
}

void Object3D::setParent(Object3D *parent)
{
    _parent = parent;
}

void *Object3D::userData() const
{
    return _userData;
}

void Object3D::setUserData(void *userData)
{
    _userData = userData;
}

bool Object3D::frustumCulled() const
{
    return _frustumCulled;
}

void Object3D::setFrustumCulled(bool frustumCulled)
{
    _frustumCulled = frustumCulled;
}

bool Object3D::receiveShadow() const
{
    return _receiveShadow;
}

void Object3D::setReceiveShadow(bool receiveShadow)
{
    _receiveShadow = receiveShadow;
}

bool Object3D::castShadow() const
{
    return _castShadow;
}

void Object3D::setCastShadow(bool castShadow)
{
    _castShadow = castShadow;
}

bool Object3D::visible() const
{
    return _visible;
}

void Object3D::setVisible(bool visible)
{
    _visible = visible;
}

bool Object3D::matrixWorldNeedsUpdate() const
{
    return _matrixWorldNeedsUpdate;
}

void Object3D::setMatrixWorldNeedsUpdate(bool matrixWorldNeedsUpdate)
{
    _matrixWorldNeedsUpdate = matrixWorldNeedsUpdate;
}

bool Object3D::matrixAutoUpdate() const
{
    return _matrixAutoUpdate;
}

void Object3D::setMatrixAutoUpdate(bool matrixAutoUpdate)
{
    _matrixAutoUpdate = matrixAutoUpdate;
}

glm::mat4 Object3D::matrixWorld() const
{
    if (_parent)
        return _parent->matrixWorld() * _matrix;
    return _matrix;
}

long Object3D::id() const
{
    return _id;
}

glm::mat4 Object3D::matrix() const
{
    return _matrix;
}

void Object3D::setMatrix(const glm::mat4 &matrix)
{
    _matrix = matrix;
}

bool Object3D::rotationAutoUpdate() const
{
    return _rotationAutoUpdate;
}

void Object3D::setRotationAutoUpdate(bool rotationAutoUpdate)
{
    _rotationAutoUpdate = rotationAutoUpdate;
}

void *Object3D::renderDepth() const
{
    return _renderDepth;
}

void Object3D::setRenderDepth(void *renderDepth)
{
    _renderDepth = renderDepth;
}

glm::vec3 Object3D::scale() const
{
    return _scale;
}

void Object3D::setScale(const glm::vec3 &scale)
{
    _scale = scale;
}

glm::vec3 Object3D::position() const
{
    return _position;
}

void Object3D::setPosition(const glm::vec3 &position)
{
    _position = position;
}

glm::quat Object3D::quaternion() const
{
    return _quaternion;
}

void Object3D::setQuaternion(const glm::quat &quaternion)
{
    _quaternion = quaternion;
}

glm::vec3 Object3D::up() const
{
    return _up;
}

void Object3D::setUp(const glm::vec3 &up)
{
    _up = up;
}
