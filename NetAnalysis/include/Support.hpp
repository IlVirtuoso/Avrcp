#include <cstddef>
#include <vector>

namespace NetAnalysis
{
    template <typename Type, typename Size = size_t> Size index_of(const std::vector<Type> &array, const Type &elem)
    {
        auto itr = array.begin();
        Size i = 0;
        while (itr != array.end())
        {
            if (*itr == elem)
                return i;
            i++;
        }
        return -1;
    }
} // namespace NetAnalysis
