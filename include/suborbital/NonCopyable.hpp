#ifndef NONCOPYABLE_HPP
#define	NONCOPYABLE_HPP

namespace suborbital
{
    class NonCopyable
    {
    protected:
        /**
         * Default constructor.
         */
        NonCopyable() = default;

    private:
        /**
         * Private (disabled) copy constructor.
         */
        NonCopyable(const NonCopyable&);

        /**
         * Private (disabled) assignment operator.
         */
        NonCopyable& operator=(const NonCopyable&);
    };
}

#endif
