%{
    #include <suborbital/EntitySet.hpp>
%}

// Include std::set so that the set iterators are exposed to SWIG.
%include <std_set.i>
%template(InternalEntitySet) std::set<suborbital::WatchPtr<suborbital::Entity>>;

// We need to do a little work to allow Python to iterate over entity sets. In particular, we need to provide an
// `__iter__` method that returns an iterator object for the set. Our iterator object needs to recall the current
// position and so we create a custom EntitySetIterator class that stores both the `current` EntitySet iterator and the
// `end` iterator. Finally, we provide a `next` method that returns the Entity pointer and increments the `current`
// iterator.

%inline %{
    struct EntitySetIterator {
        suborbital::EntitySet::iterator current;
        suborbital::EntitySet::iterator end;
    };
%}

%exception EntitySetIterator::next {
    if (arg1->current == arg1->end) {
        SWIG_SetErrorObj(PyExc_StopIteration, SWIG_Py_Void());
        SWIG_fail;
    } else {
        $action;
    }
}

%extend EntitySetIterator {
    EntitySetIterator* __iter__() {
        return $self;
    }

    suborbital::WatchPtr<suborbital::Entity> next() {
        return *($self->current++);
    }
}

%extend suborbital::EntitySet {
    EntitySetIterator __iter__() {
        EntitySetIterator iter = { $self->begin(), $self->end() };
        return iter;
    }
}

%include <suborbital/EntitySet.hpp>