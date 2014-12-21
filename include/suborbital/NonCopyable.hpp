#ifndef SUBORBITAL_NON_COPYABLE_HPP
#define	SUBORBITAL_NON_COPYABLE_HPP

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
