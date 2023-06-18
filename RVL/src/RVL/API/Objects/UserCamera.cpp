#include "UserCamera.hpp"

#include "UserOrthographicCamera.hpp"
#include "UserPerspectiveCamera.hpp"

namespace Rvl
{
    Ref<UserOrthographicCamera> UserCamera::ToOrtho(const Ref<UserCamera>& cam)
    {
        return std::dynamic_pointer_cast<UserOrthographicCamera>(cam);
    }
    
    Ref<UserPerspectiveCamera> UserCamera::ToPerspective(const Ref<UserCamera>& cam)
    {
        return std::dynamic_pointer_cast<UserPerspectiveCamera>(cam);
    }
}
