#ifndef USERNUM
#define USERNUM

#include <vector>

class UserNum
{
    private:
        char user_nums[128];
        std::vector<char> user_numv;
    public:
        UserNum(const char *);
        inline char * get_uns() { return this->user_nums; }
        inline std::vector<char> get_unv() { return this->user_numv; }
        inline size_t get_count() { return this->user_numv.size(); }
};

#endif //USERNUM
