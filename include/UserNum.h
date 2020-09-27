#ifndef USERNUM
#define USERNUM

#include <vector>

class UserNum
{
    private:
        std::vector<char> user_num;
    public:
        UserNum(const char *);
        inline std::vector<char> get_unv() { return this->user_num; }
        inline size_t get_count() { return this->user_num.size(); }
};

#endif //USERNUM
