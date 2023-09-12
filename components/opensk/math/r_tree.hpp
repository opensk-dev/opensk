# ifndef SK_MATH_R_TREE_HPP_
# define SK_MATH_R_TREE_HPP_

namespace sk::math {

class RTree {
public:
    RTree() = default;
    ~RTree() = default;

    RTree(const RTree& other) = default;
    RTree& operator=(const RTree& other) = default;

    RTree(RTree&& other) noexcept = default;
    RTree& operator=(RTree&& other) noexcept = default;

private:

};

} // sk::math

# endif // SK_MATH_R_TREE_HPP_
