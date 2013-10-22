#pragma once

#include <VTF/VTF>
#include <string>
#include <set>
#include <functional>

namespace VBGL
{

class Object3D : public VTF::RefObject
{
    long _id;
    //UUID uuid;
    std::string _name;

    Object3D* _parent;
    typedef std::set<VTF::RefPointer<Object3D> > ChildrenSet;
    ChildrenSet _children;

    glm::vec3 _up;

    glm::vec3 _position;
    glm::vec3 _rotation;//EULER
    glm::quat _quaternion;//QUATERNION
    glm::vec3 _scale;

    void* _renderDepth;

    bool _rotationAutoUpdate;

    glm::mat4 _matrix;
    glm::mat4 _matrixWorld;

    bool _matrixAutoUpdate;
    bool _matrixWorldNeedsUpdate;

    bool _visible;

    bool _castShadow;
    bool _receiveShadow;

    bool _frustumCulled;

    void* _userData;

    Object3D(const Object3D&);
    Object3D& operator=(const Object3D&);
public:
    Object3D();
    virtual ~Object3D();

    /**
     * Methods
     */

    void setRotationFromAxisAngle(const glm::vec3& axis, const float& angle);
    void setRotationFromEuler(void*);
    void setRotationFromMatrix(const glm::mat4& m);
    void setRotationFromQuaternion(const glm::quat& q);
    void rotateOnAxis(const glm::vec3& axis, const float& angle);

    void rotateX(const float& angle);
    void rotateY(const float& angle);
    void rotateZ(const float& angle);

    void translateOnAxis(const glm::vec3& axis, const float& distance);

    void translateX(const float& distance);
    void translateY(const float& distance);
    void translateZ(const float& distance);

    void translate(const glm::vec3& distance);

    glm::vec4 localToWorld(const glm::vec4& vector) const;
    glm::vec4 worldToLocal(const glm::vec4& vector) const;

    void lookAt(const glm::vec3& vector);

    void updateMatrix();
    void updateMatrixWorld(bool force);

    virtual void add(Object3D* object);
    virtual void remove(Object3D* object);

    void traverse(std::function<void(Object3D*)> func);
    Object3D* getObjectById() const;//TODO: add args
    Object3D* getObjectByName(const std::string& name, bool recursive=false) const;

    Object3D* clone() const; //TODO: IMPLEMENT

    /**
     * Getters and setters
     */

    long id() const;

    std::string name() const;
    void setName(const std::string &name);

    Object3D *parent() const;
    void setParent(Object3D *parent);

    glm::vec3 up() const;
    void setUp(const glm::vec3 &up);

    glm::vec3 position() const;
    void setPosition(const glm::vec3 &position);
    glm::quat quaternion() const;
    void setQuaternion(const glm::quat &quaternion);
    glm::vec3 scale() const;
    void setScale(const glm::vec3 &scale);

    void *renderDepth() const;
    void setRenderDepth(void *renderDepth);

    bool rotationAutoUpdate() const;
    void setRotationAutoUpdate(bool rotationAutoUpdate);

    glm::mat4 matrix() const;
    void setMatrix(const glm::mat4 &matrix);
    glm::mat4 matrixWorld() const;

    bool matrixAutoUpdate() const;
    void setMatrixAutoUpdate(bool matrixAutoUpdate);
    bool matrixWorldNeedsUpdate() const;
    void setMatrixWorldNeedsUpdate(bool matrixWorldNeedsUpdate);

    bool visible() const;
    void setVisible(bool visible);

    bool castShadow() const;
    void setCastShadow(bool castShadow);
    bool receiveShadow() const;
    void setReceiveShadow(bool receiveShadow);

    bool frustumCulled() const;
    void setFrustumCulled(bool frustumCulled);

    void *userData() const;
    void setUserData(void *userData);
};

}
