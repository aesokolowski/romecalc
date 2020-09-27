#ifndef USERNUM
#define USERNUM

#include <vector>

class UserNum
{
    private:
        std::vector<char> user_num;
    public:
        UserNum(const char *);
        inline std::vector<char> get_unv() { return user_num; }
};

#endif //USERNUM
