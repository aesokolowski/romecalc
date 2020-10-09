#ifndef USERNUM
#define USERNUM

#include <vector>

class UserNum
{
    private:
        std::vector<char> user_numv;
	size_t size;
    public:
        UserNum(const char *);
        inline std::vector<char> get_unv() { return this->user_numv; }
        inline size_t get_count() { return this->size; }
};

#endif //USERNUM
