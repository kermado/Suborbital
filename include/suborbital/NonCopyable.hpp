#ifndef SUBORBITAL_NON_COPYABLE_HPP
#define	SUBORBITAL_NON_COPYABLE_HPP

namespace suborbital
{
    /**
     * The base class for all classes that should not be copy constructable.
     */
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
         * Private (disabled) copy assignment operator.
         */
        NonCopyable& operator=(const NonCopyable&);
    };
}

#endif
