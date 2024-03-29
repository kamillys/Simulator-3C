#pragma once

namespace VTF {

class Final
{
protected:
    ~Final() { }
};

}

//WARNING: not use unless you know why.
#define FINAL private virtual VTF::Final

//WARNING: unsafe with templates
#define NONCOPYABLE(type) \
    private: \
    type(const type&); \
    type& operator=(const type&);

//Sauce: Boost.
#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
# define __VTF__FUNCTIONNAME__ __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
# define __VTF__FUNCTIONNAME__ __PRETTY_FUNCTION__
#elif defined(__FUNCSIG__)
# define __VTF__FUNCTIONNAME__ __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
# define __VTF__FUNCTIONNAME__ __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
# define __VTF__FUNCTIONNAME__ __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
# define __VTF__FUNCTIONNAME__ __func__
#else
# define __VTF__FUNCTIONNAME__ "(unknown)"
#endif

#define UNUSED(v) ((void)v)
