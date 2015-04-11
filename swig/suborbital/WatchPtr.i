%{
    #include <suborbital/WatchPtr.hpp>
%}

namespace suborbital
{
    class WatchPtrBase
    {
    protected:
        WatchPtrBase();
        ~WatchPtrBase();
    };

    template<typename T>
    class WatchPtr : public WatchPtrBase
    {
    public:
        ~WatchPtr();
        T& operator*() const;
        T* operator->() const;
        bool operator==(const WatchPtr &other) const;
        bool operator<(const WatchPtr &other) const;
        explicit operator bool() const;
    };
}